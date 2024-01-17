/*#include "GDS-820.h"

PORT openCOMPort(const char* portName) {
	return CreateFile(portName,
		GENERIC_READ | GENERIC_WRITE, 
		0, 
		0, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		0);
}

bool configureCOMPort(PORT hSerial) {
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
		return false;
	}

	dcbSerialParams.BaudRate = BAUD_RATE;
	dcbSerialParams.ByteSize = BYTE_SIZE;
	dcbSerialParams.StopBits = STOP_BITS;
	dcbSerialParams.Parity = PARITY;

	if (!SetCommState(hSerial, &dcbSerialParams)) {
		return false;
	}

	return true;
}

bool writeCOMPort(PORT hSerial, const char* data, int size) {
	DWORD dwBytesWritten;
	return WriteFile(hSerial, data, size, &dwBytesWritten, NULL);
}

bool readCOMPort(PORT hSerial, char* data, int size, DWORD& dwBytesRead) {
	return ReadFile(hSerial, data, size, &dwBytesRead, NULL);
}

bool closeCOMPort(PORT hSerial) {
	return CloseHandle(hSerial);
}

int main1() {
	setlocale(LC_ALL, "RUSSIAN");
	system("chcp 1251");
	system("cls");
	const char* port = "\\\\.\\";
	const char* name = "COM13";
	std::string temp = static_cast<std::string>(port) + static_cast<std::string>(name);
	const char* portName = temp.c_str();
	//const char* portName = "\\\\.\\COM12";
	PORT hSerial = openCOMPort(portName);

	if (hSerial == INVALID_HANDLE_VALUE) {
		std::cerr << "Не удалось открыть COM - порт\n";
		return 1;
	}

	if (!configureCOMPort(hSerial)) {
		std::cerr << "Не удалось настроить COM - порт\n";
		closeCOMPort(hSerial);
		return 1;
	}

	char buf[100];
	DWORD dwBytesRead;
	const char* ID = "*IDN?\r\n";
	if (!writeCOMPort(hSerial, ID, strlen(ID))) {
		std::cerr << "Не удалось отправить команду\n";
		closeCOMPort(hSerial);
		return 1;
	}
	if (!readCOMPort(hSerial, buf, sizeof(buf), dwBytesRead)) {
		std::cerr << "Не удалось прочитать данные\n";
		closeCOMPort(hSerial);
		return 1;
	}

	//buf[dwBytesRead] = 0;

	//std::cout << "ID: " << buf << std::endl;
	//printf("%20s", buf);

	closeCOMPort(hSerial);

	return 0;
}*/