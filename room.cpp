#include "./room.h"
#include <iostream>

using std::cout;
using std::endl;

using std::vector;

void room::reserve(int start, int end) {
    reserved_date temp { start, end };
    is_reserved = true;

    dates.push_back(temp);
}

bool room::available(int start, int end) const {
    for (vector<reserved_date>::size_type i = 0; i < dates.size(); ++i) {
        int st = dates[i].start_date;
        int en = dates[i].end_date;

        if ((start >= st && start < en) ||
            (end > st && end <= en))
            return false;
    }
    return true;
}

void room::show_reservation_state() const {
    for (vector<reserved_date>::size_type i = 0; i < dates.size(); ++i) {
        int start_date = dates[i].start_date;
        int end_date = dates[i].end_date;

        cout << "Reserved: " <<  start_date <<
            " ~ " << end_date << endl;
    }
}