#include "RaceAirGround.h"

enum class allTransport {
	boots = 1, stick, camel, centaur, eagle, fastCamel, magicCarpet
};

void RaceAirGround::printRegisterTableMenu() {
	std::cout << "1. ������� - ���������" << std::endl;
	std::cout << "2. �����" << std::endl;
	std::cout << "3. �������" << std::endl;
	std::cout << "4. �������" << std::endl;
	std::cout << "5. ����" << std::endl;
	std::cout << "6. ������� - ���������" << std::endl;
	std::cout << "7. ����� - �������" << std::endl;
	std::cout << "�������� ��������� ��� 0 ��� ��������� �������� �����������: ";
}

void RaceAirGround::printResultTable(std::vector<TRANSPORT*>& arr) {
	system("cls");
	int num = 1;
	std::cout << "���������� �����: " << std::endl;
	for (const auto& obj : arr) {
		std::cout << num << ". " << obj->getName() << ". �����: " << obj->getDistanceTime() << std::endl;
		num++;
	}
}

void RaceAirGround::printRegistredTransports(std::vector<TRANSPORT*>& arr) {
	std::cout << "������������������ ������������ ��������: ";
	int lastIndex = 0;
	for (const auto& obj : arr) {
		std::cout << obj->getName();
		if (lastIndex != arr.size() - 1) std::cout << ", ";
		lastIndex++;
	}
	std::cout << std::endl;
}

void RaceAirGround::printLastRegistredTransport(std::vector<TRANSPORT*>& transportsForRace) {
	if (transportsForRace.size()) {
		printRegistredTransports(transportsForRace);
	}
}

void RaceAirGround::startRace(std::vector<TRANSPORT*>& arr, int distance) {
	std::cout << "����� ��������: " << distance << " ��." << std::endl;
	for (int i = 0; i < arr.size(); i++) {
		arr[i]->raceTime(distance);
	}
}

void RaceAirGround::raceTimeSort(std::vector<TRANSPORT*>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		TRANSPORT* key = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j]->getDistanceTime() > key->getDistanceTime()) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

void RaceAirGround::registerTransport(std::vector<TRANSPORT*>& transports, TRANSPORT* type) {
	bool registred = false;
	for (const auto& obj : transports) {
		if (obj->getName() == type->getName()) {
			registred = true;
			break;
		}
		else {
			registred = false;
		}
	}
	if (registred == false) {
		std::cout << "���������: " << type->getName() << " ������� ���������������!" << std::endl;
		transports.push_back(type);
	}
	else {
		std::cout << "��������� " << type->getName() << " ��� ���������������!" << std::endl;
	}
}

std::vector<TRANSPORT*> RaceAirGround::createTransports(std::vector<TRANSPORT*>& transportsForRace, int distance) {
	allTransport typeTransport;
	int type;
	do {
		do {
			std::cout << "����� ��� �������� � ���������� ����������. ����������: " << distance << std::endl;
			printLastRegistredTransport(transportsForRace);
			printRegisterTableMenu();
			std::cin >> type;
			system("cls");
			if (std::cin.fail()) {
				std::cout << "������� �����!" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else if (type < 0 || type > 7) {
				std::cout << "�������� ����� �� ������!" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else { break; }
		} while (!isdigit(type));
		typeTransport = static_cast<allTransport>(type);
		system("cls");
		switch (typeTransport) {
		case allTransport::boots:
			registerTransport(transportsForRace, new BOOTS());
			break;
		case allTransport::stick:
			registerTransport(transportsForRace, new BROOMSTICK());
			break;
		case allTransport::camel:
			registerTransport(transportsForRace, new CAMEL());
			break;
		case allTransport::centaur:
			registerTransport(transportsForRace, new CENTAUR());
			break;
		case allTransport::eagle:
			registerTransport(transportsForRace, new EAGLE());
			break;
		case allTransport::fastCamel:
			registerTransport(transportsForRace, new FAST_CAMEL());
			break;
		case allTransport::magicCarpet:
			registerTransport(transportsForRace, new MAGIC_CARPET());
			break;
		}
	} while (type != 0);
	return transportsForRace;
}

void RaceAirGround::clearTransports(std::vector<TRANSPORT*>& arr) {
	for (auto obj : arr) {
		delete obj;
	}
	arr.clear();
}

void RaceAirGround::raceBegin(int distance) {
	system("cls");
	std::vector<TRANSPORT*> transportsForRace;
	int input;
	do {
		do {
			if (transportsForRace.size() < 2) std::cout << "������ ���� ���������������� ���� �� 2 ������������ ��������" << std::endl;
			std::cout << "1. ���������������� ���������" << std::endl;
			if (transportsForRace.size() >= 2) std::cout << "2. ������ �����" << std::endl;
			std::cout << "�������� ��������: ";
			std::cin >> input;
			system("cls");
			if (std::cin.fail()) {
				std::cout << "�������� ����� �� ������!" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else { break; }
		} while (!isdigit(input) || (input != 1) || (input != 2));
		if (transportsForRace.size() >= 2) {
			switch (input) {
			case 1:
				transportsForRace = createTransports(transportsForRace, distance);
				break;
			case 2:
				if (transportsForRace.size() >= 2) startRace(transportsForRace, distance);
				break;
			default:
				std::cout << "�������� ����� �� ������!" << std::endl;
			}
		} else {
			switch (input) {
			case 1:
				transportsForRace = createTransports(transportsForRace, distance);
				break;
			default:
				std::cout << "�������� ����� �� ������!" << std::endl;
			}
		}
	} while (transportsForRace.size() < 2 || input != 2);
	raceTimeSort(transportsForRace);
	printResultTable(transportsForRace);
	clearTransports(transportsForRace);
}