#pragma once
#include <iostream>
#include <windows.h>

#define BAUD_RATE CBR_9600;
#define BYTE_SIZE 8;
#define STOP_BITS ONESTOPBIT;
#define PARITY NOPARITY;

typedef HANDLE PORT;

PORT openCOMPort(const char* portName);

bool configureCOMPort(PORT hSerial);

bool writeCOMPort(PORT hSerial, const char* data, int size);

bool readCOMPort(PORT hSerial, const char* data, int size, DWORD& dwBytesRead);

bool closeCOMPort(PORT hSerial);