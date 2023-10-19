#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
//#include <unistd.h> 

using namespace std;

int HEIGHT = 9;
int WIDTH = 9;
int i_start = 0;
int j_start = 0;

int NUMOFMINES = 3;

bool boom = false;
bool win = false;

int** CreateField(int HEIGHT, int WIDTH) {
    int** Field = new int* [HEIGHT];
    for (int i = 0; i < HEIGHT; i++) {
        Field[i] = new int[WIDTH];
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            Field[i][j] = 0;
        }
    }

    return Field;
}

bool** CheckOpenField(int HEIGHT, int WIDTH) {
    bool** Field = new bool* [HEIGHT];
    for (int i = 0; i < HEIGHT; i++) {
        Field[i] = new bool[WIDTH];
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            Field[i][j] = false;
        }
    }

    return Field;
}

void FillField(int** Field) {
    srand(time(nullptr));
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (rand() % 10 == 0 && NUMOFMINES > 0) {
                Field[i][j] = 10;
                NUMOFMINES--;
            }
            else {
                Field[i][j] = 0;
            }
        }
    }
}

void ShowField(int** Field, bool** openField) {
    for (int i = 0; i < HEIGHT; i++) {
        if (i == 0) {
            cout << "   ";
            for (int num_WIDTH = 1; num_WIDTH < WIDTH + 1; num_WIDTH++) {
                if (num_WIDTH < 10) {
                    cout << "0";
                }
                else if (num_WIDTH >= 10) {
                    cout << num_WIDTH / 10;
                }
            }
            cout << endl;
            cout << "   ";
            for (int num_WIDTH = 1; num_WIDTH < WIDTH + 1; num_WIDTH++) {
                if (num_WIDTH < 10) {
                    cout << num_WIDTH;
                }
                else if (num_WIDTH >= 10) {
                    cout << num_WIDTH % 10;
                }
            }
            cout << endl;
            cout << "  ";
            for (int border = 0; border < WIDTH + 2; border++) {
                cout << "=";
            }
            cout << endl;
        }
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) {
                if (i < 9) {
                    cout << " " << i + 1 << "|";
                }
                else {
                    cout << i + 1 << "|";
                }
            }
            if (openField[i][j]) {
                switch (Field[i][j]) {
                case 0:
                    cout << " ";
                    break;
                case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
                    cout << Field[i][j];
                    break;
                case 10:
                    cout << "*";
                    break;
                case 11:
                    cout << "-";
                    break;
                }
            }
            else {
                cout << " ";
            }
            if (j == WIDTH - 1) {
                cout << "|" << i + 1;
            }
        }
        cout << endl;
        if (i == HEIGHT - 1) {
            cout << "  ";
            for (int border = 0; border < WIDTH + 2; border++) {
                cout << "=";
            }
            cout << endl;
            cout << "   ";
            for (int num_WIDTH = 1; num_WIDTH < WIDTH + 1; num_WIDTH++) {
                if (num_WIDTH < 10) {
                    cout << "0";
                }
                else if (num_WIDTH >= 10) {
                    cout << num_WIDTH / 10;
                }
            }
            cout << endl;
            cout << "   ";
            for (int num_WIDTH = 1; num_WIDTH < WIDTH + 1; num_WIDTH++) {
                if (num_WIDTH < 10) {
                    cout << num_WIDTH;
                }
                else if (num_WIDTH >= 10) {
                    cout << num_WIDTH % 10;
                }
            }
            cout << endl;
        }
    }
}

void CheckMines(int** Field) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            // Определение кол-ва мин рядом
            int minesNear = 0;
            if (Field[i][j] == 0) {
                if ((i > 0) && (j > 0))                  minesNear += (Field[i - 1][j - 1]) / 10;
                if (i > 0)                               minesNear += (Field[(i - 1)][(j)]) / 10;
                if ((i > 0) && (j < WIDTH - 1))          minesNear += (Field[(i - 1)][(j + 1)]) / 10;
                if (j > 0)                               minesNear += (Field[(i)][(j - 1)]) / 10;
                if (j < WIDTH - 1)                       minesNear += (Field[(i)][(j + 1)]) / 10;
                if ((i < HEIGHT - 1) && (j > 0))         minesNear += (Field[(i + 1)][(j - 1)]) / 10;
                if (i < HEIGHT - 1)                      minesNear += (Field[(i + 1)][(j)]) / 10;
                if ((i < HEIGHT - 1) && (j < WIDTH - 1)) minesNear += (Field[(i + 1)][(j + 1)]) / 10;
                if (minesNear > 0) Field[i][j] = minesNear;
            }
        }
    }
}

void DeleteIntField(int** Field) {
    for (int i = 0; i < HEIGHT; i++) {
        delete[] Field[i];
    }
    delete[] Field;
}

void DeleteBoolField(bool** Field) {
    for (int i = 0; i < HEIGHT; i++) {
        delete[] Field[i];
    }
    delete[] Field;
}

void CheckField(int** Field, int** tmpField, bool** openField, int i, int j) {
    tmpField[i][j] = Field[i][j];
    if (tmpField[i][j] == 10) {
        boom = true;
    }
    else {
        if ((i > 0) && (i < HEIGHT)) {
            if ((j > 0) && (j < WIDTH)) {
                if (!openField[i][j]) {
                    openField[i][j] = true;
                    if (tmpField[i][j] == 0) {
                        CheckField(Field, tmpField, openField, i - 1, j - 1);
                        CheckField(Field, tmpField, openField, i - 1, j);
                        CheckField(Field, tmpField, openField, i - 1, j + 1);
                        CheckField(Field, tmpField, openField, i - 1, j + 1);
                        CheckField(Field, tmpField, openField, i, j - 1);
                        CheckField(Field, tmpField, openField, i, j + 1);
                        CheckField(Field, tmpField, openField, i + 1, j - 1);
                        CheckField(Field, tmpField, openField, i + 1, j);
                        CheckField(Field, tmpField, openField, i + 1, j + 1);
                    }
                }
            }
        }
    }    
}

void CheckFieldWin(int** Field, int** tmpField) {
    bool similar = false;
    int numOfSimilar = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (((Field[i][j] == tmpField[i][j]) || (tmpField[i][j] == 11)) || ((Field[i][j] == 10) && (tmpField[i][j] != 10))) {
                numOfSimilar++;
            }
            else if ((Field[i][j] != tmpField[i][j])) {

            }
        }
        if (numOfSimilar == (HEIGHT * WIDTH)) similar = true;
        if ((similar == true) && (boom == false)) {
            win = true;
        }
        else {
            win = false;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian"); // задаём русский текст
    system("chcp 1251"); // настраиваем кодировку консоли
    system("cls");
    int** Field = CreateField(HEIGHT, WIDTH);
    int** tmpField = CreateField(HEIGHT, WIDTH);
    bool** openField = CheckOpenField(HEIGHT, WIDTH);
    FillField(Field);
    CheckMines(Field);
    for (int i = 0; i < ((WIDTH / 2) - (WIDTH / 5)); i++) {
        cout << " ";
    }
    cout << " Игра сапер: " << endl;
    cout << endl;
    ShowField(tmpField, openField);
    do {
        int i, j;
        do {
            cout << endl;
            for (int i = 0; i < ((WIDTH / 2) - (WIDTH / 3) + 1); i++) {
                cout << " ";
            }
            cout << "Введите номер ряда: ";
            cin >> i;
            for (int i = 0; i < ((WIDTH / 2) - (WIDTH / 3) + 1); i++) {
                cout << " ";
            }
            cout << "Введите номер столбца: ";
            cin >> j;
            if ((i < 1 || i > HEIGHT) || (j < 1 || j > WIDTH)) cout << "Неверные координаты. Попробуйте еще раз." << endl;
        } while ((i < 1 || i > HEIGHT) || (j < 1 || j > WIDTH));
        i -= 1;
        j -= 1;
        i_start = i;
        j_start = j;
        //sleep(1);    
        system("cls");
        CheckField(Field, tmpField, openField, i, j);
        for (int i = 0; i < ((WIDTH / 2) - (WIDTH / 5)); i++) {
            cout << " ";
        }
        cout << " Игра сапер: " << endl;
        cout << endl;
        ShowField(tmpField, openField);
        CheckFieldWin(Field, tmpField);
        if (win || boom) system("cls");
    } while (!(win || boom));
    for (int i = 0; i < ((WIDTH / 2) - (WIDTH / 5)); i++) {
        cout << " ";
    }
    cout << " Игра сапер: " << endl;
    cout << endl;
    if (boom) {
        ShowField(tmpField, openField);
        for (int i = 0; i < ((WIDTH / 2) - (WIDTH / 4)); i++) {
            cout << " ";
        }
        cout << endl;
        cout << " Вы проиграли!!!" << endl;
    }
    if (win) {
        ShowField(Field, openField);
        for (int i = 0; i < ((WIDTH / 2) - (WIDTH / 4)); i++) {
            cout << " ";
        }
        cout << endl;
        cout << " Вы победили!!!" << endl;
    }
    DeleteBoolField(openField);
    DeleteIntField(Field);
    DeleteIntField(tmpField);
    return 0;
}