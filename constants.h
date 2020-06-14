#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

const int date = 20200611;

enum MENU_INPUT {
    RESERVATION = 0,
    SHOW_RESERVATION_STATE,
    CANCLE_RESERVATION,
    QUIT,
    ERROR
};

class Menu {
public:
    void print_menu() const {
        puts("*************** MENU *************");
        puts("1. Reservation");
        puts("2. Show Reservation State");
        puts("3. Cancel Reservation");
        puts("-1. quit");
    }

    MENU_INPUT get_input(std::string input) {
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        if (input == "reservation" || input == "1") {
            return MENU_INPUT::RESERVATION;
        }
        else if (input == "show reservation" || 
            input == "showreservation" ||
            input == "2") {
                return MENU_INPUT::SHOW_RESERVATION_STATE;
        }
        else if (input == "cancle reservation" ||
            input == "canclereservation" ||
            input == "3") {
                return MENU_INPUT::CANCLE_RESERVATION;
        }
        else if (input == "quit" || input == "-1") {
            return MENU_INPUT::QUIT;
        }
        return ERROR;
    }
private:

};

int get_input_with_msg(const char* msg, int& n);

#endif