#ifndef HOTEL_H
#define HOTEL_H
#include "./room.h"
#include "./handle.h"
#include <vector>

class hotel {
public:
    hotel() : rooms(), running(false) { initialize(); }
    hotel(const hotel&) = delete;
    hotel& operator=(const hotel&) = delete;
    
    void initialize();
    void print_info() const;
    int reserve();
    void modify_reservation();
    void cancle_reservation();
    int show_reservation_state() const;
    void exit_program() {
        running = false;
    }
    bool is_running() const {
        return running;
    }
private:
    std::vector<Handle<room> > rooms;
    bool running;

    void print_available_rooms(int start, int end) const;
};

#endif