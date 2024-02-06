#include <iostream>
//#include <locale>
#include "Keithley.hpp"

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "RUSSIAN");
    system("chcp 1251");
    system("cls");

    Begin();

    return 0;
}