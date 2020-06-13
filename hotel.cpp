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

// TODO: 오류 처리... 정수 외 입력 시 segmentation fault
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
    puts("************ Cancle Reservation **************");
    show_reservation_state();

}

void hotel::print_available_rooms(int start, int end) const {
    printf("************ Available rooms list **************\n");

    for (vector<room*>::size_type i = 0; i < rooms.size(); ++i) {
        if (rooms[i]->available(start, end)) {
            printf("room[%d]\n", static_cast<int>(i));
        }
    }
}

void hotel::show_reservation_state() const {
    int count = 0;

    puts("************ Room Reservation State **************");
    for (vector<room*>::size_type i = 0; i < rooms.size(); ++i) {
        if (rooms[i]) {
            cout << "room" << static_cast<int>(i) << endl;
            rooms[i]->show_reservation_state();
            cout << endl;
            count++;
        }
    } 
    if (count == 0) {
        puts("No room is reserved");
    }
}

int hotel::get_input_with_msg(const char* msg, int& n)
{
    bool success = false;
    char c;

    do {
        printf("%s", msg);
        success = scanf("%d", &n);
        while ((c = getchar()) != '\n');
        if (!success) continue;
        if (n == -1) return -1;
    } while (!success);

    return 0; // when success;
}