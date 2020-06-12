#ifndef ROOM_H
#define ROOM_H

#include <stdio.h>
#include <vector>
#include "./constants.h"

typedef struct {
    int start_date;
    int end_date;
} reserved_date;

class room {
public:
    room() : price(1.0), reserve_start_date(0), reserve_end_date(0), is_reserved(false) { }
    virtual double get_price() const {
        return price;
    }
    int get_reserve_end_date() const {
        return reserve_end_date;
    }
    void reserve(int start, int end);
    bool available(int start, int end) const;
    void show_reservation_state() const;
    virtual room* clone() const {
        return new room(*this);
    }
    operator bool() const {
        return is_reserved;
    }
private:
    double price;
    int reserve_start_date;
    int reserve_end_date;
    bool is_reserved;
    std::vector<reserved_date> dates; 
};

class single : public room {
public:
    double get_price() const {
        return room::get_price() * 1.0;
    }
    virtual single* clone() const {
        return new single(*this);
    }
private:
};

class sweet : public room {
public:
    double get_price() const {
        return room::get_price() * 3.5;
    }
    virtual sweet* clone() const {
        return new sweet(*this);
    }
private:
};

#endif