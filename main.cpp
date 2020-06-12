#include <iostream>
#include <vector>
#include <stdexcept>
#include "./hotel.h"

using namespace std;

void do_work(hotel* hot, MENU_INPUT m)
{
    switch (m)
    {
    case MENU_INPUT::RESERVATION:
        hot->reserve();
        break;
    case MENU_INPUT::SHOW_RESERVATION_STATE:
        hot->show_reservation_state();
        break; 
    case MENU_INPUT::CANCLE_RESERVATION:
        break;
    case MENU_INPUT::QUIT:
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
    hotel* hot = new hotel();
    Menu* menu = new Menu();

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