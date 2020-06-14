#include "./constants.h"

int get_input_with_msg(const char* msg, int& n)
{
    bool success = false;
    char c;

    do {
        printf("%s", msg);
        success = scanf("%d", &n);
        while ((c = getchar()) != '\n');
        if (!success) continue;
        if (n == -1) return -1;
    } while (!success);

    return 0; // when success;
}