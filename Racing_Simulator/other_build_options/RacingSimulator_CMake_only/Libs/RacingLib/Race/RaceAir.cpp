#include "RaceAir.h"

enum class airTransport {
	stick = 1, eagle, magicCarpet
};

void RaceAir::printRegisterTableMenu(int distance) {
	std::cout << "����� ��� ���������� ����������. ����������: " << distance << std::endl;
	std::cout << "1. �����" << std::endl;
	std::cout << "2. ����" << std::endl;
	std::cout << "3. ����� - �������" << std::endl;
	std::cout << "�������� ��������� ��� 0 ��� ��������� �������� �����������: ";
}

std::vector<TRANSPORT*> RaceAir::createTransports(std::vector<TRANSPORT*>& transportsForRace, int distance) {
	airTransport typeTransport;
	int type;
	do {
		do {
			printLastRegistredTransport(transportsForRace);
			printRegisterTableMenu(distance);
			std::cin >> type;
			system("cls");
			if (std::cin.fail()) {
				std::cout << "������� �����!" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else if (type < 0 || type > 3) {
				std::cout << "������� ����� �� ������!" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else { break; }
		} while (!isdigit(type));
		typeTransport = static_cast<airTransport>(type);
		system("cls");
		switch (typeTransport) {
		case airTransport::stick:
			registerTransport(transportsForRace, new BROOMSTICK());
			break;
		case airTransport::eagle:
			registerTransport(transportsForRace, new EAGLE());
			break;
		case airTransport::magicCarpet:
			registerTransport(transportsForRace, new MAGIC_CARPET());
			break;
		}
	} while (type != 0);
	return transportsForRace;
}