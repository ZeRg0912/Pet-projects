#include "Keithley.h"

// Открыть порт
PORT Keithley::OpenPort(int portName) {
	PORT port{};
	wsprintf(comname, TEXT("\\\\.\\COM%d"), portName);
	//std::wstring wide_port_name(comname);
	//port_name.resize(wide_port_name.size());
	//std::copy(wide_port_name.begin(), wide_port_name.end(), port_name.begin());
	PortName = "COM - Port #" + std::to_string(portName) + '\n';

	// Открытие COM-порта
	return CreateFile(comname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
}





// Команда записи
bool Keithley::WriteToPort(std::string command) {
	DWORD bytesWritten;
	return WriteFile(device, command.c_str(), strlen(command.c_str()), &bytesWritten, NULL);
}

// Команда чтения
bool Keithley::ReadFromPort() {
	DWORD bytesRead;
	return ReadFile(device, ReadBuffer, sizeof(ReadBuffer), &bytesRead, NULL);
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





// Сбросить время
bool Keithley::ResetTime() {
	return WriteToPort("SYST:TIME:RES\n");
}

// Сброс
bool Keithley::RST() {
	return WriteToPort("*RST\n");
}

// Включить выход
bool Keithley::OutputOn() {
	return WriteToPort(":OUTP ON\n");
}

// Выключить выход
bool Keithley::OutputOff() {
	return WriteToPort(":OUTP OFF\n");
}

// Выбор режима
bool Keithley::SetFunc(std::string data) {
	std::string command = ":SOUR:FUNC " + data + "\n";
	WriteToPort(command.c_str());
	command = ":SOUR:" + std::string(data) + ":MODE FIXED\n";
	return WriteToPort(command.c_str());
}

// Установка скорости чтения
bool Keithley::SetReadSpeed(float value) {
	std::string command = ":SENS:VOLT:NPLC " + std::to_string(value) + "\n";
	std::replace(command.begin(), command.end(), ',', '.');
	return WriteToPort(command.c_str());
}





// ИСТОЧНИК НАПРЯЖЕНИЯ
//
//  Установить значение напряжения
bool Keithley::SetVolt(float value) {
	std::string command = ":SOUR:VOLT " + std::to_string(value) + "\n";
	std::replace(command.begin(), command.end(), ',', '.');
	//WriteToPort("SOUR:DEL:AUTO ON\n");
	return WriteToPort(command.c_str());
}

// Установить значение лимита тока
bool Keithley::SetCurrProt(float value) {
	std::string command = ":SENS:CURR:RANG:AUTO ON\n";
	WriteToPort(command.c_str());

	command = ":SENS:CURR:RANG" + std::to_string(value / 500) + "\n";
	//std::cout << value / 100 << std::endl;
	//WriteToPort(command.c_str());

	command = ":SENS:CURR:PROT " + std::to_string(value / 1000) + "\n";
	std::replace(command.begin(), command.end(), ',', '.');
	return WriteToPort(command.c_str());
}





// ИСТОЧНИК ТОКА
// 
// Установить значение тока
bool Keithley::SetCurr(float value) {
	std::string command = ":SOUR:CURR " + std::to_string(value / 1000) + "\n";
	std::replace(command.begin(), command.end(), ',', '.');
	return WriteToPort(command.c_str());
}

// Установить значение лимита напряжения
bool Keithley::SetVoltProt(float value) {
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





// Команды отображения на приборе
char* Keithley::DisplayVolts() {
	WriteToPort(":MEAS:VOLT?\n");
	//ReadFromPort();
	return ReadBuffer;
}

char* Keithley::DisplayCurr() {
	WriteToPort(":MEAS:CURR?\n");
	//ReadFromPort();
	return ReadBuffer;
}





// Команда чтения
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

void Keithley::SetMeas() {
	this->ResetTime();
	WriteToPort(":FORM:ELEM VOLT, CURR, TIME\n");
	WriteToPort(":SENSE:FUNC 'VOLT', 'CURR'\n");
	WriteToPort(":READ?\n");
	Sleep(100);
}

std::string Keithley::ReadVoltCurr(int cycle) {
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





// Закрыть порт
bool Keithley::ClosePort() {
	return CloseHandle(device);
}





//void Init(int numPort, std::string Source, float SourceValue, float ProtValue, int Cycles) {
//	Keithley device(numPort);
//	transform(Source.begin(), Source.end(), Source.begin(), ::toupper);
//	/*if (!device.OpenPort(numPort)) {
//		std::cout << "Can't open COMport\n";
//		return;
//	}*/
//	device.ConfigPort();
//	device.SetFunc(Source);
//	if (Source == VOLT) {
//		device.SetVolt(SourceValue);
//		device.SetCurrProt(ProtValue);
//	}
//	else if (Source == CURR) {
//		device.SetCurr(SourceValue);
//		device.SetVoltProt(ProtValue);
//	}
//	else {
//		std::cout << "INCORRECT SOURCE TYPE\n";
//		device.ClosePort();
//		return;
//	}
//	device.SetReadSpeed(0.01);
//	device.ResetTime();
//	device.OutputOn();
//	Sleep(300);
//
//	device.SetMeas();
//	for (int i = 1; i <= Cycles; i++) {
//		std::cout << device.ReadVoltCurr(i) << std::endl;
//	}
//	Sleep(5);
//
//	device.OutputOff();
//
//	device.ClosePort();
//}





void Config(Keithley* device, std::string Source, float SourceValue, float ProtValue) {
	transform(Source.begin(), Source.end(), Source.begin(), ::toupper);
	if (device->GetPort() == INVALID_HANDLE_VALUE) {
		device->SetEnable(false);
		device->ClosePort();
		device->SetName("Порт НЕДОСТУПЕН!");
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
	std::cout << obj->ReadVoltCurr(cycle) << std::endl;
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

	int quantity_devices = getInput<int>("Кол - во приборов", true);

	for (int i = 0; i < quantity_devices; i++) {
		port = getInput<int>("Номер COM - порта (0..20)", true);
		source = getInput<std::string>("Тип источника (Volt, Curr)",false ,{"VOLT", "CURR"});
		source_value = getInput<float>("Значение источника (В, мА)");
		prot_value = getInput<float>("Ограничение (В, мА)");
		Keithley* device = new Keithley(port);
		Config(device, source, source_value, prot_value);
		Devices.push_back(device);
	}
	Devices.erase(std::remove_if(Devices.begin(), Devices.end(), RemoveCondition), Devices.end());
	//Devices.shrink_to_fit();

	cycles = getInput<int>("Кол - во измерений: ", true);

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
			}
		}
		Sleep(10);
		for (auto& obj : Devices) {
			Stop(obj);
		}
	}
	else {
		std::cout << "Нет доступных устройств!\n";
	}
}

void setcur(int x, int y)//установка курсора на позицию  x y
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};