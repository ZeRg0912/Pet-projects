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
	std::string temp = "SOUR:CURR " + std::to_string(value / 1000) + "\n";
	const char* command = temp.c_str();
	return WriteFile(device, command, strlen(command), &bytesWritten, NULL);
}

// Установить значение лимита напряжения
bool Keithley::SetVoltProt(double value) {
	DWORD bytesWritten;
	std::string temp = "SENS:VOLT:RANG:AUTO ON\n";
	const char* command = temp.c_str();
	WriteFile(device, command, strlen(command), &bytesWritten, NULL);

	//temp = "SENS:CURR:RANG" + std::to_string(value / 500) + "\n";
	//command = temp.c_str();
	//std::cout << value / 100 << std::endl;
	//WriteFile(device, command, strlen(command), &bytesWritten, NULL);

	temp = "SENS:VOLT:PROT " + std::to_string(value + 5) + "\n";
	std::replace(temp.begin(), temp.end(), ',', '.');
	command = temp.c_str();
	return WriteFile(device, command, strlen(command), &bytesWritten, NULL);
}

// Команды отображения на приборе
char* Keithley::DisplayVolts() {
	DWORD bytesWritten; 
	DWORD bytesRead;
	const char* displayVolts = "MEAS:VOLT?\n";
	const char* readVolts = "FORM:ELEM VOLT\n";

	memset(ReadBuffer, 0, sizeof(ReadBuffer));

	//WriteFile(device, readVolts, strlen(readVolts), &bytesWritten, NULL);
	//Sleep(10);
	WriteFile(device, displayVolts, strlen(displayVolts), &bytesWritten, NULL);
	ReadFile(device, &ReadBuffer, sizeof(ReadBuffer), &bytesRead, NULL);
	//ReadBuffer[bytesRead] = '\0';
	return ReadBuffer;
}

char* Keithley::DisplayCurr() {
	DWORD bytesWritten;
	DWORD bytesRead;
	const char* displayCurr = "MEAS:CURR?\n";

	memset(ReadBuffer, 0, sizeof(ReadBuffer));

	//WriteFile(device, readCurr, strlen(readCurr), &bytesWritten, NULL);
	//Sleep(10);
	WriteFile(device, displayCurr, strlen(displayCurr), &bytesWritten, NULL);
	ReadFile(device, &ReadBuffer, sizeof(ReadBuffer), &bytesRead, NULL);

	//ReadBuffer[bytesRead] = '\0';

	return ReadBuffer;
}

// Команда чтения
char* Keithley::ReadVolt() {
	DWORD bytesWritten;
	DWORD bytesRead;
	const char* readCommand = "READ?\n";
	const char* readVolt = "FORM:ELEM VOLT\n";

	WriteFile(device, readVolt, strlen(readVolt), &bytesWritten, NULL);
	WriteFile(device, readCommand, strlen(readCommand), &bytesWritten, NULL);
	ReadFile(device, &ReadBuffer, sizeof(ReadBuffer), &bytesRead, NULL);
	Sleep(50);

	return ReadBuffer;
}

char* Keithley::ReadCurr() {
	DWORD bytesWritten;
	DWORD bytesRead;
	const char* readCommand = "READ?\n";
	const char* readCurr = "FORM:ELEM CURR\n";

	WriteFile(device, readCurr, strlen(readCurr), &bytesWritten, NULL);
	WriteFile(device, readCommand, strlen(readCommand), &bytesWritten, NULL);
	ReadFile(device, &ReadBuffer, sizeof(ReadBuffer), &bytesRead, NULL);
	Sleep(50);

	//std::string str(ReadBuffer); - возврат строкой

	return ReadBuffer;
}

std::string Keithley::ReadFromPort() {
	std::string info;
	std::string vcc;
	std::string icc;

	for (int i = 0; i < 10; i++) {
		memset(&ReadBuffer, 0, sizeof(ReadBuffer));
		info = "";
		std::cout << "Measurment " << i + 1 << ": " << std::endl;
		vcc = ReadVolt();
		icc = ReadCurr(); 
		//std::replace(vcc.begin(), vcc.end(), '\0', ' ');
		//std::replace(icc.begin(), icc.end(), '\0', ' ');
		//info = "Vcc = " + vcc + "\nIcc = " + icc;

		//std::cout << info << std::endl;
		std::cout << vcc << std::endl;
		//std::cout << icc << std::endl;

		Sleep(150);
	}	
	return info;
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