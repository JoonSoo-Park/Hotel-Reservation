#include "./room.h"
#include "./constants.h"
#include "./Reservation.h"
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <cctype>
#include <iomanip>

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

void room::reserve(struct tm& S, struct tm& E) {
    Reservation reservation(S, E);
    is_reserved = true;

    reservations.push_back(reservation);

    sort (reservations.begin(), reservations.end(), Reservation::compare);
}

void room::show_reservation_state() const {
    for (auto i = 0; i < reservations.size(); ++i) {
        cout << static_cast<int>(i) << " : Reserved: ";
        reservations[i].Print();
    }
}

int room::modify_reservation() 
{
    show_reservation_state();

    auto idx = static_cast<int>(ROOM_CONSTS::MODIFY);
    get_input_with_msg("Enter reservation number to modify: ", idx);

    if (idx < 0 || idx >= reservations.size()) {
        return 0;
    }

    // TODO
    // Get the dates
    // check if is valid
    // apply the changes
    time_t rawtime;
    time(&rawtime);

    struct tm* t = localtime(&rawtime);
    struct tm S = *t;
    struct tm E = *t;

    if (get_reservation_start(S) == -1) {
        return -1;
    }
    
    if (get_reservation_end(S, E) == -1) {
        return -1;
    }

    // Check if available
    if (available(S, E, idx)) {
        reservations[idx].Modify(S, E);
    } else {
        cout << "Date already reserved.";
        return -1;
    }

    return 1;
}

void room::cancle_reservation() {
    show_reservation_state();

    auto idx = static_cast<int>(ROOM_CONSTS::QUIT);
    get_input_with_msg("Enter reservation number to cancle: ", idx);

    if (idx >= 0 && idx < reservations.size()) {
        reservations.erase(reservations.begin() + idx);
        if (reservations.size() == 0) {
            is_reserved = false;
        }
    } else {
        throw runtime_error("Invalid reservation number!");
    }
}

bool room::available(struct tm& S, struct tm& E, int idx) {
    time_t new_start = mktime(&S);
    time_t new_end = mktime(&E);

    for (auto i = 0; i < reservations.size(); ++i) {
        if (static_cast<int>(i) == idx) {
            continue;
        }

        time_t start = reservations[i].MktimeS();
        time_t end = reservations[i].MktimeE();

        if ((difftime(new_start, start) >= 0 && difftime(end, new_start) > 0 ) ||
            (difftime(new_end, start) > 0 && difftime(end, new_end) >= 0)) {
                return false;
        }
    }
    return true;
}

// not needed anymore from v.4
bool room::check_date_validity(struct tm D, int idx)
{
    for (auto i = 0; i < reservations.size(); ++i) {
        if (static_cast<int>(i) == idx) {
            continue;
        }
        time_t start = reservations[i].MktimeS();
        time_t end = reservations[i].MktimeE();
        time_t target = mktime(&D);


        cout << difftime(target, start) << endl;
        cout << difftime(end, target) << endl;
        if (difftime(target, start) >= 0 && difftime(end, target) > 0) {
            return false;
        }
    }
    return true;
}