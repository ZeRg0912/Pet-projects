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

template <typename T>
T getInput(const std::string& hint, bool positive_only = false) {
	T input;
	while (true) {
		std::cout << "������� " << hint << ": "; 
		std::cin >> input;
		system("cls");
		if (!std::cin.fail() && (!positive_only || (positive_only && !(std::less<T>()(input, 0))))) {
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

template<>
std::string getInput(const std::string& hint, bool positive_only) {
	std::string input;
	std::vector<std::string> ValidCommands = { "VOLT", "CURR" };
	while (true) {
		std::cout << "������� " << hint << ": ";
		std::cin >> input;
		system("cls");
		std::transform(input.begin(), input.end(), input.begin(), ::toupper);
		auto it = std::find(ValidCommands.begin(), ValidCommands.end(), input);
		if (it != ValidCommands.end()) {
			break;
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "������ �����, ���������� ������� ���������� ��������!\n";
		}
	}
	return input;
}

void setcur(int x, int y)//��������� ������� �� �������  x y
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

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
	PORT OpenPort(int portName) {
		PORT port{};
		wsprintf(comname, TEXT("\\\\.\\COM%d"), portName);
		//std::wstring wide_port_name(comname);
		//port_name.resize(wide_port_name.size());
		//std::copy(wide_port_name.begin(), wide_port_name.end(), port_name.begin());
		PortName = "COM - Port #" + std::to_string(portName) + '\n';

		// �������� COM-�����
		return CreateFile(comname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	}





	// ������� ������
	bool WriteToPort(std::string command) {
		DWORD bytesWritten;
		return WriteFile(device, command.c_str(), strlen(command.c_str()), &bytesWritten, NULL);
	}

	// ������� ������
	bool ReadFromPort() {
		DWORD bytesRead;
		return ReadFile(device, ReadBuffer, sizeof(ReadBuffer), &bytesRead, NULL);
	}





	// ��������� ����
	bool ConfigPort() {
		DCB dcb = { 0 };
		dcb.DCBlength = sizeof(dcb);
		if (!GetCommState(device, &dcb)) {
			return false;
		}
		dcb.BaudRate = BAUD_RATE_57600;
		dcb.ByteSize = BYTE_SIZE;
		dcb.StopBits = STOP_BITS;
		dcb.Parity = PARITY;

		if (!SetCommState(device, &dcb)) {
			return false;
		}
		return true;
	}

	bool SetBaudRate(int BaudRate) {
		DCB dcb{};
		dcb.DCBlength = sizeof(dcb);
		if (!GetCommState(device, &dcb)) {
			return false;
		}

		dcb.BaudRate = BaudRate;

		if (!SetCommState(device, &dcb)) {
			return false;
		}

		return true;
	}

	bool SetByteSize(int ByteSize) {
		DCB dcb{};
		dcb.DCBlength = sizeof(dcb);
		if (!GetCommState(device, &dcb)) {
			return false;
		}

		dcb.ByteSize = ByteSize;

		if (!SetCommState(device, &dcb)) {
			return false;
		}

		return true;
	}

	bool SetStopBits(int StopBits) {
		DCB dcb{};
		dcb.DCBlength = sizeof(dcb);
		if (!GetCommState(device, &dcb)) {
			return false;
		}

		dcb.StopBits = StopBits;

		if (!SetCommState(device, &dcb)) {
			return false;
		}

		return true;
	}

	bool SetParity(int Parity) {
		DCB dcb{};
		dcb.DCBlength = sizeof(dcb);
		if (!GetCommState(device, &dcb)) {
			return false;
		}

		dcb.Parity = Parity;

		if (!SetCommState(device, &dcb)) {
			return false;
		}

		return true;
	}





	// �������� �����
	bool ResetTime() {
		return WriteToPort("SYST:TIME:RES\n");
	}

	// �����
	bool RST() {
		return WriteToPort("*RST\n");
	}

	// �������� �����
	bool OutputOn() {
		return WriteToPort(":OUTP ON\n");
	}

	// ��������� �����
	bool OutputOff() {
		return WriteToPort(":OUTP OFF\n");
	}

	// ����� ������
	bool SetFunc(std::string data) {
		std::string command = ":SOUR:FUNC " + data + "\n";
		WriteToPort(command.c_str());
		command = ":SOUR:" + std::string(data) + ":MODE FIXED\n";
		return WriteToPort(command.c_str());
	}

	// ��������� �������� ������
	bool SetReadSpeed(float value) {
		std::string command = ":SENS:VOLT:NPLC " + std::to_string(value) + "\n";
		std::replace(command.begin(), command.end(), ',', '.');
		return WriteToPort(command.c_str());
	}





	// �������� ����������
	//
	//  ���������� �������� ����������
	bool SetVolt(float value) {
		std::string command = ":SOUR:VOLT " + std::to_string(value) + "\n";
		std::replace(command.begin(), command.end(), ',', '.');
		//WriteToPort("SOUR:DEL:AUTO ON\n");
		return WriteToPort(command.c_str());
	}

	// ���������� �������� ������ ����
	bool SetCurrProt(float value) {
		std::string command = ":SENS:CURR:RANG:AUTO ON\n";
		WriteToPort(command.c_str());

		command = ":SENS:CURR:RANG" + std::to_string(value / 500) + "\n";
		//std::cout << value / 100 << std::endl;
		//WriteToPort(command.c_str());

		command = ":SENS:CURR:PROT " + std::to_string(value / 1000) + "\n";
		std::replace(command.begin(), command.end(), ',', '.');
		return WriteToPort(command.c_str());
	}





	// �������� ����
	// 
	// ���������� �������� ����
	bool SetCurr(float value) {
		std::string command = ":SOUR:CURR " + std::to_string(value / 1000) + "\n";
		std::replace(command.begin(), command.end(), ',', '.');
		return WriteToPort(command.c_str());
	}

	// ���������� �������� ������ ����������
	bool SetVoltProt(float value) {
		std::string command = ":SENS:VOLT:RANG:AUTO ON\n";
		WriteToPort(command.c_str());

		//temp = "SENS:CURR:RANG" + std::to_string(value / 500) + "\n";
		//command = temp.c_str();
		//std::cout << value / 100 << std::endl;
		//WriteToPort(command);

		command = ":SENS:VOLT:PROT " + std::to_string(value + 5) + "\n";
		std::replace(command.begin(), command.end(), ',', '.');
		return WriteToPort(command.c_str());
	}





	// ������� ����������� �� �������
	char* DisplayVolts() {
		WriteToPort(":MEAS:VOLT?\n");
		//ReadFromPort();
		return ReadBuffer;
	}

	char* DisplayCurr() {
		WriteToPort(":MEAS:CURR?\n");
		//ReadFromPort();
		return ReadBuffer;
	}

	// ������� ������
	char* ReadVolt() {
		//Sleep(10);
		WriteToPort(":FORM:ELEM VOLT\r");
		WriteToPort(":SENS:FUNC 'VOLT'\r");
		WriteToPort("READ?\n");
		ReadFromPort();
		Sleep(20);
		return ReadBuffer;
	}

	char* ReadCurr() {
		//Sleep(10);
		WriteToPort(":FORM:ELEM CURR\r");
		WriteToPort(":SENS:FUNC 'CURR'\r");
		WriteToPort(":READ?\n");
		ReadFromPort();
		Sleep(20);
		return ReadBuffer;
	}

	void SetMeas() {
		this->ResetTime();
		WriteToPort(":FORM:ELEM VOLT, CURR, TIME\n");
		WriteToPort(":SENSE:FUNC 'VOLT', 'CURR'\n");
		WriteToPort(":READ?\n");
		Sleep(100);
	}

	std::string ReadVoltCurr(int cycle) {
		std::string info;
		std::string svcc;
		std::string sicc;
		std::string stime;
		float time;
		float vcc;
		system("cls");
		setcur(0, 0);
		std::cout << GetNameDevice();
		std::cout << "Measurment #" << cycle << ": " << std::endl;
		WriteToPort(":READ?\n");
		ReadFromPort();
		info = ReadBuffer;
		svcc = info.substr(0, 13);
		sicc = info.substr(14, 13);
		stime = info.substr(29, 13);

		std::istringstream iss_time(stime);
		iss_time >> time;
		std::istringstream iss_vcc(svcc);
		iss_vcc >> vcc;
		std::stringstream iss_info;
		iss_info << "TIME: "
			<< std::fixed
			<< std::setprecision(3)
			<< time << " Seconds\n"
			<< "Vcc = "
			<< std::fixed
			<< std::setprecision(4)
			<< vcc
			<< " Volts\n"
			<< "Icc = "
			<< sicc
			<< " Ampers\n";
		info = iss_info.str();
		//std::cout << iss_info.str() << std::endl;
		memset(ReadBuffer, 0, sizeof(ReadBuffer));
		Sleep(5);
		return info;
	}

	// ������� ����
	bool ClosePort() {
		return CloseHandle(device);
	}
};

//void Init(int numPort, std::string Source, float SourceValue, float ProtValue, int Cycles);

void Config(Keithley* device, std::string Source, float SourceValue, float ProtValue) {
	transform(Source.begin(), Source.end(), Source.begin(), ::toupper);
	if (device->GetPort() == INVALID_HANDLE_VALUE) {
		device->SetEnable(false);
		device->ClosePort();
		device->SetName("���� ����������!");
		//std::cout << "Can't open COMport\n";
		return;
	}
	else {
		device->ConfigPort();
		device->SetFunc(Source);
		if (Source == VOLT) {
			device->SetVolt(SourceValue);
			device->SetCurrProt(ProtValue);
		}
		else if (Source == CURR) {
			device->SetCurr(SourceValue);
			device->SetVoltProt(ProtValue);
		}
		else {
			std::cout << "INCORRECT SOURCE TYPE\n";
			device->SetEnable(false);
			device->ClosePort();
			return;
		}
		device->SetEnable(true);
		device->SetReadSpeed(0.01);
	}
	return;
}

void StartMeas(Keithley* obj, int cycle) {
	std::cout << obj->ReadVoltCurr(cycle);
}

void Stop(Keithley* obj) {
	obj->OutputOff();
	obj->ClosePort();
}

void Begin() {
	std::vector<Keithley*> Devices;
	int port, cycles;
	std::string source;
	float source_value, prot_value;

	auto RemoveCondition = [](Keithley* obj) {return !obj->GetEnable(); };

	int quantity_devices = getInput<int>("��� - �� ��������", true);

	for (int i = 0; i < quantity_devices; i++) {
		port = getInput<int>("����� COM - ����� (0..20)", true);
		source = getInput<std::string>("��� ��������� (Volt, Curr)", false);
		source_value = getInput<float>("�������� ��������� (�, ��)");
		prot_value = getInput<float>("����������� (�, ��)");
		Keithley* device = new Keithley(port);
		Config(device, source, source_value, prot_value);
		Devices.push_back(device);
	}
	Devices.erase(std::remove_if(Devices.begin(), Devices.end(), RemoveCondition), Devices.end());
	//Devices.shrink_to_fit();

	cycles = getInput<int>("��� - �� ���������: ", true);

	for (auto& obj : Devices) {
		obj->OutputOn();
	}

	Sleep(300);

	for (auto& obj : Devices) {
		obj->SetMeas();
	}

	if (!Devices.empty()) {
		for (int i = 1; i <= cycles; i++) {
			for (auto& obj : Devices) {
				StartMeas(obj, i);
				std::cout << std::string(30, '=') << std::endl;
			}
		}
		Sleep(10);
		for (auto& obj : Devices) {
			Stop(obj);
		}
	}
	else {
		std::cout << "��� ��������� ���������!\n";
	}

	for (Keithley* element : Devices) {
		delete element;
	}
	Devices.clear();
}