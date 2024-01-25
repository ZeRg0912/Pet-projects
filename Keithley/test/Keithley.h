#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <functional>
#include <algorithm>
#include <cstring>

// Базовы значения порта
#define BAUD_RATE_9600 CBR_9600;
#define BAUD_RATE_57600 CBR_57600;
#define BYTE_SIZE 8;
#define STOP_BITS ONESTOPBIT;
#define PARITY NOPARITY;

#define VOLT "VOLT"
#define CURR "CURR"

typedef HANDLE PORT;

class Keithley {
protected:
	PORT device;
	char ReadBuffer[256] = { NULL };
public:
	Keithley(int port) {
		device = OpenPort(port);
	}
	~Keithley() {
		ClosePort();
	}

	PORT GetPort() {
		return device;
	}

	// Открыть порт
	PORT OpenPort(int portName);

	// Настроить порт
	bool ConfigPort();

	bool SetBaudRate(int BaudRate);

	bool SetByteSize(int ByteSize);

	bool SetStopBits(int StopBits);

	bool SetParity(int Parity);

	// Команда записи
	bool WriteToPort(const char* data);

	// Сброс
	bool RST();

	// Включить выход
	bool OutputOn();

	// Выключить выход
	bool OutputOff();

	// Выбор режима
	bool SetFunc(const char* data);

	// ИСТОЧНИК НАПРЯЖЕНИЯ
	// 
	// Установить значение напряжения
	bool SetVolt(double value);

	// Установить значение лимита тока
	bool SetCurrProt(double value);


	// ИСТОЧНИК ТОКА
	// 
	// Установить значение тока
	bool SetCurr(double value);

	// Установить значение лимита напряжения
	bool SetVoltProt(double value);

	// Команды отображения на приборе
	char* DisplayVolts();

	char* DisplayCurr();

	// Команда чтения
	char* ReadVolt();

	char* ReadCurr();

	std::string ReadFromPort();

	// Вывод на консоль значений Vcc & Icc
	void PrintRead();

	// Закрыть порт
	bool ClosePort();
};