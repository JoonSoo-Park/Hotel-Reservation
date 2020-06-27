#include "./constants.h"
#include <iostream>

using std::cout;
using std::endl;

int get_input_with_msg(const char* msg, int& n)
{
    int success;
    char c;

    do {
        cout << msg;

        success = get_single_int(n);

        if (!success) continue;
        if (n == -1) return -1;
    } while (!success);

    return 0; // when success;
}

int get_single_int(int& d)
{
    char t;
    int success = scanf("%d", &d);
    while ((t = getchar()) != '\n');

    return success;
}

int get_single_char(char& c)
{
    char t;
    int success = scanf("%c", &c);
    while ((t = getchar()) != '\n');

    return success;
}

bool check_end_date_validity(int& start_date, int& end_date)
{
    return start_date < end_date;
}

void print_error(const char* msg)
{
    cout << "Error: " << msg << "!!" << endl;

    return;
}