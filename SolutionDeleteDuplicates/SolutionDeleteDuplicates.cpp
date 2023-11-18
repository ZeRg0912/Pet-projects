#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void show(const vector<int>& in) {
	cout << "Массив: " << endl;
	for (auto i : in) {
		cout << i << " ";
	}
	cout << endl;
}

void deleteDuplicate(const vector<int>& in) {
	for (auto i : in) {

	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");
	system("cls");

	vector<int> src {1, 2, 3, 4, 5, 22, 3, 5, 1, 22, 3, 5, 1, 22, 1, 2};
	show(src);
	sort(src.begin(), src.end());
	auto last = unique(src.begin(), src.end());
	src.erase(last, src.end());
	show(src);
	return 0;
}