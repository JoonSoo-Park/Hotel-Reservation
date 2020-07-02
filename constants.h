#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

int get_single_char(char&);

int get_single_int(int&);

int get_input_with_msg(const char* msg, int& n);

bool check_end_date_validity(int&, int&);

void print_error(const char*);

int get_year(const char*, int&);

int get_month(const char*, int&);

bool is_youn_year(int&);

int get_day(const char*, struct tm&);

int get_reservation_start(struct tm&);

int get_reservation_end(struct tm&, struct tm&);

#endif