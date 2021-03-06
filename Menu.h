#ifndef MENU_H
#define MENU_H
#include <cctype>
#include <string>
#include <algorithm>

enum class MENU_INPUT {
    RESERVATION = 1,
    SHOW_RESERVATION_STATE,
    MODIFY_RESERVATION,
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
        puts("3. Modify Reservation");
        puts("4. Cancel Reservation");
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
        else if (input == "modify reservation" ||
            input == "modifyreservation" ||
            input == "3") {
                return MENU_INPUT::MODIFY_RESERVATION;
        }
        else if (input == "cancle reservation" ||
            input == "canclereservation" ||
            input == "4") {
                return MENU_INPUT::CANCLE_RESERVATION;
        }
        else if (input == "quit" || input == "-1") {
            return MENU_INPUT::QUIT;
        }
        return MENU_INPUT::ERROR;
    }
private:

};

#endif