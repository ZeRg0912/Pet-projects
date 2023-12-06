#include <iostream>
#include <algorithm>

using namespace std;

// Разделение по схеме Lomuto
int partition(int a[], int start, int end)
{
    int middle = a[end];
    int middleIndex = start;
    for (int i = start; i < end; i++)
    {
        if (a[i] <= middle)
        {
            swap(a[i], a[middleIndex]);
			middleIndex++;
        }
    }
    swap(a[middleIndex], a[end]);
    return middleIndex;
}

// Процедура быстрой сортировки
void quicksort(int a[], int start, int end){
    if (start >= end) {
        return;
    }
    int middle = partition(a, start, end);
    quicksort(a, start, middle - 1);
    quicksort(a, middle + 1, end);
}

void findInArr(int arr[], int x) {
	int left = 0;
	int right = 5;
	int middle;
	bool find = false;
	int numFind;
	while (left < right) {
		middle = (left + right) / 2;
		if (arr[middle] == x) {
			cout << "Find x: " << middle;
			find = true;
			break;
		}
		else if (arr[middle] > x) right = middle - 1;
		else if (arr[middle] < x) left = middle + 1;
	}
	if (arr[left] == x) {
		cout << "Find x: " << left;
		find = true;
	}

	if (find) cout << " FIND ";
	else cout << " NOT FIND ";
}

int main() {
	int arr[6] = {53, 5, 22, 0, 1, 66};
	quicksort(arr, 0, 5);
	findInArr(arr, 53);
	return 0;
}