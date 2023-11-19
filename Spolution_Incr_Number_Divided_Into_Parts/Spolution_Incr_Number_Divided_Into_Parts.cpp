#include <iostream>
#include <vector>
using namespace std;

vector<int> int_to_array(int number) {
	int tmp_number = number;
	int size = 0;
	do {
		tmp_number /= 10;
		size++;
	} while (tmp_number > 0);
	vector<int> array(size);
	tmp_number = number;
	for (int i = array.size() - 1; i >= 0; i--) {
		array[i] = tmp_number % 10;
		tmp_number /= 10;
	}
	return array;
}

void Solution(vector<int>& array, int size, int incr) {
	size -= 1;
	array[size] += incr;
	if (array[size] >= 10) {
		int temp_num = array[size] / 10;
		array[size] = array[size] % 10;
		Solution(array, size, temp_num);
	}
}

void show(vector<int> array) {
	for (int i = 0; i < array.size(); ++i) {
		cout << array[i] << " ";
	}
	cout << endl;
}

int main()
{
	int number = 1289;
	vector<int> array = int_to_array(number);
	show(array);
	Solution(array, array.size(), 582);
	show(array);

	return 0;
}