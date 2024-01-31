#include <iostream>
#include "Keithley.h"

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    system("chcp 1251");
    system("cls");

    Start(13, VOLT, 5.42, 10, 2000);
    Sleep(1000);
    Start(13, CURR, 10, 5, 2000);

    return 0;
}