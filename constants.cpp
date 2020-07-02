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

int get_year(const char* msg, int& year)
{
    while (true) {
        int ret = get_input_with_msg(msg, year);
        if (!ret && (year > 1900 && year <= 9999)) {
            break;
        } else if (ret == -1) {
            return -1;
        }
    }
    return 0;
}

int get_month(const char* msg, int& month)
{
    while (true) {
        int ret = get_input_with_msg(msg, month);
        if (!ret && (month > 0 && month < 13)) {
            break;
        } else if (ret == -1) {
            return -1;
        }
    }
    return 0;
}

bool is_youn_year(int& y)
{
    return (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
}

int get_day(const char* msg, struct tm& R)
{
    while (true) {
        int ret = get_input_with_msg(msg, R.tm_mday);
        if (ret == -1) {
            return -1;
        }

        if (R.tm_mon == 2) {
            if (is_youn_year(R.tm_year)) {
                if (R.tm_mday > 0 && R.tm_mday <= 27) {
                    break;
                }
            }
            else {
                if (R.tm_mday > 0 && R.tm_mday <= 28) {
                    break;
                }
            }
        } else if (R.tm_mon == 1 || R.tm_mon == 3 || R.tm_mon == 5 || R.tm_mon == 7 ||
                    R.tm_mon == 8 || R.tm_mon == 10 || R.tm_mon == 12){
            if (R.tm_mday > 0 && R.tm_mday <= 31) {
                break;
            }
        } else {
            if (R.tm_mday > 0 && R.tm_mday <= 30) {
                break;
            }
        }
    }
    return 0;
}

int get_reservation_start(struct tm& start)
{
    if (get_year("Enter starting year: ", start.tm_year) == -1) {
        return -1;
    }
    // cout << start->tm_year << endl;
    if (get_month("Enter starting month: ", start.tm_mon) == -1) {
        return -1;
    }
    // cout << start->tm_mon << endl;
    if (get_day("Enter starting day: ", start) == -1) {
        return -1;
    }
    // cout << start->tm_mday << endl;

    return 0;
}

int get_reservation_end(struct tm& start, struct tm& end)
{
    cout << "************* Reservation ending date *************\n";
    do {
        if (get_year("Enter ending year: ", end.tm_year) == -1) {
            return -1;
        }
    } while (start.tm_year > end.tm_year);

    do {
        if (get_month("Enter ending month: ", end.tm_mon) == -1) {
            return -1;
        }
        if ((start.tm_year == end.tm_year && start.tm_mon <= end.tm_mon) ||
            (start.tm_year < end.tm_year)) {
            break;
        }
    } while (true);
    // cout << end->tm_mon << endl;

    do {
        if (get_day("Enter ending day: ", end) == -1) {
            return -1;
        }
        if (start.tm_year == end.tm_year) {
            if (start.tm_mon == end.tm_mon) {
                if (start.tm_mday < end.tm_mday) {
                    break;
                }
            } else if (start.tm_mon < end.tm_mon) {
                break;
            } 
        }
    } while (true);



    return 0;
}