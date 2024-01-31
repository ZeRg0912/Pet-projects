#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <functional>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <sstream>

// Базовы значения порта
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

	// Открыть порт
	PORT OpenPort(int portName);

	// Настроить порт
	bool ConfigPort();

	bool SetBaudRate(int BaudRate);

	bool SetByteSize(int ByteSize);

	bool SetStopBits(int StopBits);

	bool SetParity(int Parity);

	// Сбросить время
	bool ResetTime();

	// Команда записи
	bool WriteToPort(const char* data);
	
	// Команда чтения
	bool ReadFromPort();

	// Сброс
	bool RST();

	// Включить выход
	bool OutputOn();

	// Выключить выход
	bool OutputOff();

	// Выбор режима
	bool SetFunc(std::string data);

	// Установка скорости чтения
	bool SetReadSpeed(float value);

	// ИСТОЧНИК НАПРЯЖЕНИЯ
	// 
	// Установить значение напряжения
	bool SetVolt(float value);

	// Установить значение лимита тока
	bool SetCurrProt(float value);


	// ИСТОЧНИК ТОКА
	// 
	// Установить значение тока
	bool SetCurr(float value);

	// Установить значение лимита напряжения
	bool SetVoltProt(float value);

	// Команды отображения на приборе
	char* DisplayVolts();

	char* DisplayCurr();

	// Команда чтения
	char* ReadVolt();

	char* ReadCurr();

	std::string ReadVoltCurr(int num);

	// Вывод на консоль значений Vcc & Icc
	void PrintRead();

	// Закрыть порт
	bool ClosePort();
};