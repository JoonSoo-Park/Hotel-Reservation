#include "./hotel.h"
#include "./constants.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

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

    auto room_number = static_cast<int>(ROOM_TYPE::UNDEFINED);
    auto room_type = static_cast<int>(ROOM_TYPE::UNDEFINED);
    while (getline(infile, line)) {
        sscanf(line.c_str(), "%d : %d", &room_number, &room_type);
        if (room_type == static_cast<int>(ROOM_TYPE::SINGLE)) {
            rooms.push_back(make_unique<single>());
        } 
        else if (room_type == static_cast<int>(ROOM_TYPE::SWEET)) {
            rooms.push_back(make_unique<sweet>());
        }
    }
    infile.close();

    running = true;
}

void hotel::print_info() const {
    for (auto i = 0; i < rooms.size(); ++i) {
        if (rooms[i]->Is_reserved()) {
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

    cout << "************ Reservation ************\n";
    time_t now;
    struct tm* t;
    struct tm S;
    struct tm E;

    time(&now);
    t = localtime(&now);
    S = *t;
    E = *t;

    if (get_reservation_start(S) == -1) {
        return -1;
    }
    if (get_reservation_end(S, E) == -1) {
        return -1;
    }

    S.tm_year -= 1900;
    E.tm_year -= 1900;
    S.tm_mon--;
    E.tm_mon--;

    print_available_rooms(S, E);

    auto n = -1;
    while (true) {
        get_input_with_msg("Enter room number to reserve(-1 to cancle)", n);
        if (n == -1) {
            return -1;
        }
        if (n < 0 || n >= rooms.size()) {
            print_error("Wrong input! Please enter room number properly");
            continue;
        }
        if (rooms[n]->available(S, E, -1)) {
            break;
        }
    }

    rooms[static_cast<int>(n)]->reserve(S, E);
    return 0; // success
}

int hotel::show_reservation_state() const {
    int count = 0;

    cout << "************ Room Reservation State **************\n";
    for (auto i = 0; i < rooms.size(); ++i) {
        if (rooms[static_cast<int>(i)]->Is_reserved()) {
            cout << "Room" << static_cast<int>(i) << endl;
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

void hotel::print_available_rooms(struct tm& S, struct tm& E) const {
    cout << "************ Available rooms list **************\n";

    for (auto i = 0; i < rooms.size(); ++i) {
        if (rooms[static_cast<int>(i)]->available(S, E, -1)) {
            cout << "room[" << static_cast<int>(i) << "]\n";
        }
    }
}
