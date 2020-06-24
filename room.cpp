#include "./room.h"
#include "./constants.h"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::sort;
using std::vector;
using std::runtime_error;

enum class ROOM_CONSTS {
    QUIT = -1,
    MODIFY = -1,
    NONE = -1
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

int room::modify_reservation() 
{
    show_reservation_state();

    auto idx = static_cast<int>(ROOM_CONSTS::MODIFY);
    get_input_with_msg("Enter reeservation number to modify: ", idx);

    if (idx >= 0 && idx < dates.size()) {
        auto new_start_date = static_cast<int>(ROOM_CONSTS::NONE);
        auto new_end_date = static_cast<int>(ROOM_CONSTS::NONE);
        if ((get_input_with_msg("Enter new starting date(-1 to cancle): ", new_start_date)) == -1) {
            return -1;
        }
        if ((get_input_with_msg("Enter new ending date(-1 to cancle): ", new_end_date)) == -1) {
            return -1;
        }

        dates[idx].start_date = new_start_date;
        dates[idx].end_date = new_end_date;
    } else {
        throw runtime_error("Modify_Reservation: Wrong reservation number was entered!");
    }
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
        throw runtime_error("Invalid reservation number!");
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