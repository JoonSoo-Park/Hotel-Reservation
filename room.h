#ifndef ROOM_H
#define ROOM_H
#include <stdio.h>
#include <vector>
#include <memory>
#include "./Reservation.h"

class room {
public:
    room() : price(1.0), is_reserved(false) { }

    virtual double get_price() const {
        return price;
    }

    virtual void reserve(int, struct tm&, struct tm&);
    virtual void show_reservation_state() const;
    int modify_reservation();
    void cancle_reservation(int);

    bool available(struct tm&, struct tm&, int);
    bool Is_reserved() const noexcept {
        return is_reserved;
    }

    virtual std::unique_ptr<room> clone() const {
        return std::make_unique<room>(*this);
    }

private:
    double price;
    bool is_reserved;
    std::vector<Reservation> reservations;

    bool check_date_validity(struct tm, int);
    bool check_date_validity(struct tm&, struct tm&);
};

class single : public room {
public:
    double get_price() const override {
        return room::get_price() * 1.0;
    }

    virtual std::unique_ptr<room> clone() const override {
        return std::make_unique<single>(*this);
    }
private:
};

class sweet : public room {
public:
    double get_price() const override {
        return room::get_price() * 3.5;
    }

    virtual std::unique_ptr<room> clone() const override {
        return std::make_unique<sweet>(*this);
    }
private:
};

#endif