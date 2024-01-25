#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <functional>
#include <algorithm>
#include <cstring>

// ������ �������� �����
#define BAUD_RATE_9600 CBR_9600;
#define BAUD_RATE_57600 CBR_57600;
#define BYTE_SIZE 8;
#define STOP_BITS ONESTOPBIT;
#define PARITY NOPARITY;

#define VOLT "VOLT"
#define CURR "CURR"

typedef HANDLE PORT;

class Keithley {
protected:
	PORT device;
	char ReadBuffer[256] = { NULL };
public:
	Keithley(int port) {
		device = OpenPort(port);
	}
	~Keithley() {
		ClosePort();
	}

	PORT GetPort() {
		return device;
	}

	// ������� ����
	PORT OpenPort(int portName);

	// ��������� ����
	bool ConfigPort();

	bool SetBaudRate(int BaudRate);

	bool SetByteSize(int ByteSize);

	bool SetStopBits(int StopBits);

	bool SetParity(int Parity);

	// ������� ������
	bool WriteToPort(const char* data);

	// �����
	bool RST();

	// �������� �����
	bool OutputOn();

	// ��������� �����
	bool OutputOff();

	// ����� ������
	bool SetFunc(const char* data);

	// �������� ����������
	// 
	// ���������� �������� ����������
	bool SetVolt(double value);

	// ���������� �������� ������ ����
	bool SetCurrProt(double value);


	// �������� ����
	// 
	// ���������� �������� ����
	bool SetCurr(double value);

	// ���������� �������� ������ ����������
	bool SetVoltProt(double value);

	// ������� ����������� �� �������
	char* DisplayVolts();

	char* DisplayCurr();

	// ������� ������
	char* ReadVolt();

	char* ReadCurr();

	std::string ReadFromPort();

	// ����� �� ������� �������� Vcc & Icc
	void PrintRead();

	// ������� ����
	bool ClosePort();
};