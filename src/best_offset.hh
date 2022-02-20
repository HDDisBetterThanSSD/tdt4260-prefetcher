#include <stdint.h>
#include <stdbool.h>
#include <map>
#include <algorithm>

#include "interface.hh"
#include "recent_request.hh"

#define MAX_REQUESTS    100


#define MAX_SCORE       31
#define GOOD_SCORE      25
#define BAD_SCORE       5


/*  This will create offsets with max value of 64, 
    where every number is on the form 2^i * 3^j * 5^k,
    where i, j, k >= 0
*/
#define NO_OFFSETS      27  


struct OffsetScore {
    uint16_t offset;
    uint16_t score;
};


class BestOffset
{
private:
    /* data */
    int             current_offset;
    bool            add_offset;

    OffsetScore     offsets[NO_OFFSETS];
    RecentRequest   recent_requests;
    
    uint16_t        no_requests;
    const uint16_t  max_no_requests;

    const uint8_t   max_score;
    const uint8_t   good_score_limit;
    const uint8_t   bad_score_limit;

    /* methods */
    int reset();

    int test_offsets(Addr addr);

    int evaluate_scores();

    void init_offsets();

public:
    BestOffset(
        uint8_t     bad_score_limit     = BAD_SCORE,
        uint8_t     good_score_limit    = GOOD_SCORE, 
        uint16_t    max_no_requests     = MAX_REQUESTS,
        uint8_t     max_score           = MAX_SCORE
    );
    ~BestOffset();

    int get_offset(Addr addr);
};
