#include <iostream>
using namespace std;

void Solution(int* array, int size, int incr) {
	size -= 1;
	array[size] += incr;
	if (array[size] >= 10) {
		int temp_num = array[size] / 10;
		array[size] = array[size] % 10;
		Solution(array, size, temp_num);
	}
}

void show(int* arr, int size) {
	for (int i = 0; i < size; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main()
{
	int array[] = {1, 2, 8, 9};
	int size = sizeof(array) / sizeof(array[0]);
	show(array, size);
	Solution(array, size, 1572);
	show(array, size);

	return 0;
}