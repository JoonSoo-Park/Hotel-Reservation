#include "./Reservation.h"
#include "./constants.h"
#include <iostream>

using std::cout;
using std::vector;

Reservation::Reservation(res_date s, res_date e) : start_date(s), end_date(e) {
    Initialize();
    Reserve();
}

void Reservation::Initialize()
{
    time_t rawtime;

    time(&rawtime);    
    start_info = localtime(&rawtime);
    end_info = start_info;
}

void Reservation::Reserve()
{
    start_info->tm_year = start_date.year - 1900;
    start_info->tm_mon = start_date.month - 1;
    start_info->tm_mday = start_date.day;
    start_info->tm_hour = 14;
    start_info->tm_min = 0;
    start_info->tm_sec = 0;


    end_info->tm_year = end_date.year - 1900;
    end_info->tm_mon = end_date.month - 1;
    end_info->tm_mday = end_date.day;
    end_info->tm_hour = 10;
    end_info->tm_min = 0;
    end_info->tm_sec = 0;
}

void Reservation::Modify(res_date s, res_date e)
{
    start_info->tm_year = s.year - 1900;
    start_info->tm_mon = s.month - 1;
    start_info->tm_mday = s.day;

    end_info->tm_year = e.year - 1900;
    end_info->tm_mon = e.month - 1;
    end_info->tm_mday = e.day;
}

void Reservation::Print() const 
{
    char buffer[100];

    strftime(buffer, sizeof(buffer), "%Y-%m-%d(%a)", start_info);
    printf("%s ~ ", buffer);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d(%a)", end_info);
    printf("%s\n", buffer);
}

vector<time_t> Reservation::Mktime() const
{
    vector<time_t> ret;
    ret.push_back(mktime(start_info));
    ret.push_back(mktime(end_info));

    return ret;
}