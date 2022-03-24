#ifndef BEST_OFFSET_H
#define BEST_OFFSET_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <map>
#include <algorithm>

#include "interface.hh"
#include "recent_request.hh"

#define MAX_REQUESTS    64


#define MAX_SCORE       31
#define GOOD_SCORE      25
#define BAD_SCORE       1


/*  This will create offsets with max value of 64, 
    where every number is on the form 2^i * 3^j * 5^k,
    where i, j, k >= 0
*/
#define NO_OFFSETS      52/*27 gives max of 64 */  /*52 gives max of 256 */


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

    /* methods */
    /**
     * @brief Resets the best-offset learning
     * 
     * Sets the no_requests to 0 and 
     * resets all the scores in @a offsets
     * 
     */
    void reset();

    /**
     * @brief Tests all the different offsets in the offsets list
     * 
     * @param addr The base address to test the offsets on.
     * @return Returns true if one or more of the offsets have a score greater than the GOOD_SCORE value
     */
    bool test_offsets(Addr addr);

    /**
     * @brief Finds the best offset based on the score for each offset
     * 
     * @return Returns the best offset, unless the best offset is 0. Then the prefetcher should be off.
     */
    int evaluate_scores();

    /**
     * @brief Internal method to calculate the offsets. Is run when object is created.
     * 
     */
    void init_offsets();

public:
    /**
     * @brief Construct a new Best Offset object to calculate the best offsets for prefetching
     * 
     */
    BestOffset();

    /**
     * @brief Get the best offset and trigger learning
     * 
     * @param addr The baseaddress of the data
     * @return Returns the best offset, if it returns 0, you should not prefetch.
     */
    int get_offset(Addr addr);

    void insert_prefetched_line(Addr addr);
};

#endif