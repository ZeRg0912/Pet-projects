#include <iostream>

int bits(int in) {
	int bits = 0;
	int temp = in;
	while (temp != 0x00) {
		temp = temp >> 1;
		bits++;
	}
	return bits;
}

int main() {
	int n = 0x55555;
	std::cout << bits(n) << std::endl;

	return 0;
}