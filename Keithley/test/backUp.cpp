#include <iostream>
#include <Windows.h>

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    system("chcp 1251");
    system("cls");
    HANDLE hPort;
    char buffer[256]{ 0 };
    DWORD bytesRead;
    DWORD bytesWritten;

    TCHAR comname[100];
    wsprintf(comname, TEXT("\\\\.\\COM%d"), 13);

    // Открытие COM-порта
    hPort = CreateFileW(comname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hPort == INVALID_HANDLE_VALUE)
    {
        std::wcout << L"Ошибка открытия COM-порта" << std::endl;
        return 1;
    }

    /*COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;*/

    // Установка конфигурации COM-порта
    DCB dcb;
    GetCommState(hPort, &dcb);
    dcb.BaudRate = CBR_57600;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity = NOPARITY;
    SetCommState(hPort, &dcb);

    //const char* RST = "*RST\n";
    //WriteFile(hPort, RST, strlen(RST), &bytesWritten, NULL);

    // Выставление напряжения и тока
    const char* setVolt = "SOUR:VOLT 5\n";
    const char* setCurr = "SENS:CURR:PROT 30E-3\n";
    WriteFile(hPort, setVolt, strlen(setVolt), &bytesWritten, NULL);
    WriteFile(hPort, setCurr, strlen(setCurr), &bytesWritten, NULL);

    const char* outOn = "OUTP ON\n";
    WriteFile(hPort, outOn, strlen(outOn), &bytesWritten, NULL);

    //Sleep(2500);

    const char* readCommand = "READ?\n";

    for (int i = 0; i < 11; i++) {
        WriteFile(hPort, readCommand, strlen(readCommand), &bytesWritten, NULL);
        ReadFile(hPort, buffer, sizeof(buffer), &bytesRead, NULL);

        std::cout << "VCC = ";
        for (int j = 0; j < 13; j++) {
            std::cout << buffer[j];
        }
        std::cout << " ||| ";
        std::cout << "ICC = ";
        for (int j = 15; j < 27; j++) {
            std::cout << buffer[j];
        }
        std::cout << std::endl;        

        Sleep(200);
        memset(&buffer[0], 0, sizeof(buffer));
    }

    const char* outOff = "OUTP OFF\n";
    WriteFile(hPort, outOff, strlen(outOff), &bytesWritten, NULL);



    // Закрытие COM-порта
    CloseHandle(hPort);

    return 0;
}