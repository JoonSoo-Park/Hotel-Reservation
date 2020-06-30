#include <bits/stdc++.h>
using namespace std;

typedef struct {
    int year;
    int month;
    int day;
} res_date;

int get_single_int(int& d)
{
    char t;
    int success = scanf("%d", &d);
    while ((t = getchar()) != '\n');

    return success;
}

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

int get_year(int& year)
{
    while (true) {
        int ret = get_input_with_msg("Enter year: ", year);
        if (!ret && (year > 0 && year <= 9999)) {
            break;
        } else if (ret == -1) {
            return -1;
        }
    }
    return 0;
}

int get_month(int& month)
{
    while (true) {
        int ret = get_input_with_msg("Enter month: ", month);
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

int get_day(res_date& R)
{
    while (true) {
        int ret = get_input_with_msg("Enter day: ", R.day);
        if (ret == -1) {
            return -1;
        }

        if (R.month == 2) {
            if (is_youn_year(R.year)) {
                if (R.day > 0 && R.day <= 27) {
                    break;
                }
            }
            else {
                if (R.day > 0 && R.day <= 28) {
                    break;
                }
            }
        } else if (R.month == 1 || R.month == 3 || R.month == 5 || R.month == 7 ||
                    R.month == 8 || R.month == 10 || R.month == 12){
            if (R.day > 0 && R.day <= 31) {
                break;
            }
        } else {
            if (R.day > 0 && R.day <= 30) {
                break;
            }
        }
    }
    return 0;
}

res_date get_reservation_start()
{
    res_date start{0, 0, 0};

    get_year(start.year);
    get_month(start.month);
    get_day(start);

    return start;
}

res_date get_reservation_end(res_date& start)
{
    res_date end{0, 0, 0};

    do {
        get_year(end.year);
    } while (start.year > end.year);

    do {
        get_month(end.month);
        if ((end.year == start.year && end.month >= start.month) ||
            (end.year > start.year)) {
                break;
        }
    } while (true);

    do {
        get_day(end);
        if ((start.month == end.month && start.day < end.day) || 
            (start.month < end.month)) {
                break;
        }
    } while (true);

    return end;
}

void print_res_date(res_date& res)
{
    cout << "year: " << res.year << endl;
    cout << "month: " << res.month << endl;
    cout << "day: " << res.day << endl;
}

int main()
{
    res_date start = get_reservation_start();
    res_date end = get_reservation_end(start);

    print_res_date(start);
    print_res_date(end);
}