#include "Keithley.h"

// Открыть порт
PORT Keithley::OpenPort(int portName) {
    PORT port;
    TCHAR comname[100];
    wsprintf(comname, TEXT("\\\\.\\COM%d"), portName);

    // Открытие COM-порта
    return CreateFileW(comname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (port == INVALID_HANDLE_VALUE)
    {
        std::wcout << L"Ошибка открытия COM-порта" << std::endl;
    }
    else {
        return port;
    }
}

// Настроить порт
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
	DCB dcb;
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
	DCB dcb;
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
	DCB dcb;
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
	DCB dcb;
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

// Команда записи
bool Keithley::WriteToPort(const char* command) {
	DWORD bytesWritten;
	return WriteFile(device, command, strlen(command), &bytesWritten, NULL);
}

// Сброс
bool Keithley::RST() {
	DWORD bytesWritten;
	const char* RST = "*RST\n";
	return WriteFile(device, RST, strlen(RST), &bytesWritten, NULL);
}

// Включить выход
bool Keithley::OutputOn() {
	DWORD bytesWritten;
	const char* Output = "OUTP ON\n";
	return WriteFile(device, Output, strlen(Output), &bytesWritten, NULL);
}

// Выключить выход
bool Keithley::OutputOff() {
	DWORD bytesWritten;
	const char* Output = "OUTP OFF\n";
	return WriteFile(device, Output, strlen(Output), &bytesWritten, NULL);
}

// Выбор режима
bool Keithley::SetFunc(const char* data) {
	DWORD bytesWritten;
	std::string temp = "SOUR:FUNC " + std::string(data) + "\n";
	const char* command = temp.c_str();
	WriteToPort(command);
	memset(&command, 0, sizeof(command));
	temp = "SOUR:" + std::string(data) + ":MODE FIXED\n";
	command = temp.c_str();
	return WriteToPort(command);
}

// ИСТОЧНИК НАПРЯЖЕНИЯ
//
//  Установить значение напряжения
bool Keithley::SetVolt(double value) {
	DWORD bytesWritten;
	std::string temp = "SOUR:VOLT " + std::to_string(value) + "\n";
	const char* command = temp.c_str();
	return WriteFile(device, command, strlen(command), &bytesWritten, NULL);
}

// Установить значение лимита тока
bool Keithley::SetCurrProt(double value) {
	DWORD bytesWritten;
	std::string temp = "SENS:CURR:RANG:AUTO ON\n";
	const char* command = temp.c_str();
	WriteFile(device, command, strlen(command), &bytesWritten, NULL);

	//temp = "SENS:CURR:RANG" + std::to_string(value / 500) + "\n";
	//command = temp.c_str();
	//std::cout << value / 100 << std::endl;
	//WriteFile(device, command, strlen(command), &bytesWritten, NULL);

	temp = "SENS:CURR:PROT " + std::to_string(value / 1000) + "\n";
	std::replace(temp.begin(), temp.end(), ',', '.');
	command = temp.c_str();
	return WriteFile(device, command, strlen(command), &bytesWritten, NULL);
}


// ИСТОЧНИК ТОКА
// 
// Установить значение тока
bool Keithley::SetCurr(double value) {
	DWORD bytesWritten;
	TCHAR command[100];
	wsprintf(command, TEXT("SOUR:CURR:LEV "), value / 1000, TEXT("\n"));
	return WriteFile(device, command, wcslen(command), &bytesWritten, NULL);
}

// Установить значение лимита напряжения
bool Keithley::SetVoltProt(double value) {
	DWORD bytesWritten;
	TCHAR command[100];
	//wsprintf(command, TEXT("SENS:VOLT:RANG:AUTO ON\n"));
	wsprintf(command, TEXT("SENS:VOLT:RANG "), value + 5, TEXT("\n"));
	WriteFile(device, command, wcslen(command), &bytesWritten, NULL);
	wsprintf(command, TEXT("SENS:VOLT:PROT "), value, TEXT("\n"));
	return WriteFile(device, command, wcslen(command), &bytesWritten, NULL);
}

// Команда чтения
char* Keithley::ReadFromPort() {
	const char* readCommand = "READ?\n";
	const char* readVolts = "READ?\n";
	const char* readCurr = "READ?\n";
	DWORD bytesWritten;
	DWORD bytesRead;
	memset(ReadBuffer, 0, sizeof(ReadBuffer));
	WriteFile(device, readCommand, strlen(readCommand), &bytesWritten, NULL);
	ReadFile(device, ReadBuffer, sizeof(ReadBuffer), &bytesRead, NULL);
	return ReadBuffer;
}

// Вывод на консоль значений Vcc & Icc
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

// Закрыть порт
bool Keithley::ClosePort() {
	return CloseHandle(device);
}