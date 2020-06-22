#include "./room.h"
#include "./constants.h"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::sort;
using std::vector;

enum class ROOM_CONSTS {
    QUIT = -1
};

void room::reserve(int start, int end) {
    reserved_date temp { start, end };
    is_reserved = true;

    dates.push_back(temp);

    sort (dates.begin(), dates.end(), compare_reservation);
}

bool room::available(int start, int end) const {
    for (auto i = 0; i < dates.size(); ++i) {
        auto st = dates[i].start_date;
        auto en = dates[i].end_date;

        if ((start >= st && start < en) ||
            (end > st && end <= en) || 
            (start <= st && end >= en))
            return false;
    }
    return true;
}

void room::cancle_reservation() {
    show_reservation_state();

    auto idx = static_cast<int>(ROOM_CONSTS::QUIT);
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
    for (auto i = 0; i < dates.size(); ++i) {
        auto start_date = dates[i].start_date;
        auto end_date = dates[i].end_date;

        cout << static_cast<int>(i) << " ";
        cout << "Reserved: " <<  start_date <<
            " ~ " << end_date << endl;
    }
}