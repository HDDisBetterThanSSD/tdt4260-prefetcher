#include "best_offset.hh"

BestOffset::BestOffset(
        uint8_t     bad_score_limit,
        uint8_t     good_score_limit,
        uint16_t    max_no_requests,
        uint8_t     max_score
    ) : 
        no_requests(0),
        max_no_requests(max_no_requests),
        max_score(max_score),
        good_score_limit(good_score_limit),
        bad_score_limit(bad_score_limit) 
{
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

}

int BestOffset::get_offset(Addr addr) {
    if (!add_offset)
        return 0;
    
    if (++no_requests >= MAX_REQUESTS)
        evaluate_scores();
}


int BestOffset::test_offsets(Addr addr) {
    for (int i = 0; i < NO_OFFSETS; i++) {
        if (recent_requests.is_recent(addr + offsets[i].offset * BLOCK_SIZE)) {
            /* Increment score of current tested offset */
            if (++offsets[i].score >= GOOD_SCORE)
                return offsets[i].offset;
            /* If offset score is bigger or equal to GOOD_SCORE, return the offset */

        }
    }
    /* else return 0 */
    return 0;
}

/* Initialize offsets to be on the form 2^i * 3^j * 5^k,
    where i, j, k >= 0.
    Does not need to be fast, run on init
*/
void BestOffset::init_offsets() {
    int c2 = 0, c3 = 0, c5 = 0, next;
    offsets[0].offset = 1;
    for (int i = 1; i < NO_OFFSETS; i++) {
        next = min(2 * offsets[c2], 3 * offsets[c3], 5 * offsets[c5]);
        offsets[i] = {next, 0};
        if (next == 2 * offsets[c2]) c2++;
        if (next == 3 * offsets[c3]) c3++;
        if (next == 5 * offsets[c5]) c5++;
    }
}