#include <iostream>
#include "Keithley.h"

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    system("chcp 1251");
    system("cls");

    Keithley device1(13);
    device1.ConfigPort();
    device1.SetFunc(VOLT);
    device1.SetVolt(5.4262);
    device1.SetCurrProt(10);
    device1.SetReadSpeed(0.01);
    device1.ResetTime();
    device1.OutputOn();
    Sleep(300);

    device1.ReadVoltCurr(2000);

    device1.OutputOff();

    device1.ClosePort();

    return 0;
}