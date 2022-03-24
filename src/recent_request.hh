#ifndef RECENT_REQUEST_H
#define RECENT_REQUEST_H

#include <stdint.h>

#include "interface.hh"

#define BLOCK_SIZE_BITS 6                   /* This is bits to represent the BLOCKSIZE from interface.hh */
#define RR_SIZE_BITS    6
#define RR_SIZE         (1 << RR_SIZE_BITS)
#define INDEX_MASK      (RR_SIZE - 1)

#define GET_INDEX(addr) ((addr >> BLOCK_SIZE_BITS) & INDEX_MASK)
#define GET_TAG(addr)   (addr >> (BLOCK_SIZE_BITS + RR_SIZE_BITS))

typedef uint64_t Tag;

class RecentRequest
{
private:
    Tag     rr_table_left[RR_SIZE];
    Tag     rr_table_right[RR_SIZE];

    Addr    prev_addr;

    void insert(Tag *rr_table, Addr addr);
public:
    RecentRequest(/* args */);
    ~RecentRequest();

    void insert_left(Addr addr);
    void insert_right(Addr addr);

    bool is_recent(Addr addr);

    void reset();
};

#endif