#ifndef HOTEL_H
#define HOTEL_H
#include "./room.h"
#include "./handle.h"
#include <vector>

class hotel {
public:
    hotel() : rooms(10), running(true) { initialize(); }
    
    void initialize();
    void print_info() const;
    int reserve();
    void show_reservation_state() const;
    void exit_program() {
        running = false;
    }
    bool is_running() const {
        return running;
    }
private:
    // std::vector<room*> rooms;
    std::vector<Handle<room> > rooms;
    bool running;

    void print_available_rooms(int start, int end) const;
};

#endif