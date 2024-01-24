#pragma once
#include <iostream>
#include <windows.h>

// ������ �������� �����
#define BAUD_RATE CBR_9600;
#define BYTE_SIZE 8;
#define STOP_BITS ONESTOPBIT;
#define PARITY NOPARITY;

#define VOLT "VOLT"
#define CURR "CURR"

typedef HANDLE PORT;

// ������� ����
PORT OpenPort(int portName);

// ��������� ����
bool ConfigPort(PORT SerialPort);

bool SetBaudRate(PORT SerialPort, int BaudRate);

bool SetByteSize(PORT SerialPort, int ByteSize);

bool SetStopBits(PORT SerialPort, int StopBits);

bool SetParity(PORT SerialPort, int Parity);

// ������� ������
bool WriteToPort(PORT SerialPort, const char* data);

// �����
bool RST(PORT SerialPort);

// �������� �����
bool OutputOn(PORT SerialPort);

// ��������� �����
bool OutputOff(PORT SerialPort);

// ����� ������
bool SetFunc(PORT SerialPort, const char* data);

// �������� ����������
// 
// ���������� �������� ����������
bool SetVolt(PORT SerialPort, int value);

// ���������� �������� ������ ����
bool SetCurrProt(PORT SerialPort, int value);


// �������� ����
// 
// ���������� �������� ����
bool SetVolt(PORT SerialPort, double value);

// ���������� �������� ������ ����������
bool SetCurrProt(PORT SerialPort, int value);

// ������� ������
char* ReadFromPort(PORT SerialPort, const char* data);

// ����� �� ������� �������� Vcc & Icc
void PrintRead(char* buffer);

// ������� ����
bool closePort(PORT SerialPort);