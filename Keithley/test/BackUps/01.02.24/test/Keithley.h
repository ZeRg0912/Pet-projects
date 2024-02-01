#pragma once
#include <iostream>
#include <limits>
#include <windows.h>
#include <string>
#include <functional>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <variant>

// ������ �������� �����
#define BAUD_RATE_9600 CBR_9600;
#define BAUD_RATE_57600 CBR_57600;
#define BYTE_SIZE 8;
#define STOP_BITS ONESTOPBIT;
#define PARITY NOPARITY;

#define VOLT "VOLT"
#define CURR "CURR"
#define RES "RES"

#if defined(max)
#undef max
#endif

typedef HANDLE PORT;

void setcur(int x, int y);

void Begin();

void Init(int numPort, std::string Source, float SourceValue, float ProtValue, int Cycles);

template <typename T>
T getInput(const std::string& hint, bool positive_only = false) {
	T input;
	system("cls");
	while (true) {
		std::cout << "������� " << hint << ": ";
		if (std::cin >> input && (!positive_only || (positive_only && !(std::less<T>()(input, 0))))) {
			break;
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (positive_only) {
				std::cout << "������ �����, ���������� ������� ���������� ������������ ��������!\n";
			}
			else {
				std::cout << "������ �����, ���������� ������� ���������� ��������!\n";
			}
		}
	}
	return input;
}

class Keithley {
protected:
	PORT device;
	char ReadBuffer[2048] = { NULL };
	char Command[2048] = { NULL };
public:
	Keithley(int port) : device(OpenPort(port)) {
		//device = OpenPort(port);
		HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);   //��������� ������
		CONSOLE_CURSOR_INFO cursor = { 1, false };   // ����� �� 1 �� 100 ������ ������� � ���������
		// false\true - ���������
		SetConsoleCursorInfo(hCons, &cursor);  //���������� �������� ���������� �������
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