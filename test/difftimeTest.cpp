#include <bits/stdc++.h>
using namespace std;

int main()
{
    time_t now;
    time(&now);
    struct tm* t = localtime(&now);

    struct tm S = *t;
    struct tm E = *t;

    S.tm_year = 3000;

    printf("%.f\n", difftime(mktime(&S), mktime(&E)));
}