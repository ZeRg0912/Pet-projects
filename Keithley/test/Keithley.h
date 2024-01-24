#pragma once
#include <iostream>
#include <windows.h>

// Базовы значения порта
#define BAUD_RATE CBR_9600;
#define BYTE_SIZE 8;
#define STOP_BITS ONESTOPBIT;
#define PARITY NOPARITY;

#define VOLT "VOLT"
#define CURR "CURR"

typedef HANDLE PORT;

// Открыть порт
PORT OpenPort(int portName);

// Настроить порт
bool ConfigPort(PORT SerialPort);

bool SetBaudRate(PORT SerialPort, int BaudRate);

bool SetByteSize(PORT SerialPort, int ByteSize);

bool SetStopBits(PORT SerialPort, int StopBits);

bool SetParity(PORT SerialPort, int Parity);

// Команда записи
bool WriteToPort(PORT SerialPort, const char* data);

// Сброс
bool RST(PORT SerialPort);

// Включить выход
bool OutputOn(PORT SerialPort);

// Выключить выход
bool OutputOff(PORT SerialPort);

// Выбор режима
bool SetFunc(PORT SerialPort, const char* data);

// ИСТОЧНИК НАПРЯЖЕНИЯ
// 
// Установить значение напряжения
bool SetVolt(PORT SerialPort, int value);

// Установить значение лимита тока
bool SetCurrProt(PORT SerialPort, int value);


// ИСТОЧНИК ТОКА
// 
// Установить значение тока
bool SetVolt(PORT SerialPort, double value);

// Установить значение лимита напряжения
bool SetCurrProt(PORT SerialPort, int value);

// Команда чтения
char* ReadFromPort(PORT SerialPort, const char* data);

// Вывод на консоль значений Vcc & Icc
void PrintRead(char* buffer);

// Закрыть порт
bool closePort(PORT SerialPort);