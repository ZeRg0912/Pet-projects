#include <iostream>
#include "Keithley.h"

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    system("chcp 1251");
    system("cls");

    PORT Keithley = OpenPort(13);
    
    ConfigPort(Keithley);
    SetFunc(Keithley, VOLT);
    SetVolt(Keithley, 5);
    SetCurrProt(Keithley, 50);
    OutputOn(Keithley);

    PrintRead(ReadFromPort(Keithley));

    return 0;
}