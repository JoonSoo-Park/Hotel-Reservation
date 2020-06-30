#include "./Reservation.h"
#include "./constants.h"
#include <iostream>

using std::cout;
using std::endl;

void Reservation::Initialize()
{
    time_t rawtime;

    time(&rawtime);    
    time_info = localtime(&rawtime);
}

void Reservation::Reserve(int year, int month, int day)
{
    time_info->tm_year = year - 1900;
    time_info->tm_mon = month - 1;
    time_info->tm_mday = day;
    time_info->tm_hour = 14;
    time_info->tm_min = 0;
    time_info->tm_sec = 0;
}

void Reservation::Modify()
{

}

void Reservation::Print() const 
{
    char buffer[100];

    strftime(buffer, sizeof(buffer), 
            "%Y-%m-%d/%a ~ %Y-%m-%d/%a", time_info);
}