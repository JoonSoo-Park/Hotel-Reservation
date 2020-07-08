#ifndef RESERVATION_H
#define RESERVATION_H
#include <vector>
#include <ctime>
#include <vector>
#include <string>

class Reservation {
public:
    Reservation() = delete;
    Reservation(int, struct tm&, struct tm&);

    void Modify(struct tm&, struct tm&);
    void Print() const;
    time_t MktimeS() {
        return mktime(&start_info);
    }
    time_t MktimeE() {
        return mktime(&end_info);
    }
    std::string Get_Log();
    
    static bool compare(Reservation& a, Reservation& b);
private:
    int room_number;
    struct tm start_info;
    struct tm end_info;

    void Initialize();
    void Reserve(struct tm&, struct tm&);
    void Print_Log() const;
};


#endif