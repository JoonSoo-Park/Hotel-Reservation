#include "./room.h"
#include "./constants.h"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::sort;
using std::vector;

void room::reserve(int start, int end) {
    reserved_date temp { start, end };
    is_reserved = true;

    dates.push_back(temp);

    sort (dates.begin(), dates.end(), compare_reservation);
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

void room::cancle_reservation() {
    show_reservation_state();

    int idx;
    get_input_with_msg("Enter reservation number to cancle: ", idx);

    if (idx >= 0 && idx < dates.size()) {
        dates.erase(dates.begin() + idx);
        if (dates.size() == 0) {
            is_reserved = false;
        }
    } else {
        throw std::runtime_error("Invalid reservation number!");
    }
}

void room::show_reservation_state() const {
    for (vector<reserved_date>::size_type i = 0; i < dates.size(); ++i) {
        int start_date = dates[i].start_date;
        int end_date = dates[i].end_date;

        cout << static_cast<int>(i) << " ";
        cout << "Reserved: " <<  start_date <<
            " ~ " << end_date << endl;
    }
}