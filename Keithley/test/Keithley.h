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

// Базовы значения порта
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
	system("cls");
	while (true) {
		std::cout << "Введите " << hint << ": ";
		if (std::cin >> input && (!positive_only || (positive_only && !(std::less<T>()(input, 0))))) {
			break;
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (positive_only) {
				std::cout << "Ошибка ввода, пожалуйста введите корректное полоительное значение!\n";
			}
			else {
				std::cout << "Ошибка ввода, пожалуйста введите корректное значение!\n";
			}
		}
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
		HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);		//Получение хендла
		CONSOLE_CURSOR_INFO cursor = { 1, false };			// Число от 1 до 100 размер курсора в процентах
		// false\true - видимость
		SetConsoleCursorInfo(hCons, &cursor);				//Применение заданных параметров курсора
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
	bool WriteToPort(std::string data);
	
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

	void SetMeas();

	std::string ReadVoltCurr(int num);

	// Закрыть порт
	bool ClosePort();
};

void Config(Keithley* device, std::string Source, float SourceValue, float ProtValue);

void StartMeas(Keithley* obj, int cycle);

void Stop(Keithley* obj);

void setcur(int x, int y);

void Begin();

void Init(int numPort, std::string Source, float SourceValue, float ProtValue, int Cycles);

Keithley StartConfig(int numPort, std::string Source, float SourceValue, float ProtValue);