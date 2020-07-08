#include "./Reservation.h"
#include "./constants.h"
#include <iostream>
#include <sstream>
#include <ios>
#include <plog/Log.h>

using std::cout;
using std::vector;
using std::ios;
using std::string;
using std::ostringstream;

Reservation::Reservation(int rn, struct tm& S, struct tm& E) : room_number(rn) 
{
    Initialize();
    Reserve(S, E);
}

void Reservation::Initialize()
{
    time_t rawtime;
    struct tm* t;

    time(&rawtime);    
    t = localtime(&rawtime);
    start_info = *t;
    end_info = *t;
}

void Reservation::Reserve(struct tm& S, struct tm& E)
{
    start_info.tm_year = S.tm_year;
    start_info.tm_mon = S.tm_mon;
    start_info.tm_mday = S.tm_mday;
    start_info.tm_hour = 14;
    start_info.tm_min = 0;
    start_info.tm_sec = 0;

    end_info.tm_year = E.tm_year;
    end_info.tm_mon = E.tm_mon;
    end_info.tm_mday = E.tm_mday;
    end_info.tm_hour = 10;
    end_info.tm_min = 0;
    end_info.tm_sec = 0;

    mktime(&start_info);
    mktime(&end_info);

    Print_Log();
}

void Reservation::Modify(struct tm& S, struct tm& E)
{
    time_t now;
    time(&now);
    struct tm* t = localtime(&now);
    struct tm new_S = *t;
    struct tm new_E = *t;

    string log = Get_Log();
    string modified_log;

    start_info.tm_year = S.tm_year - 1900;
    start_info.tm_mon = S.tm_mon - 1;
    start_info.tm_mday = S.tm_mday;

    end_info.tm_year = E.tm_year - 1900;
    end_info.tm_mon = E.tm_mon - 1;
    end_info.tm_mday = E.tm_mday;

    mktime(&start_info);
    mktime(&end_info);

    modified_log = Get_Log();
    PLOGI << "\n\troom[" << room_number << "] modified: " << log << " -> " << modified_log;
}

void Reservation::Print() const 
{
    char buffer[100];

    strftime(buffer, sizeof(buffer), "%Y-%m-%d(%a)", &start_info);
    printf("%s ~ ", buffer);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d(%a)", &end_info);
    printf("%s\n", buffer);
}

void Reservation::Print_Log() const
{
    char buffer[100];
    char buffer2[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d(%a)", &start_info);
    strftime(buffer2, sizeof(buffer2), "%Y-%m-%d(%a)", &end_info);
    PLOGI << "\n\troom[" << room_number << "] reserved: " << buffer << " ~ " << buffer2;
}

string Reservation::Get_Log()
{
    ostringstream ret{ios::ate};

    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d(%a)", &start_info);
    ret << buffer << " ~ ";
    strftime(buffer, sizeof(buffer), "%Y-%m-%d(%a)", &end_info);
    ret << buffer;

    return ret.str();
}

bool Reservation::compare(Reservation& a, Reservation& b)
{
    if (a.start_info.tm_year < b.start_info.tm_year) {
        return true;
    } else if (a.start_info.tm_year > b.start_info.tm_year) {
        return false;
    } else { // same year
        if (a.start_info.tm_mon < b.start_info.tm_mon) {
            return true;
        } else if (a.start_info.tm_mon > b.start_info.tm_mon) {
            return false;
        } else { // same month
            if (a.start_info.tm_mday < b.start_info.tm_mday) {
                return true;
            } else if (a.start_info.tm_mday > b.start_info.tm_mday) {
                return false;
            }
        }
    }

    // if start-date is same, then compare ending date
    if (a.end_info.tm_year < b.end_info.tm_year) {
        return true;
    } else if (a.end_info.tm_year > b.end_info.tm_year) {
        return false;
    } else { // same year
        if (a.end_info.tm_mon < b.end_info.tm_mon) {
            return true;
        } else if (a.end_info.tm_mon > b.end_info.tm_mon) {
            return false;
        } else { // same month
            if (a.end_info.tm_mday < b.end_info.tm_mday) {
                return true;
            } else if (a.end_info.tm_mday > b.end_info.tm_mday) {
                return false;
            }
        }
    }

    // if they same start and end, then I don't know
    return true;
}