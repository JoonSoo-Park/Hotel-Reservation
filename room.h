#ifndef ROOM_H
#define ROOM_H
#include <stdio.h>
#include <vector>
#include <memory>

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

    virtual void reserve(int start, int end);
    virtual void show_reservation_state() const;
    int modify_reservation();
    void cancle_reservation();

    bool available(int start, int end) const;
    bool Is_reserved() const noexcept {
        return is_reserved;
    }

    virtual std::unique_ptr<room> clone() const {
        return std::make_unique<room>(*this);
    }

private:
    double price;
    int reserve_start_date;
    int reserve_end_date;
    bool is_reserved;
    std::vector<reserved_date> dates; 

    bool check_date_validity(int, int);
    void modify_dates(int, int, int);

    static bool compare_reservation(reserved_date& r1, reserved_date& r2) {
        return r1.start_date < r2.start_date;
    }
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