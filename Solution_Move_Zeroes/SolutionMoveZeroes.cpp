#include <iostream>
#include <string>

using namespace std;

void printArr(int* arr) {
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int arr[5]{0, 2, 4, 0, 5};

    int index = 0;

    printArr(arr);

    for (int i = 0; i < 5; i++) {
        if (arr[i] != 0) {
            arr[index++] = arr[i];
        }
    }

    while (index < 5) {
        arr[index++] = 0;
    }

    printArr(arr);
    
    return 0;
}

