#include <iostream>
#include <vector>
#include "./hotel.h"

using namespace std;

int main()
{
    hotel* hot = new hotel();

    while (hot->is_running()) {
        hot->reserve();
    }
}