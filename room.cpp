#include "./room.h"

void room::reserve(int start, int end) {
    if (booked) {
        fprintf(stderr, "Already booked room!");
    }
    else {
        reserve_start_date = start;
        reserve_end_date = end;

        if (date >= reserve_start_date && date <= reserve_end_date)
            booked = true;
    }
}

bool room::available(int start, int end) const {
    if (end >= reserve_start_date && start <= reserve_end_date)
        return false;
    return true;
}