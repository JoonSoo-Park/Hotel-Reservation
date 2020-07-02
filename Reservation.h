#ifndef RESERVATION_H
#define RESERVATION_H
#include <vector>
#include <ctime>

class Reservation {
public:
    Reservation() = delete;
    Reservation(struct tm&, struct tm&);

    void Modify(struct tm&, struct tm&);
    void Print() const;
    time_t MktimeS() {
        return mktime(&start_info);
    }
    time_t MktimeE() {
        return mktime(&end_info);
    }
    
    static bool compare(Reservation& a, Reservation& b);
private:
    // 예약 내용
    struct tm start_info;
    struct tm end_info;

    void Initialize();
    void Reserve(struct tm&, struct tm&);
};


#endif