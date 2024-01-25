#include "Keithley.h"

// Открыть порт
PORT OpenPort(int portName) {
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
bool ConfigPort(PORT SerialPort) {
	DCB dcb = { 0 };
	dcb.DCBlength = sizeof(dcb);
	if (!GetCommState(SerialPort, &dcb)) {
		return false;
	}

	dcb.BaudRate = BAUD_RATE_57600;
	dcb.ByteSize = BYTE_SIZE;
	dcb.StopBits = STOP_BITS;
	dcb.Parity = PARITY;

	if (!SetCommState(SerialPort, &dcb)) {
		return false;
	}

	return true;
}

bool SetBaudRate(PORT SerialPort, int BaudRate) {
	DCB dcb;
	dcb.DCBlength = sizeof(dcb);
	if (!GetCommState(SerialPort, &dcb)) {
		return false;
	}

	dcb.BaudRate = BaudRate;

	if (!SetCommState(SerialPort, &dcb)) {
		return false;
	}

	return true;
}

bool SetByteSize(PORT SerialPort, int ByteSize) {
	DCB dcb;
	dcb.DCBlength = sizeof(dcb);
	if (!GetCommState(SerialPort, &dcb)) {
		return false;
	}

	dcb.ByteSize = ByteSize;

	if (!SetCommState(SerialPort, &dcb)) {
		return false;
	}

	return true;
}

bool SetStopBits(PORT SerialPort, int StopBits) {
	DCB dcb;
	dcb.DCBlength = sizeof(dcb);
	if (!GetCommState(SerialPort, &dcb)) {
		return false;
	}

	dcb.StopBits = StopBits;

	if (!SetCommState(SerialPort, &dcb)) {
		return false;
	}

	return true;
}

bool SetParity(PORT SerialPort, int Parity) {
	DCB dcb;
	dcb.DCBlength = sizeof(dcb);
	if (!GetCommState(SerialPort, &dcb)) {
		return false;
	}

	dcb.Parity = Parity;

	if (!SetCommState(SerialPort, &dcb)) {
		return false;
	}

	return true;
}

// Команда записи
bool WriteToPort(PORT SerialPort, const wchar_t* command) {
	DWORD bytesWritten;
	return WriteFile(SerialPort, command, wcslen(command), &bytesWritten, NULL);
}

// Сброс
bool RST(PORT SerialPort) {
	DWORD bytesWritten;
	const char* RST = "*RST\n";
	return WriteFile(SerialPort, RST, strlen(RST), &bytesWritten, NULL);
}

// Включить выход
bool OutputOn(PORT SerialPort) {
	DWORD bytesWritten;
	const char* Output = "OUTP ON\n";
	return WriteFile(SerialPort, Output, strlen(Output), &bytesWritten, NULL);
}

// Выключить выход
bool OutputOff(PORT SerialPort) {
	DWORD bytesWritten;
	const char* Output = "OUTP OFF\n";
	return WriteFile(SerialPort, Output, strlen(Output), &bytesWritten, NULL);
}

// Выбор режима
bool SetFunc(PORT SerialPort, const char* data) {
	DWORD bytesWritten;
	TCHAR command[100];
	wsprintf(command, TEXT("SOUR:FUNC "), data, TEXT("\n"));
	WriteToPort(SerialPort, command);
	command[100] = { 0 };
	wsprintf(command, TEXT("SOUR:"), data, TEXT(":MODE FIXED\n"));
	WriteToPort(SerialPort, command);
	//return WriteFile(SerialPort, command, wcslen(command), &bytesWritten, NULL);
}

// ИСТОЧНИК НАПРЯЖЕНИЯ
//
// 
// 
//  MODE FIXED добавить!!!!!!!!!!!!!!
//
// 
// 
//  Установить значение напряжения
bool SetVolt(PORT SerialPort, double value) {
	DWORD bytesWritten;
	TCHAR command[100];
	wsprintf(command, TEXT("SOUR:VOLT:LEV "), value, TEXT("\n"));
	return WriteFile(SerialPort, command, wcslen(command), &bytesWritten, NULL);
}

// Установить значение лимита тока
bool SetCurrProt(PORT SerialPort, double value) {
	DWORD bytesWritten;
	TCHAR command[100];
	//wsprintf(command, TEXT("SENS:CURR:RANG:AUTO ON\n"));
	wsprintf(command, TEXT("SENS:CURR:RANG "), value / 100, TEXT("\n"));
	WriteFile(SerialPort, command, wcslen(command), &bytesWritten, NULL);
	wsprintf(command, TEXT("SENS:CURR:PROT "), value / 1000, TEXT("\n"));
	return WriteFile(SerialPort, command, wcslen(command), &bytesWritten, NULL);
}


// ИСТОЧНИК ТОКА
// 
// Установить значение тока
bool SetCurr(PORT SerialPort, double value) {
	DWORD bytesWritten;
	TCHAR command[100];
	wsprintf(command, TEXT("SOUR:CURR:LEV "), value / 1000, TEXT("\n"));
	return WriteFile(SerialPort, command, wcslen(command), &bytesWritten, NULL);
}

// Установить значение лимита напряжения
bool SetVoltProt(PORT SerialPort, int value) {
	DWORD bytesWritten;
	TCHAR command[100];
	//wsprintf(command, TEXT("SENS:VOLT:RANG:AUTO ON\n"));
	wsprintf(command, TEXT("SENS:VOLT:RANG "), value + 5, TEXT("\n"));
	WriteFile(SerialPort, command, wcslen(command), &bytesWritten, NULL);
	wsprintf(command, TEXT("SENS:VOLT:PROT "), value, TEXT("\n"));
	return WriteFile(SerialPort, command, wcslen(command), &bytesWritten, NULL);
}

// Команда чтения
char* ReadFromPort(PORT SerialPort) {
	const char* readCommand = "READ?\n";
	DWORD bytesWritten;
	DWORD bytesRead;
	char buffer[256]{ 0 };
	if (WriteFile(SerialPort, readCommand, strlen(readCommand), &bytesWritten, NULL)) {
		if (ReadFile(SerialPort, buffer, sizeof(buffer), &bytesRead, NULL)) {
			return buffer;
		} else return false;			
	} else return false;
}

// Вывод на консоль значений Vcc & Icc
void PrintRead(char* buffer) {
	std::cout << "VCC = ";
	for (int j = 0; j < 13; j++) {
		std::cout << buffer[j];
	}
	std::cout << " ||| ";
	std::cout << "ICC = ";
	for (int j = 15; j < 27; j++) {
		std::cout << buffer[j];
	}
	std::cout << std::endl;
}

// Закрыть порт
bool closePort(PORT SerialPort) {
	return CloseHandle(SerialPort);
}