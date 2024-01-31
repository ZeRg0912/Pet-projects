#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <functional>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <sstream>

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

void Start(int numPort, std::string Source, float SourceValue, float ProtValue, int Cycles);

class Keithley {
protected:
	PORT device;
	char ReadBuffer[2048] = { NULL };
	char Command[2048] = { NULL };
public:
	Keithley(){
	//device = OpenPort(port);
	}
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

	// �������� �����
	bool ResetTime();

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
	bool SetReadSpeed(float value);

	// �������� ����������
	// 
	// ���������� �������� ����������
	bool SetVolt(float value);

	// ���������� �������� ������ ����
	bool SetCurrProt(float value);


	// �������� ����
	// 
	// ���������� �������� ����
	bool SetCurr(float value);

	// ���������� �������� ������ ����������
	bool SetVoltProt(float value);

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