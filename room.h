#ifndef ROOM_H
#define ROOM_H

#include <stdio.h>
#include "./constants.h"

class room {
public:
    room() : price(1.0), reserve_start_date(0), reserve_end_date(0), booked(false) { }
    virtual double get_price() const {
        return price;
    }
    int get_reserve_end_date() const {
        return reserve_end_date;
    }
    void reserve(int start, int end);
    bool available(int start, int end) const;
    operator bool() const {
        return booked;
    }
private:
    double price;
    int reserve_start_date;
    int reserve_end_date;
    bool booked;
};

class single : public room {
public:
    double get_price() const {
        return room::get_price() * 1.0;
    }
private:
};

class sweet : public room {
public:
    double get_price() const {
        return room::get_price() * 3.5;
    }
private:
};

#endif