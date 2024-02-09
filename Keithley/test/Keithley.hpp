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
#include <fstream>
#include <conio.h>

// Базовы значения порта
#define BAUD_RATE_9600 CBR_9600;
#define BAUD_RATE_57600 CBR_57600;
#define BYTE_SIZE 8;
#define STOP_BITS ONESTOPBIT;
#define PARITY NOPARITY;

#define VOLT "VOLT"
#define CURR "CURR"
#define RES "RES"

#define DELAY 1000

#if defined(max)
#undef max
#endif

typedef HANDLE PORT;

template <typename T>
T getInput(const std::string& hint, bool positive_only = false) {
	T input;
	while (true) {
		std::cout << "Enter " << hint << ": "; 
		std::cin >> input;
		system("cls");
		if (!std::cin.fail() && (!positive_only || (positive_only && !(std::less<T>()(input, 0))))) {
			break;
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (positive_only) {
				std::cout << "Input error, please enter the correct positive value!\n";
			}
			else {
				std::cout << "Input error, please enter the correct value!\n";
			}
		}
	}
	return input;
}

template<>
std::string getInput(const std::string& hint, bool valid_command) {
	std::string input;
	std::vector<std::string> ValidCommands = { "VOLT", "CURR" };
	while (true) {
		std::cout << "Enter " << hint << ": ";
		std::cin >> input;
		system("cls");
		if (valid_command) {
			std::transform(input.begin(), input.end(), input.begin(), ::toupper);
			auto it = std::find(ValidCommands.begin(), ValidCommands.end(), input);
			if (it != ValidCommands.end()) {
				break;
			}
			else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Input error, please enter the correct command!\n";
			}
		}
		else if (!valid_command) {
			break;
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Input error, please enter the correct command!\n";
		}
	}
	return input;
}

void setcur(int x, int y)//установка курсора на позицию  x y
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
	DWORD bytesWritten;
	DWORD bytesRead;
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
		this->enable = value;
	}

	void SetName(std::string NewName) {
		this->PortName = NewName;
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
	PORT OpenPort(int portName) {
		PORT port{};
		wsprintf(comname, TEXT("\\\\.\\COM%d"), portName);
		PortName = "COM - Port #" + std::to_string(portName);

		// Открытие COM-порта
		return CreateFile(comname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	}





	// Команда записи
	bool WriteToPort(std::string command) {
		return WriteFile(device, command.c_str(), strlen(command.c_str()), &bytesWritten, NULL);
	}

	// Команда чтения
	bool ReadFromPort() {
		return ReadFile(device, ReadBuffer, sizeof(ReadBuffer), &bytesRead, NULL);
	}





	// Проверка вкл устройства
	bool IsOn() {
		std::string command = "*IDN?\n";
		DWORD status;
		if (!WriteFile(device, command.c_str(), strlen(command.c_str()), &status, NULL)) {
			std::cout << "BAD\n";
			return false;
		}
		Sleep(10);
		char responce[1024];
		if (!ReadFile(device, responce, sizeof(responce), &bytesRead, NULL)) {
			std::cout << "BAD\n";
			return false;
		}
		if (bytesRead > 0) {
			return true;
		}
		return false;
	}




	// Настроить порт
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





	// Сбросить время
	bool ResetTime() {
		return WriteToPort("SYST:TIME:RES\n");
	}

	// Сброс
	bool RST() {
		return WriteToPort("*RST\n");
	}

	// Включить выход
	bool OutputOn() {
		return WriteToPort(":OUTP ON\n");
	}

	// Выключить выход
	bool OutputOff() {
		return WriteToPort(":OUTP OFF\n");
	}

	// Установка скорости чтения
	bool SetReadSpeed(double value) {
		std::string command = ":SENS:VOLT:NPLC " + std::to_string(value) + "\n";
		std::replace(command.begin(), command.end(), ',', '.');
		return WriteToPort(command.c_str());
	}



	// Выбор режима
	bool SetFunc(std::string data) {
		std::string command = ":SOUR:FUNC " + data + "\n";
		WriteToPort(command.c_str());
		command = ":SOUR:" + std::string(data) + ":MODE FIXED\n";
		return WriteToPort(command.c_str());
	}

	// ИСТОЧНИК НАПРЯЖЕНИЯ
	//
	//  Установить значение напряжения
	bool SetVolt(float value) {
		std::string command = ":SOUR:VOLT " + std::to_string(value) + "\n";
		std::replace(command.begin(), command.end(), ',', '.');
		return WriteToPort(command.c_str());
	}

	// Установить значение лимита тока
	bool SetCurrProt(float value) {
		std::string command = ":SENS:CURR:RANG:AUTO ON\n";
		WriteToPort(command.c_str());

		// Задать Range
#if 0
		command = ":SENS:CURR:RANG" + std::to_string(value / 500) + "\n";
		std::cout << value / 100 << std::endl;
		WriteToPort(command.c_str());
#endif

		command = ":SENS:CURR:PROT " + std::to_string(value / 1000) + "\n";
		std::replace(command.begin(), command.end(), ',', '.');
		return WriteToPort(command.c_str());
	}





	// ИСТОЧНИК ТОКА
	// 
	// Установить значение тока
	bool SetCurr(float value) {
		std::string command = ":SOUR:CURR:RANG " + std::to_string((value / 1000) * 2) + "\n";
		std::replace(command.begin(), command.end(), ',', '.');
		WriteToPort(command.c_str());
		command = ":SOUR:CURR " + std::to_string(value / 1000) + "\n";
		std::replace(command.begin(), command.end(), ',', '.');
		return WriteToPort(command.c_str());
	}

	// Установить значение лимита напряжения
	bool SetVoltProt(float value) {
		std::string command = ":SENS:VOLT:RANG:AUTO ON\n";
		WriteToPort(command.c_str());

		// Задать Range
#if 0
		command = ":SENS:CURR:RANG" + std::to_string(value / 500) + "\n";
		std::cout << value / 100 << std::endl;
		WriteToPort(command.c_str());
#endif

		command = ":SENS:VOLT:PROT " + std::to_string(value) + "\n";
		std::replace(command.begin(), command.end(), ',', '.');
		return WriteToPort(command.c_str());
	}





	// Команды отображения на приборе
	char* DisplayVolts() {
		WriteToPort(":MEAS:VOLT?\n");
		return ReadBuffer;
	}

	char* DisplayCurr() {
		WriteToPort(":MEAS:CURR?\n");
		return ReadBuffer;
	}

	// Команда чтения
	void SetMeas() {
		this->ResetTime();
		WriteToPort(":FORM:ELEM VOLT, CURR, TIME\n");
		WriteToPort(":SENSE:FUNC 'VOLT', 'CURR'\n");
		WriteToPort(":READ?\n");
		Sleep(100);
	}

	std::string ReadVoltCurr() {
		std::string info;
		std::string svcc;
		std::string sicc;
		std::string stime;
		float time;
		float vcc;
		ReadFromPort();
		info = ReadBuffer;
		svcc = info.substr(0, 13);
		sicc = info.substr(14, 13);
		stime = info.substr(28, 13);


		std::istringstream iss_time(stime);
		iss_time >> time;
		std::istringstream iss_vcc(svcc);
		iss_vcc >> vcc;
		std::stringstream iss_info;
		//info var 1
#if 0
		iss_info 
			<< GetNameDevice()
			<< "Measurment #"
			<< cycle
			<< ": \n"
			<< "TIME: "
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
			<< " Ampers\n"
			<< std::string(30, '=') 
			<< std::endl;
			#endif
		//info var 2
		iss_info
			<< GetNameDevice()
			<< ": "
			<< "TIME: "
			<< std::fixed
			<< std::setprecision(3)
			<< time << " s || "
			<< "Vcc = "
			<< std::fixed
			<< std::setprecision(4)
			<< vcc
			<< " V || "
			<< "Icc = "
			<< sicc
			<< " A          \n";
		info = iss_info.str();
		memset(ReadBuffer, 0, sizeof(ReadBuffer));
		return info;
	}

	// Закрыть порт
	bool ClosePort() {
		return CloseHandle(device);
	}
};

void Config(Keithley* device, std::string Source, float SourceValue, float ProtValue) {
	transform(Source.begin(), Source.end(), Source.begin(), ::toupper);
	if (device->GetPort() == INVALID_HANDLE_VALUE) {
		device->SetEnable(false);
		device->SetName("PORT UNAVALIABLE!");
		device->ClosePort();
		return;
	}
	else {
		device->ConfigPort();
		if (!(device->IsOn())) {
			device->SetEnable(false);
			device->SetName("DEVICE UNAVALIABLE!");
			device->ClosePort();
		}
		else {
			device->SetFunc(Source);
			if (Source == VOLT) {
				if (device->SetVolt(SourceValue)) device->SetCurrProt(ProtValue);
				else {
					device->SetEnable(false);
					device->ClosePort();
				}
			}
			else if (Source == CURR) {
				if (device->SetCurr(SourceValue)) device->SetVoltProt(ProtValue);
				else {
					device->SetEnable(false);
					device->ClosePort();
				}
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
	}	
}

void Stop(Keithley* obj) {
	obj->OutputOff();
	obj->ClosePort();
}

void Begin() {
	std::vector<Keithley*> Devices;
	int port;
	long long cycles;
	std::string source;
	float source_value, prot_value;
	std::string file_to_save;
	std::string text;
	bool infinity = false;

	auto RemoveCondition = [](Keithley* obj) {return !(obj->GetEnable()); };

	int quantity_devices = getInput<int>("Number of devices", true);

	for (int i = 0; i < quantity_devices; i++) {
		port = getInput<int>("COM - port number (0..20)", true);
		source = getInput<std::string>("Source Type (Volt, Curr)", true);
		source_value = getInput<float>("Source value (V, mA)");
		prot_value = getInput<float>("Protection value (V, mA)");
		Keithley* device = new Keithley(port);
		Config(device, source, source_value, prot_value);
		Devices.push_back(device);
	}

	Devices.erase(std::remove_if(Devices.begin(), Devices.end(), RemoveCondition), Devices.end());
	Devices.shrink_to_fit();

	//Select Cycles
	do {
		std::cout << "Select: finite number of dimensions (num) or inf: ";
		std::string select_meas;
		std::cin >> select_meas;
		std::transform(select_meas.begin(), select_meas.end(), select_meas.begin(), ::toupper);
		if (select_meas == "NUM") {
			cycles = getInput<long long>("Number of measurements", true);
			infinity = false;
			break;
		}
		else if (select_meas == "INF") {
			//cycles = INFINITY;
			infinity = true;
			break;
		}		
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "You entered an incorrect value!\n";

		}
	} while (true);
	system("cls");
	
	file_to_save = getInput<std::string>("The name of the file to save the measurements", false);
	file_to_save += ".txt";

	if (Devices.empty()) {
		std::cout << "No avaliable devices!\n";
	} 
	else {
		std::ofstream OutFile(file_to_save, std::ios_base::app);
		int first = 0;

		for (auto& obj : Devices) {
			obj->OutputOn();
		}

		Sleep(200);

		for (auto& obj : Devices) {
			obj->SetMeas();
		}

		if (OutFile.is_open()) {
			bool exit = false;
			// infinity mode
			if (infinity) {
				long long i = 1;
				while (!exit) {
					if (_kbhit()) {
						switch (_getch()) {
						case 'x':
							exit = true;
							break;
						}
					}
					setcur(0, 0);
					std::cout << "Measurment #" << i << std::endl;
					OutFile << "Measurment #" << i << '\n';
					if (!Devices.empty()) {
						for (auto& obj : Devices) {
							if (obj->WriteToPort(":READ?\n")) {
								text = obj->ReadVoltCurr();
								std::cout << text;
								OutFile << text;
								if (&obj == &Devices.back()) {
									std::cout << std::string(80, '=') << std::endl;
									OutFile << std::string(80, '=') << '\n';
								}
								else {
									std::cout << std::string(80, '-') << std::endl;
									OutFile << std::string(80, '-') << '\n';
								}
							}
							else {
								obj->SetEnable(false);
								obj->ClosePort();
								Devices.erase(std::remove_if(Devices.begin(), Devices.end(), RemoveCondition), Devices.end());
								Devices.shrink_to_fit();
							}
						}
						i++;
						Sleep(DELAY);
					}
					else {
						std::cout << "No avaliable devices!\n";
						break;
					}
				}
			}
			// cycles mode
			else {
				for (long long i = 1; i <= cycles; i++) {
					if (!exit) {
						if (_kbhit()) {
							switch (_getch()) {
							case 'x':
								exit = true;
								break;
							}
						}
						setcur(0, 0);
						std::cout << "Measurment #" << i << std::endl;
						OutFile << "Measurment #" << i << '\n';
						for (auto& obj : Devices) {
							if (obj->WriteToPort(":READ?\n")) {
								text = obj->ReadVoltCurr();
								std::cout << text;
								OutFile << text;
								if (&obj == &Devices.back()) {
									std::cout << std::string(100, '=') << std::endl;
									OutFile << std::string(100, '=') << '\n';
								}
								else {
									std::cout << std::string(100, '-') << std::endl;
									OutFile << std::string(100, '-') << '\n';
								}
							}
							else {
								obj->SetEnable(false);
								obj->ClosePort();
							}
						}
						Sleep(DELAY - 100);
					}
					else {
						break;
					}
				}
			}			
			OutFile.close();
		}
		else {
			std::cerr << "Can't open or create file!\n";
		}
		
		Sleep(10);
		for (auto& obj : Devices) {
			Stop(obj);
		}
	}	

	//Clear vector of devices
	//Devices.erase(std::remove(Devices.begin(), Devices.end(), nullptr));
	for (auto obj : Devices) {
		delete obj;
	}
	Devices.clear();
	system("pause");
}