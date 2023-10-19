// Miner_last.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>

using namespace std;

int rows = 9;     //ряды
int cols = 9;     //столбцы

int numMines = 9; //кол-во мин
int checkMinesWin = 0;

bool win = false;
bool boom = false;

int** createIntArray(int rows, int cols) {
    int** Array = new int* [rows];
    for (int i = 0; i < rows; i++) {
        Array[i] = new int [cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Array[i][j] = 0;
        }
    }
    return Array;
}

bool** createBoolArray(int rows, int cols) {
    bool** Array = new bool* [rows];
    for (int i = 0; i < rows; i++) {
        Array[i] = new bool [cols] {false};
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Array[i][j] = false;
        }
    }
    return Array;
}

void fillIntArray(int** Array) {
    srand(time(nullptr));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (rand() % 10 == 0 && numMines > 0) {
                Array[i][j] = 9;
                numMines--;
                checkMinesWin++;
            }
            else {
                Array[i][j] = 0;
            }
        }
    }
    // Определение кол-ва мин рядом
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int minesNear = 0;
            if (Array[i][j] == 0) {
                if ((i > 0) && (j > 0))               minesNear += (Array[i - 1][j - 1]) / 9;
                if (i > 0)                            minesNear += (Array[(i - 1)][(j)]) / 9;
                if ((i > 0) && (j < cols - 1))        minesNear += (Array[(i - 1)][(j + 1)]) / 9;
                if (j > 0)                            minesNear += (Array[(i)][(j - 1)]) / 9;
                if (j < cols - 1)                     minesNear += (Array[(i)][(j + 1)]) / 9;
                if ((i < rows - 1) && (j > 0))        minesNear += (Array[(i + 1)][(j - 1)]) / 9;
                if (i < rows - 1)                     minesNear += (Array[(i + 1)][(j)]) / 9;
                if ((i < rows - 1) && (j < cols - 1)) minesNear += (Array[(i + 1)][(j + 1)]) / 9;
                if (minesNear > 0) Array[i][j] = minesNear;
            }
        }
    }
}

void deleteIntArray(int** Array) {
    for (int i = 0; i < rows; i++) {
        delete[] Array[i];
    }
    delete[] Array;
}

void deleteBoolArray(bool** Array) {
    for (int i = 0; i < rows; i++) {
        delete[] Array[i];
    }
    delete[] Array;
}

void showField(int** play, bool** open) {
    for (int i = 0; i < rows; i++) {
        // перед первой строкой
        if (i == 0) {
            cout << "    ";
            for (int num = 1; num <= cols; num++) {
                if (num > 0 && num < 10) {
                    cout << "  ";
                }
                else {
                    cout << num / 10 << " ";
                }
            }
            cout << endl;
            cout << "    ";
            for (int num = 1; num <= cols; num++) {
                if (num > 0 && num < 10) {
                    cout << num << " ";
                }
                else {
                    cout << num % 10 << " ";
                }
            }
            cout << endl;
            cout << "    ";
            for (int border = 0; border < (2 * cols) - 1; border++) {
                cout << "=";
            }
            cout << endl;
        }
        // начало каждой строки
        if (i < 9) {
            cout << " " << i + 1 << "||";
        }
        else {
            cout << i + 1 << "||";
        }

        // прокрут ячеек
        for (int j = 0; j < cols; j++) {
            if (open[i][j] == true) {
                switch (play[i][j])
                {
                case 9:
                    cout << '*';
                    break;

                case 0:
                    cout << " ";
                    break;

                case 10:
                    cout << "-";
                    break;

                default:
                    cout << play[i][j];
                }
                if (j < cols - 1) cout << " ";
            }
            else {
                cout << " ";
                if (j < cols - 1) cout << " ";
            }
        }

        // конец каждой строки
        if (i < 9) {
            cout << "||" << i + 1 << " ";
        }
        else {
            cout << "||" << i + 1;
        }
        cout << endl;
        // после последней строки
        if (i == rows - 1) {
            cout << "    ";
            for (int border = 0; border < (2 * cols) - 1; border++) {
                cout << "=";
            }
            cout << endl;
            cout << "    ";
            for (int num = 1; num <= cols; num++) {
                if (num > 0 && num < 10) {
                    cout << num << " ";
                }
                else {
                    cout << num % 10 << " ";
                }
            }
            cout << endl;
            cout << "    ";
            for (int num = 1; num <= cols; num++) {
                if (num > 0 && num < 10) {
                    cout << "  ";
                }
                else {
                    cout << num / 10 << " ";
                }
            }
        }
    }
}

void clean(int** play, bool** open, int i, int j) {
    if ((i >= 0) && (i < rows)){
        if ((j >= 0) && (j < cols)) {
            if (!open[i][j]) {
                open[i][j] = true;
                if (play[i][j] == 0) {
                    play[i][j] = 10;
                    clean(play, open, i - 1, j - 1);
                    clean(play, open, i - 1, j);
                    clean(play, open, i - 1, j + 1);
                    clean(play, open, i, j - 1);
                    clean(play, open, i, j + 1);
                    clean(play, open, i + 1, j - 1);
                    clean(play, open, i + 1, j);
                    clean(play, open, i + 1, j + 1);
                }
            }                
        }
    }
}

void checkWin (int** play, bool** open) {
    bool similar = false;
    int numOfSimilar = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (open[i][j] && play[i][j] != 9) {
                numOfSimilar++;
            }
        }
        if ((numOfSimilar) == ((rows * cols) - checkMinesWin)) similar = true;
        if ((similar == true) && (boom == false)) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    open[i][j] = true;
                }
            }
            win = true;
        }
    }
}


int main()
{
    setlocale(LC_ALL, "Russian"); // задаём русский текст
    system("chcp 1251"); // настраиваем кодировку консоли

    int** playingField = createIntArray(rows, cols);
    bool** openField = createBoolArray(rows, cols);

    fillIntArray(playingField);
    system("cls");

    cout << " Игра сапер: " << endl;
    cout << endl;
    showField(playingField, openField);
    do {
        int i, j;
        do {
            cout << endl;
            cout << "Введите номер ряда: ";
            cin >> i;
            cout << "Введите номер столбца: ";
            cin >> j;
            if ((i < 1 || i > rows) || (j < 1 || j > cols)) cout << "Неверные координаты. Попробуйте еще раз." << endl;
        } while ((i < 1 || i > rows) || (j < 1 || j > cols));
        i -= 1;
        j -= 1;
        //sleep(1);    
        system("cls");
        if (playingField[i][j] == 9) {
            openField[i][j] = true;
            boom = true;
        }
        else {
            clean(playingField, openField, i, j);
            for (int i = 0; i < ((cols / 2) - (cols / 5)); i++) {
                cout << " ";
            }
            cout << " Игра сапер: " << endl;
            cout << endl;
            showField(playingField, openField);
            checkWin(playingField, openField);
        }        
        if (win || boom) system("cls");
    } while (!(win || boom));
    cout << " Игра сапер: " << endl;
    cout << endl;
    if (boom) {
        showField(playingField, openField);
        for (int i = 0; i < ((rows / 2) - (cols / 4)); i++) {
            cout << " ";
        }
        cout << endl;
        cout << " Вы проиграли!!!" << endl;
    }
    if (win) {
        showField(playingField, openField);
        for (int i = 0; i < ((rows / 2) - (cols / 4)); i++) {
            cout << " ";
        }
        cout << endl;
        cout << " Вы победили!!!" << endl;
    }
    deleteIntArray(playingField);
    deleteBoolArray(openField);
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
