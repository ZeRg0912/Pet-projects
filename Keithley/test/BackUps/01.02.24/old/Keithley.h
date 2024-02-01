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
#define RES "RES"

typedef HANDLE PORT;

class Keithley {
protected:
	PORT device;
	char ReadBuffer[2048] = { NULL };
public:
	Keithley(int port) : device(OpenPort(port)) {
		//device = OpenPort(port);
	}
	~Keithley() {
		//delete[] ReadBuffer;
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
	
	// ������� ������
	bool ReadFromPort();

	// �����
	bool RST();

	// �������� �����
	bool OutputOn();

	// ��������� �����
	bool OutputOff();

	// ����� ������
	bool SetFunc(std::string data);

	// ��������� �������� ������
	bool SetReadSpeed(double value);

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

	std::string ReadVoltCurr(int num);

	// ����� �� ������� �������� Vcc & Icc
	void PrintRead();

	// ������� ����
	bool ClosePort();
};