#include "./hotel.h"
#include <iostream>

using namespace std;

void hotel::initialize() {
    rooms[0] = new sweet();
    rooms[1] = new single();
    rooms[2] = new single();
    rooms[3] = new sweet();
    rooms[4] = new sweet();
    rooms[5] = new sweet();
    rooms[6] = new single();
    rooms[7] = new single();
    rooms[8] = new single();
    rooms[9] = new single();
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
    printf("Enter starting date, end date: ");
    scanf("%d %d", &start, &end);
    print_available_rooms(start, end);

    int n;
    printf("Enter room number to reserve: ");
    scanf("%d", &n);
}

void hotel::print_available_rooms(int start, int end) const {
    printf("************ Available rooms list **************\n");

    for (vector<room*>::size_type i = 0; i < rooms.size(); ++i) {
        if (rooms[i]->available(start, end)) {
            printf("room[%d]\n", static_cast<int>(i));
        }
    }
}