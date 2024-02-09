#include <iostream>
#include <locale>
#include "Keithley.hpp"

int main() {
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    //setlocale(LC_ALL, "RUSSIAN");
    system("chcp 1251");
    system("cls");

    Begin();
    /*Keithley a(14);
    while (true) {
        if (a.IsOn()) {
            std::cout << "GOOD\n";
        }
        else {
            std::cout << "BAD\n";
        }
    }*/

    return 0;
}