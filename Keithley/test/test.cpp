#include <iostream>
#include "Keithley.h"

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    system("chcp 1251");
    system("cls");

    Keithley device1(13);
    
    device1.ConfigPort();
    device1.SetFunc(VOLT);
    device1.SetVolt(10);
    device1.SetCurrProt(50);
    device1.OutputOn();
    Sleep(50);

    for (int i = 0; i < 10; i++) {
        device1.ReadFromPort();
        Sleep(10);
        device1.PrintRead();
        Sleep(190);
    }

    device1.OutputOff();

    device1.ClosePort();

    return 0;
}