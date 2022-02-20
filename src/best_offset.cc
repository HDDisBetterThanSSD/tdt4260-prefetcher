#include "best_offset.hh"

BestOffset::BestOffset() : current_offset(1), add_offset(true), no_requests(0) {
    init_offsets();
    reset();
}

BestOffset::~BestOffset()
{
}

void BestOffset::reset() {
    no_requests = 0;

    /* Set all scores to 0 */
    for (int i = 0; i < NO_OFFSETS; i++)
        offsets[i].score = 0;
}

int BestOffset::evaluate_scores() {
    /* Find the best score and set current offset to that */
    int best_offset_index = 0;
    for (int i = 1; i < NO_OFFSETS; i++) {
        /* Here the comparison favours bigger offsets, change to strictly bigger in favour of smaller offsets */
        if (offsets[i].score >= offsets[best_offset_index].score)
            best_offset_index = i;
    }
    return (offsets[best_offset_index].score > BAD_SCORE) ? offsets[best_offset_index].offset : 0;
}

int BestOffset::get_offset(Addr addr) {
    /*  Test different offsets. If true, one or more offsets have a score better than GOOD_SCORE
        OR
        The number of requests is larger or equal to the MAX_REQUESTS */
    recent_requests.insert_left(addr);

    if (test_offsets(addr) || (++no_requests >= MAX_REQUESTS)) {
        /*
        if ((current_offset = evaluate_scores())
            add_offset = true;
        else
            add_offset = false;*/

        /* The following function and the if above do the same thing */
        add_offset = (current_offset = evaluate_scores()) ? true : false;
        reset();
    }

    return (add_offset) ? current_offset : 0;
}


bool BestOffset::test_offsets(Addr addr) {
    bool found_good_offset = false;
    for (int i = 0; i < NO_OFFSETS; i++) {
        if (recent_requests.is_recent(addr - offsets[i].offset * BLOCK_SIZE)) {
            /* Increment score of current tested offset */
            if (++offsets[i].score == MAX_SCORE)
                found_good_offset = true;
                //return offsets[i].offset;
            /* If offset score is bigger or equal to GOOD_SCORE, return the offset */

        }
    }
    /* else return 0 */
    return found_good_offset;
}


void BestOffset::init_offsets() {
    /* Initialize offsets to be on the form 2^i * 3^j * 5^k,
    where i, j, k >= 0.
    Does not need to be fast, run on init
    */
    int c2 = 0, c3 = 0, c5 = 0, next;
    offsets[0].offset = 1;
    for (int i = 1; i < NO_OFFSETS; i++) {
        next = std::min(std::min(2 * offsets[c2].offset, 3 * offsets[c3].offset), 5 * offsets[c5].offset);
        offsets[i].offset = next;
        if (next == 2 * offsets[c2].offset) c2++;
        if (next == 3 * offsets[c3].offset) c3++;
        if (next == 5 * offsets[c5].offset) c5++;
    }
}

void BestOffset::insert_prefetched_line(Addr addr) {
    recent_requests.insert_right(addr - current_offset * BLOCK_SIZE);
}