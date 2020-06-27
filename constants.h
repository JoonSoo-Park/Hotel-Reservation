#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

const int date = 20200611;

int get_single_char(char&);

int get_single_int(int&);

int get_input_with_msg(const char* msg, int& n);

bool check_end_date_validity(int&, int&);

void print_error(const char*);

#endif