#include "Keithley.h"

// ������� ����
PORT Keithley::OpenPort(int portName) {
	PORT port{};
    TCHAR comname[100];
    wsprintf(comname, TEXT("\\\\.\\COM%d"), portName);

    // �������� COM-�����
    return CreateFile(comname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (port == INVALID_HANDLE_VALUE)
    {
        std::wcout << L"������ �������� COM-�����" << std::endl;
    }
    else {
        return port;
    }
}

// ������� ������
bool Keithley::WriteToPort(const char* command) {
	DWORD bytesWritten;
	return WriteFile(device, command, strlen(command), &bytesWritten, NULL);
}

// ������� ������
bool Keithley::ReadFromPort() {
	DWORD bytesRead;
	return ReadFile(device, ReadBuffer, sizeof(ReadBuffer), &bytesRead, NULL);
}

// ��������� ����
bool Keithley::ConfigPort() {
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

bool Keithley::SetBaudRate(int BaudRate) {
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

bool Keithley::SetByteSize(int ByteSize) {
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

bool Keithley::SetStopBits(int StopBits) {
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

bool Keithley::SetParity(int Parity) {
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

// �����
bool Keithley::RST() {
	return WriteToPort("*RST\n");
}

// �������� �����
bool Keithley::OutputOn() {
	return WriteToPort(":OUTP ON\n");
}

// ��������� �����
bool Keithley::OutputOff() {
	return WriteToPort(":OUTP OFF\n");
}

// ����� ������
bool Keithley::SetFunc(std::string data) {
	std::string command = ":SOUR:FUNC " + data + "\n";
	WriteToPort(command.c_str());
	command = ":SOUR:" + std::string(data) + ":MODE FIXED\n";
	return WriteToPort(command.c_str());
}

// ��������� �������� ������
bool Keithley::SetReadSpeed(double value) {
	std::string command = ":SENS:VOLT:NPLC " + std::to_string(value) + "\n";
	std::replace(command.begin(), command.end(), ',', '.');
	return WriteToPort(command.c_str());
}

// �������� ����������
//
//  ���������� �������� ����������
bool Keithley::SetVolt(double value) {
	std::string command = ":SOUR:VOLT " + std::to_string(value) + "\n";
	//WriteToPort("SOUR:DEL:AUTO ON\n");
	return WriteToPort(command.c_str());
}

// ���������� �������� ������ ����
bool Keithley::SetCurrProt(double value) {
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
bool Keithley::SetCurr(double value) {
	std::string command = ":SOUR:CURR " + std::to_string(value / 1000) + "\n";
	return WriteToPort(command.c_str());
}

// ���������� �������� ������ ����������
bool Keithley::SetVoltProt(double value) {
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
char* Keithley::DisplayVolts() {
	WriteToPort("MEAS:VOLT?\n");
	//ReadFromPort();
	return ReadBuffer;
}

char* Keithley::DisplayCurr() {
	WriteToPort("MEAS:CURR?\n");
	//ReadFromPort();
	return ReadBuffer;
}

// ������� ������
char* Keithley::ReadVolt() {
	//Sleep(10);
	WriteToPort(":FORM:ELEM VOLT\r");
	WriteToPort(":SENS:FUNC 'VOLT'\r");
	WriteToPort("READ?\n");
	ReadFromPort();
	Sleep(20);
	return ReadBuffer;
}

char* Keithley::ReadCurr() {
	//Sleep(10);
	WriteToPort(":FORM:ELEM CURR\r");
	WriteToPort(":SENS:FUNC 'CURR'\r");
	WriteToPort(":READ?\n");
	ReadFromPort();
	Sleep(20);
	return ReadBuffer;
}

std::string Keithley::ReadVoltCurr(int num) {
	std::string info;
	std::string vcc;
	std::string icc; 

	for (int i = 0; i <= num; i++) {
		vcc = ReadVolt();
		icc = ReadCurr();
		if (i > 0) {
			std::cout << "Measurment " << i << ": " << std::endl;
			int pos = vcc.find('\n');
			vcc = vcc.substr(0, pos - 1);
			icc = icc.substr(pos + 1, (icc.length() - 1) / 2);
			info = "VCC = " + vcc + "; ICC = " + icc + "\n";
			std::cout << info;
		}
		Sleep(150);
		memset(ReadBuffer, 0, sizeof(ReadBuffer));
	}	
	return info;
}

// ����� �� ������� �������� Vcc & Icc
void Keithley::PrintRead() {
	std::cout << "VCC = ";
	for (int i = 0; i < 13; i++) {
		std::cout << ReadBuffer[i];
	}
	std::cout << " ||| ";
	std::cout << "ICC = ";
	for (int i = 15; i < 27; i++) {
		std::cout << ReadBuffer[i];
	}
	std::cout << std::endl;
}

// ������� ����
bool Keithley::ClosePort() {
	return CloseHandle(device);
}