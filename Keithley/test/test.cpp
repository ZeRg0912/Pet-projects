#include <iostream>
#include "Keithley.h"

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    system("chcp 1251");
    system("cls");

    //Init(13, VOLT, -5, 10, 100);
    //Sleep(1000);
    //Init(13, CURR, 10, 5, 2000);
    Begin();

    return 0;
}