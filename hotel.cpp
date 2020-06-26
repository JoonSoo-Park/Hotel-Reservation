#include "./hotel.h"
#include "./constants.h"
#include <iostream>
#include <fstream>
#include <string>

using std::unique_ptr;
using std::string;
using std::ifstream;
using std::vector;
using std::cout;
using std::endl;
using std::cerr;
using std::make_unique;

enum class ROOM_TYPE {
    UNDEFINED = 0,
    SINGLE,
    SWEET
};

void hotel::initialize() {
    string line;
    ifstream infile("room_init.txt");

    if (!infile.is_open()) {
        cerr << "Failed to open file!\n";
        return;
    }

    while (getline(infile, line)) {
        if (line.empty())
            break;
    } 

    auto room_number = ROOM_TYPE::UNDEFINED;
    auto room_type = ROOM_TYPE::UNDEFINED;
    while (getline(infile, line)) {
        sscanf(line.c_str(), "%d : %d", &room_number, &room_type);
        if (room_type == ROOM_TYPE::SINGLE) {
            rooms.push_back(Handle<room>(new single()));
        } 
        else if (room_type == ROOM_TYPE::SWEET) {
            rooms.push_back(Handle<room>(new sweet()));
        }
    }
    infile.close();

    running = true;
}

void hotel::print_info() const {
    for (auto i = 0; i < rooms.size(); ++i) {
        if (rooms[i]) {
            cout << "room" << static_cast<int>(i) << " " <<
                 rooms[static_cast<int>(i)]->get_price() << endl;
        }
    }
}

int hotel::reserve() {
    int start;
    int end;
    char c;
    auto success = false;

    if ((get_input_with_msg("Enter starting date(-1 to cancle): ", start)) == -1) {
        return -1;
    }
    if ((get_input_with_msg("Enter ending date(-1 to cancle): ", end)) == -1) {
        return -1;
    }
    print_available_rooms(start, end);

    auto n = -1;
    /*
    if ((get_input_with_msg("Enter room number to reserve(-1 to cancle)", n)) == -1) {
        return -1;
    }
    */

    while (true) {
        get_input_with_msg("Enter room number to reserve(-1 to cancle)", n);
        if (n == -1) {
            return -1;
        }
        if (rooms[n]->available(start, end)) {
            break;
        }
    }
        
    rooms[static_cast<int>(n)]->reserve(start, end);
    return 0; // success
}

void hotel::modify_reservation() {
    puts("************ Modify Reservation **************\n");

    auto is_reserved = show_reservation_state();

    if (is_reserved) {
        auto room_number = 0;
        get_input_with_msg("Enter room number to modify: ", room_number);

        if (room_number >= 0 && room_number < rooms.size() && rooms[room_number]) {
            auto idx = 0;
            rooms[room_number]->modify_reservation();
        } else {
            throw std::runtime_error("Modify Reservation: Invalid room number!");
        }
    }
}

void hotel::cancle_reservation() {
    cout << "************ Cancle Reservation **************\n";

    auto is_reserved = show_reservation_state();

    if (is_reserved) {
        auto room_number = 0;
        get_input_with_msg("Enter room number to cancle: ", room_number);

        if (room_number >= 0 && room_number < rooms.size()) {
            auto idx = 0;
            rooms[room_number]->cancle_reservation();
        } else {
            throw std::runtime_error("Invalid room number!");
        }
    }
}

void hotel::print_available_rooms(int start, int end) const {
    cout << "************ Available rooms list **************\n";

    for (auto i = 0; i < rooms.size(); ++i) {
        if (rooms[static_cast<int>(i)]->available(start, end)) {
            cout << "room[" << static_cast<int>(i) << "]\n";
        }
    }
}

int hotel::show_reservation_state() const {
    int count = 0;

    cout << "************ Room Reservation State **************\n";
    for (auto i = 0; i < rooms.size(); ++i) {
        if (rooms[static_cast<int>(i)]) {
            cout << "room" << static_cast<int>(i) << endl;
            rooms[static_cast<int>(i)]->show_reservation_state();
            cout << endl;
            count++;
        }
    } 
    if (count == 0) {
        cout << "No rooms are reserved\n";
    }
    return count;
}
