#ifndef HOTEL_H
#define HOTEL_H
#include "./room.h"
#include "./handle.h"
#include <vector>
#include <memory>

class hotel {
public:
    hotel() : rooms(), running(false) { initialize(); }

    // disable copy cont, operator=
    hotel(const hotel&) = delete;
    hotel& operator=(const hotel&) = delete;
    
    void initialize();
    void print_info() const;

    int reserve();
    int show_reservation_state() const;
    void modify_reservation();
    void cancle_reservation();

    void exit_program() {
        running = false;
    }
    bool is_running() const {
        return running;
    }
private:
    std::vector<std::unique_ptr<room> > rooms;

    bool running;

    void print_available_rooms(int start, int end) const;
};

#endif