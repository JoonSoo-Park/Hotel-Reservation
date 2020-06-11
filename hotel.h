#ifndef HOTEL_H
#define HOTEL_H
#include "./room.h"
#include <vector>

class hotel {
public:
    hotel() : rooms(10), running(true) { initialize(); }
    ~hotel() {
        for (int i = 0; i < 10; ++i)
            delete rooms[i];
    }
    void initialize();
    void print_info() const;
    int reserve();
    bool is_running() const {
        return running;
    }
private:
    std::vector<room*> rooms;
    bool running;

    void print_available_rooms(int start, int end) const;
};

#endif