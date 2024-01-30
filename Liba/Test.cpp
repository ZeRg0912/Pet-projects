#include <iostream>
#include "Liba.h"

using namespace std;

int main() {
	auto num = 0;

	do {
		cout << "Put number: ";
		cin >> num;
		if (CinCheck(num, "int")) cout << "WRONG\n";
		else break;
	} while(CinCheck(num, "int"));

	return 0;
}