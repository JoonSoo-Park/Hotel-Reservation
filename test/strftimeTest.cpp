#include <bits/stdc++.h>
using namespace std;

int main() 
{
    time_t rawtime;
    struct tm* start_info;
    struct tm* end_info;

    time(&rawtime);    
    start_info = localtime(&rawtime);
    end_info = start_info;

    char buffer[100];

    strftime(buffer, sizeof(buffer), "%Y-%m-%d(%a)", start_info);
    printf("%s ~ ", buffer);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d(%a)", end_info);
    printf("%s\n", buffer);
}