#ifndef RESERVATION_H
#define RESERVATION_H

#include <ctime>

class Reservation {
public:
    Reservation() : time_info(nullptr) {
        Initialize();
    }
    Reservation(int year, int month, int day) : time_info(nullptr) { 
        Initialize();
        Reserve(year, month, day);
    }
    ~Reservation() {
        delete time_info;
    }
    void Initialize();
    void Reserve(int, int, int);
    void Modify();
    void Print() const;
private:
    // 예약 내용
    time_t t;
    struct tm* time_info;
};

#endif