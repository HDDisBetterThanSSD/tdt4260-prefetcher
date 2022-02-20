#include "recent_request.hh"



RecentRequest::RecentRequest() : prev_addr(0) {
    /* Reset the tables */
    reset();
}

RecentRequest::~RecentRequest() {
}

void RecentRequest::insert(Tag *rr_table, Addr addr) {
    rr_table[GET_INDEX(addr)] = GET_TAG(addr);
}

void RecentRequest::insert_left(Addr addr) {
    
    // Insert the left address one request later
    if (prev_addr)
        insert(rr_table_left, prev_addr);

    prev_addr = addr;
    //rr_table_left[GET_INDEX(addr)] = GET_TAG(addr);
}

void RecentRequest::insert_right(Addr addr) {
    insert(rr_table_right, addr);
    //rr_table_right[GET_INDEX(addr)] = GET_TAG(addr);
}

bool RecentRequest::is_recent(Addr addr) {
    int index   = GET_INDEX(addr);
    Tag tag     = GET_TAG(addr);

    return (rr_table_left[index] == tag || rr_table_right[index] == tag);
}

void RecentRequest::reset() {
    memset(rr_table_left, 0, sizeof(Tag) * RR_SIZE);
    memset(rr_table_right, 0, sizeof(Tag) * RR_SIZE);
}