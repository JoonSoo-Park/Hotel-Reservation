#include "./hotel.h"
#include <iostream>

using namespace std;

void hotel::initialize() {
    rooms[0] = new single();
    rooms[1] = new single();
    rooms[2] = new single();
    rooms[3] = new single();
    rooms[4] = new single();
    rooms[5] = new single();
    rooms[6] = new single();
    rooms[7] = new sweet();
    rooms[8] = new sweet();
    rooms[9] = new sweet();
}

void hotel::print_info() const {
    for (int i = 0; i < 10; ++i) {
        if (rooms[i]) {
            cout << "room" << i << " " << rooms[i]->get_price() << endl;
        }
    }
}

int hotel::reserve() {
    int start, end;
    char c;
    bool success = false;

    if ((get_input_with_msg("Enter starting date(-1 to cancle): ", start)) == -1) {
        return -1;
    }
    if ((get_input_with_msg("Enter ending date(-1 to cancle): ", end)) == -1) {
        return -1;
    }
    print_available_rooms(start, end);

    int n;
    if ((get_input_with_msg("Enter room number to reserve(-1 to cancle)", n)) == -1) {
        return -1;
    }
        
    rooms[n]->reserve(start, end);
    return 0; // success
}

void hotel::cancle_reservation() {
    cout << "************ Cancle Reservation **************\n";

    int is_reserved = show_reservation_state();

    if (is_reserved) {
        int room_number = 0;
        get_input_with_msg("Enter room number to cancle: ", room_number);

        if (room_number >= 0 && room_number < rooms.size()) {
            int idx = 0;
            rooms[room_number]->cancle_reservation();
        } else {
            throw std::runtime_error("Invalid room number!");
        }
    }
}

void hotel::print_available_rooms(int start, int end) const {
    cout << "************ Available rooms list **************\n";

    for (vector<room*>::size_type i = 0; i < rooms.size(); ++i) {
        if (rooms[i]->available(start, end)) {
            cout << "room[" << static_cast<int>(i) << "]\n";
        }
    }
}

int hotel::show_reservation_state() const {
    int count = 0;

    cout << "************ Room Reservation State **************\n";
    for (vector<room*>::size_type i = 0; i < rooms.size(); ++i) {
        if (rooms[i]) {
            cout << "room" << static_cast<int>(i) << endl;
            rooms[i]->show_reservation_state();
            cout << endl;
            count++;
        }
    } 
    if (count == 0) {
        cout << "No rooms are reserved\n";
    }
    return count;
}
