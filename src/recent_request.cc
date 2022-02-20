#include "recent_request.hh"



RecentRequest::RecentRequest(/* args */) {
    /* Reset the tables */
    reset();
}

RecentRequest::~RecentRequest() {
}

void RecentRequest::insert_left(Addr addr) {
    rr_table_left[GET_INDEX(addr)] = GET_TAG(addr);
}

void RecentRequest::insert_right(Addr addr) {
    rr_table_right[GET_INDEX(addr)] = GET_TAG(addr);
}

RecentRequest::is_recent(Addr addr) {
    int index   = GET_INDEX(addr);
    Tag tag     = GET_TAG(addr);

    return (rr_table_left[index] == tag || rr_table_right[index] == tag);
}

void RecentRequest::reset() {
    memset(rr_table_left, 0, sizeof(Tag) * RR_SIZE);
    memset(rr_table_right, 0, sizeof(Tag) * RR_SIZE);
}