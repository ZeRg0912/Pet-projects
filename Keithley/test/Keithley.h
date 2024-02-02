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
#include <vector>
#include <set>

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

//template <typename T>
//T getInput(const std::string& hint, bool positive_only = false) {
//	T input;
//	while (true) {
//	system("cls");
//		std::cout << "������� " << hint << ": ";
//		if (std::cin >> input && (!positive_only || (positive_only && !(std::less<T>()(input, 0))))) {
//			break;
//		}
//		else {
//			std::cin.clear();
//			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			if (positive_only) {
//				std::cout << "������ �����, ���������� ������� ���������� ������������ ��������!\n";
//			}
//			else {
//				std::cout << "������ �����, ���������� ������� ���������� ��������!\n";
//			}
//		}
//	}
//	return input;
//}

template <typename T>
T getInput(const std::string& hint, bool positive_only = false, const std::set<T>& commands = {}) {
	T input;
	while (true) {
		std::cout << "������� " << hint << ": ";
		std::cin >> input;
		system("cls");
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "������ �����, ���������� ������� ���������� ��������!\n";
			continue;
		}
		if (positive_only && input < 0) {
			std::cout << "������ �����, ���������� ������� ���������� ������������ ��������!\n";
			continue;
		}
		if constexpr (!commands.empty() && std::is_same_v<T, std::string>) {
			for (int i = 0; i < input.size(); i++) {
				input[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(input[i])));
			}
			if (input != commands) {
				std::cout << "������ �����, ���������� ������� ���������� ��� ���������!\n";
				continue;
			}
		}
		break;
	}
	return input;
}

class Keithley {
protected:
	TCHAR comname[100];
	std::string PortName;
	PORT device;
	char ReadBuffer[2048] = { NULL };
	//char Command[2048] = { NULL };
	bool enable;
public:
	Keithley(int port) : device(OpenPort(port)), enable(false) {
		//device = OpenPort(port);
		HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);		//��������� ������
		CONSOLE_CURSOR_INFO cursor = { 1, false };			// ����� �� 1 �� 100 ������ ������� � ���������
		// false\true - ���������
		SetConsoleCursorInfo(hCons, &cursor);				//���������� �������� ���������� �������
	}

	~Keithley() {		
		//delete[] ReadBuffer;
		ClosePort();
	}

	void SetEnable(bool value) {
		enable = value;
	}

	void SetName(std::string NewName) {
		PortName = NewName;
	}

	bool GetEnable() {
		return enable;
	}

	PORT GetPort() {
		return device;
	}

	std::string GetNameDevice() {
		return PortName;
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
	bool WriteToPort(std::string data);
	
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

	void SetMeas();

	std::string ReadVoltCurr(int num);

	// ������� ����
	bool ClosePort();
};

//void Init(int numPort, std::string Source, float SourceValue, float ProtValue, int Cycles);

void Config(Keithley* device, std::string Source, float SourceValue, float ProtValue);

void StartMeas(Keithley* obj, int cycle);

void Stop(Keithley* obj);

void Begin();

void setcur(int x, int y);