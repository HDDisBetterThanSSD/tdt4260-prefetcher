/*
 * A sample prefetcher which does sequential one-block lookahead.
 * This means that the prefetcher fetches the next block _after_ the one that
 * was just accessed. It also ignores requests to blocks already in the cache.
 */

#include "interface.hh"
#include "best_offset.hh"

BestOffset bo_pf;

void prefetch_init(void)
{
    bo_pf = BestOffset();
}

void prefetch_access(AccessStat stat)
{
    /* pf_addr is now an address within the _next_ cache block */
    //Addr pf_addr = stat.mem_addr + BLOCK_SIZE;

    /*
     * Issue a prefetch request if a demand miss occured,
     * and the block is not already in cache.
     */
    //if (stat.miss && !in_cache(pf_addr)) {
        //issue_prefetch(pf_addr);
    //}

    Addr pf_offset = bo_pf.get_offset(stat.mem_addr);

    if (pf_offset) {
        //Addr pf_addr = stat.mem_addr + pf_offset * BLOCK_SIZE;
        //if (pf_addr <= MAX_PHYS_MEM_ADDR)
        
        issue_prefetch(stat.mem_addr + pf_offset * BLOCK_SIZE);
    }
}

void prefetch_complete(Addr addr) {
    /*
     * Called when a block requested by the prefetcher has been loaded.
     */
    bo_pf.insert_prefetched_line(addr);
}
