#include "RacingLib.h"

int setDistance() {
	int distance;
	do {
		std::cout << "������� ����� ��������� (������ ���� ������������): ";
		std::cin >> distance;
		system("cls");
		if (std::cin.fail() || distance <= 0) {
			std::cout << "������� ������������� �����!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else { break; }
	} while (distance <= 0);
	return distance;
}

void Race::printMenuTable() {
	std::cout << "����� ���������� � �������� ���������!" << std::endl;
	std::cout << "1. ����� ��� ��������� ����������" << std::endl;
	std::cout << "2. ����� ��� ���������� ����������" << std::endl;
	std::cout << "3. ����� ��� ��������� � ���������� ����������" << std::endl;
	std::cout << "�������� ��� �����: ";
}

void Race::doRestart(Race& race) {
	int restart;
	do {
		std::cout << "\n1. �������� ��� ���� �����" << std::endl;
		std::cout << "2. �����" << std::endl;
		std::cout << "�������� ��������: ";
		std::cin >> restart;
		system("cls");
		if (std::cin.fail()) {
			std::cout << "������� �����!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (restart < 1 || restart > 2) {
			std::cout << "�������� ����� �� ������!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else { break; }
	} while (restart < 1 || restart > 2);
	system("cls");
	switch (restart) {
	case 1:
		race.begin();
		break;
	}
}

void Race::begin() {
	int input;
	int distance;
	RaceAirGround* currentMode = nullptr;
	do {
		printMenuTable();
		std::cin >> input;
		system("cls");
		if (std::cin.fail()) {
			std::cout << "������� �����!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (input < 1 || input > 3) {
			std::cout << "�������� ����� �� ������!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else { break; }
	} while (!isdigit(input));
	if (currentMode != nullptr) delete currentMode;
	switch (input) {
	case 1:
		system("cls");
		distance = setDistance();
		currentMode = new RaceGround;
		currentMode->raceBegin(distance);
		break;
	case 2:
		system("cls");
		distance = setDistance();
		currentMode = new RaceAir;
		currentMode->raceBegin(distance);
		break;
	case 3:
		system("cls");
		distance = setDistance();
		currentMode = new RaceAirGround;
		currentMode->raceBegin(distance);
		break;
	}
	delete currentMode;
	doRestart(*this);
}