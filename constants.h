#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

typedef struct {
    int year;
    int month;
    int day;
} res_date;

int get_single_char(char&);

int get_single_int(int&);

int get_input_with_msg(const char* msg, int& n);

bool check_end_date_validity(int&, int&);

void print_error(const char*);

int get_year(int&);

int get_month(int&);

bool is_youn_year(int&);

int get_day(res_date&);

#endif