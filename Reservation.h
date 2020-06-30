#ifndef RESERVATION_H
#define RESERVATION_H
#include <vector>
#include <ctime>

typedef struct res_date;

class Reservation {
public:
    Reservation() = delete;
    Reservation(res_date, res_date);
    ~Reservation() {
        delete start_info;
        delete end_info;
    }

    Reservation& operator=(const Reservation&) = delete;
    Reservation(const Reservation&) = delete;

    void Modify(res_date, res_date);
    void Print() const;
    std::vector<time_t> Mktime() const;
private:
    // 예약 내용
    struct tm* start_info;
    struct tm* end_info;
    res_date start_date;
    res_date end_date;

    void Initialize();
    void Reserve();
};

#endif