#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <plog/Log.h>
#include "./hotel.h"
#include "./Menu.h"

using namespace std;

void do_work(hotel* hot, MENU_INPUT m)
{
    switch (m)
    {
    case MENU_INPUT::RESERVATION:
        PLOGI << "Reservation";
        system("clear");
        if (hot->reserve() == -1) {
            PLOGI << "Cancled";
        }
        system("clear");
        break;
    case MENU_INPUT::SHOW_RESERVATION_STATE:
        PLOGI << "Show Reservation";
        system("clear");
        if (hot->show_reservation_state() == -1) {
            PLOGI << "Cancled";
        }
        break; 
    case MENU_INPUT::MODIFY_RESERVATION:
        PLOGI << "Modify Reservation";
        system("clear");
        if (hot->modify_reservation() == -1) {
            PLOGI << "Cancled";
        }
        system("clear");
        break;
    case MENU_INPUT::CANCLE_RESERVATION:
        PLOGI << "Cancle Reservation";
        system("clear");
        if (hot->cancle_reservation() == -1) {
            PLOGI << "Cancled";
        }
        system("clear");
        break;
    case MENU_INPUT::QUIT:
        PLOGI << "Quit";
        puts("Exiting program");
        hot->exit_program();
        break;
    case MENU_INPUT::ERROR:
    default:
        break;
    }
}

int main()
{
    auto hot = new hotel();
    auto menu = new Menu();

    plog::init(plog::verbose, "Log.txt");

    while (hot->is_running()) {
        string input;
        MENU_INPUT m;

        menu->print_menu();
        printf(">> ");
        cin >> input;

        try {
            m = menu->get_input(input);
            do_work(hot, m);
        } catch (std::invalid_argument e) {
            puts("wrong input!\ninput should be numbers");
        } catch (std::runtime_error e) {
            cout << e.what() << endl;
        } catch (std::domain_error e) {
            cout << e.what() << endl;
        } catch (std::exception e) {
            cout << e.what() << endl;
        }

        cout << endl;
    }

    delete menu;
}