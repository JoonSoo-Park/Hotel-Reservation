#include "./room.h"
#include "./constants.h"
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <cctype>

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

bool room::check_date_validity(int new_date, int idx)
{
    using sz_type = vector<reserved_date>::size_type;
    for (sz_type i = 0; i < dates.size(); ++i) {
        if (static_cast<int>(i) == idx) {
            continue;
        }
        if (dates[i].start_date <= new_date && new_date <= dates[i].end_date) {
            cout << "Date already reserved!\n";
            return false;
        }
    }
    return true;
}

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

    if (idx < 0 || idx >= dates.size()) {
        return 0;
    }

    auto new_start_date = static_cast<int>(ROOM_CONSTS::NONE);
    auto new_end_date = static_cast<int>(ROOM_CONSTS::NONE);

    do {
        if (get_input_with_msg("Enter new start date: ", new_start_date) == -1) {
            return -1;
        }
    } while (!check_date_validity(new_start_date, idx));

    do {
        if (get_input_with_msg("Enter new end date: ", new_end_date) == -1) {
            return -1;
        }
    } while (!check_end_date_validity(new_start_date, new_end_date) ||
             !check_date_validity(new_end_date, idx));

    modify_dates(idx, new_start_date, new_end_date);

    return 1;
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

void room::modify_dates(int idx, int new_start_date, int new_end_date)
{
    const char yes = 'y';
    const char no = 'n';

    cout << "New reservation date " << new_start_date << " ~ " << new_end_date << endl;

    while (true) {
        char c;

        cout << "Apply change? (y / n): ";
        get_single_char(c);

        c = tolower(c);
        if (c == yes) {
            dates[idx].start_date = new_start_date;
            dates[idx].end_date = new_end_date;
            cout << "Changes have been applied.\n";
            break;
        } else if (c == no) {
            cout << "No changes are applied.\n";
            return;
        }
    }
}