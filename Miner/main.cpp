#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
//#include <unistd.h> 

using namespace std;

int HEIGHT = 20;
int WIDTH = 30;
int i_start = 0;
int j_start = 0;

int NUMOFMINES = 50;

bool boom = false;
bool win = false;
bool reverse_i = false;
bool reverse_j = false;

bool num7 = false;
bool num8 = false;
bool num9 = false;
bool num4 = false;
bool num6 = false;
bool num1 = false;
bool num2 = false;
bool num3 = false;

void CheckField_7(int** Field, int** tmpField, int i, int j);
void CheckField_8(int** Field, int** tmpField, int i, int j);
void CheckField_9(int** Field, int** tmpField, int i, int j);
void CheckField_4(int** Field, int** tmpField, int i, int j);
void CheckField_6(int** Field, int** tmpField, int i, int j);
void CheckField_1(int** Field, int** tmpField, int i, int j);
void CheckField_2(int** Field, int** tmpField, int i, int j);
void CheckField_3(int** Field, int** tmpField, int i, int j);

void CheckField_7_line(int** Field, int** tmpField, int i, int j);
void CheckField_8_line(int** Field, int** tmpField, int i, int j);
void CheckField_9_line(int** Field, int** tmpField, int i, int j);
void CheckField_4_line(int** Field, int** tmpField, int i, int j);
void CheckField_6_line(int** Field, int** tmpField, int i, int j);
void CheckField_1_line(int** Field, int** tmpField, int i, int j);
void CheckField_2_line(int** Field, int** tmpField, int i, int j);
void CheckField_3_line(int** Field, int** tmpField, int i, int j);

void CheckField_7_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_8_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_9_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_4_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_6_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_1_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_2_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_3_line_line(int** Field, int** tmpField, int i, int j);

void CheckField_7_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_8_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_9_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_4_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_6_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_1_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_2_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_3_line_line_line(int** Field, int** tmpField, int i, int j);

void CheckField_7_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_8_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_9_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_4_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_6_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_1_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_2_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_3_line_line_line_line(int** Field, int** tmpField, int i, int j);

void CheckField_7_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_8_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_9_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_4_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_6_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_1_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_2_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_3_line_line_line_line_line(int** Field, int** tmpField, int i, int j);

void CheckField_7_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_8_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_9_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_4_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_6_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_1_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_2_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_3_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j);

void CheckField_7_line_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_8_line_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_9_line_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_4_line_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_6_line_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_1_line_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_2_line_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j);
void CheckField_3_line_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j);

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

void ShowField(int** Field) {
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

void copyBoard(int** src, int** dst) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

void DeleteField(int** Field) {
    for (int i = 0; i < HEIGHT; i++) {
        delete[] Field[i];
    }
    delete[] Field;
}

void CheckField_backup(int** Field, int** tmpField, int i, int j) {
    int minesNear = 0;
    int i_tmp = 0;
    int j_tmp = 0;

    tmpField[i][j] = Field[i][j];

    if (tmpField[i][j] == 10) {
        boom = true;
    }
    else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
        tmpField[i][j] = 11;

        i = i_start;
        j = j_start;
        // num 7
        if ((i > 0) && (j > 0)) {
            while (((i > 0) && (j > 0)) && Field[i - 1][j - 1] != 10) {
                i--;
                j--;
                tmpField[i][j] = Field[i][j];
                if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
                    tmpField[i][j] = 11;
                }
                else {
                    tmpField[i][j] = Field[i][j];
                    break;
                }
            }
        }

        i = i_start;
        j = j_start;
        // num 8
        if ((i > 0)) {
            while ((i > 0) && Field[i - 1][j] != 10) {
                i--;
                tmpField[i][j] = Field[i][j];
                if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
                    tmpField[i][j] = 11;
                }
                else {
                    tmpField[i][j] = Field[i][j];
                    break;
                }
            }
        }

        i = i_start;
        j = j_start;
        // num 9
        if ((i > 0) && (j < WIDTH - 1)) {
            while (((i > 0) && (j < WIDTH - 1)) && Field[i - 1][j + 1] != 10) {
                i--;
                j++;
                tmpField[i][j] = Field[i][j];
                if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
                    tmpField[i][j] = 11;
                }
                else {
                    tmpField[i][j] = Field[i][j];
                    break;
                }
            }
        }

        i = i_start;
        j = j_start;
        // num 4
        if (j > 0) {
            while ((j > 0) && Field[i][j - 1] != 10) {
                j--;
                tmpField[i][j] = Field[i][j];
                if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
                    tmpField[i][j] = 11;
                }
                else {
                    tmpField[i][j] = Field[i][j];
                    break;
                }
            }
        }

        i = i_start;
        j = j_start;
        // num 6
        if (j < WIDTH - 1) {
            while ((j < WIDTH - 1) && Field[i][j + 1] != 10) {
                j++;
                tmpField[i][j] = Field[i][j];
                if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
                    tmpField[i][j] = 11;
                }
                else {
                    tmpField[i][j] = Field[i][j];
                    break;
                }
            }
        }

        i = i_start;
        j = j_start;
        // num 1
        if ((i < HEIGHT - 1) && (j > 0)) {
            while (((i < HEIGHT - 1) && (j > 0)) && Field[i + 1][j - 1] != 10) {
                i++;
                j--;
                tmpField[i][j] = Field[i][j];
                if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
                    tmpField[i][j] = 11;
                }
                else {
                    tmpField[i][j] = Field[i][j];
                    break;
                }
            }
        }

        i = i_start;
        j = j_start;
        // num 2
        if (i < HEIGHT - 1) {
            while ((i < HEIGHT - 1) && Field[i + 1][j] != 10) {
                i++;
                tmpField[i][j] = Field[i][j];
                if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
                    tmpField[i][j] = 11;
                }
                else {
                    tmpField[i][j] = Field[i][j];
                    break;
                }
            }
        }

        i = i_start;
        j = j_start;
        // num 3
        if ((i < HEIGHT - 1) && (j < WIDTH - 1)) {
            while (((i < HEIGHT - 1) && (j < WIDTH - 1)) && Field[i + 1][j + 1] != 10) {
                i++;
                j++;
                tmpField[i][j] = Field[i][j];
                if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
                    tmpField[i][j] = 11;
                }
                else {
                    tmpField[i][j] = Field[i][j];
                    break;
                }
            }
        }

    }
    else {
        tmpField[i][j] = Field[i][j];
    }

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
    }
}

void CheckField_7_line_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0) && (j >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num7 = false;
            i_tmp = i - 1;
            j_tmp = j - 1;
            if ((i_tmp > 0) && (j_tmp > 0) && num7 == false) {
                CheckField_7_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num7 = true;
        }
    }
}

void CheckField_8_line_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num8 = false;
            i_tmp = i - 1;
            j_tmp = j;
            if (i > 0 && num8 == false) {
                CheckField_8_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num8 = true;
        }
    }
}

void CheckField_9_line_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0) && (j <= WIDTH - 1)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num9 = false;
            i_tmp = i - 1;
            j_tmp = j + 1;
            if ((i > 0) && (j < WIDTH - 1) && num9 == false) {
                CheckField_9_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num9 = true;
        }
    }
}

void CheckField_4_line_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if (j >= 0) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num4 = false;
            i_tmp = i;
            j_tmp = j - 1;
            if (j > 0 && num4 == false) {
                CheckField_4_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num4 = true;
        }
    }
}

void CheckField_6_line_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;
    if (j <= WIDTH - 1) {
        tmpField[i][j] = Field[i][j];

        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num6 = false;
            i_tmp = i;
            j_tmp = j + 1;
            if (j < WIDTH - 1 && num6 == false) {
                CheckField_6_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num6 = true;
        }
    }
}

void CheckField_1_line_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i <= HEIGHT - 1) && (j >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num1 = false;
            i_tmp = i + 1;
            j_tmp = j - 1;
            if ((i < HEIGHT - 1) && (j > 0) && num1 == false) {
                CheckField_1_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num1 = true;
        }
    }
}

void CheckField_2_line_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if (i <= HEIGHT - 1) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num2 = false;
            i_tmp = i + 1;
            j_tmp = j;
            if (i < HEIGHT - 1 && num2 == false) {
                CheckField_2_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num2 = true;
        }
    }
}

void CheckField_3_line_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i <= HEIGHT - 1) && (j <= WIDTH - 1)) {
        tmpField[i][j] = Field[i][j];

        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num3 = false;
            i_tmp = i + 1;
            j_tmp = j + 1;
            if ((i < HEIGHT - 1) && (j < WIDTH - 1) && num3 == false) {
                CheckField_3_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num3 = true;
        }
    }
}

void CheckField_7_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0) && (j >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num7 = false;
            i_tmp = i - 1;
            j_tmp = j - 1;
            if ((i_tmp > 0) && (j_tmp > 0) && num7 == false) {
                CheckField_7_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num7 = true;
        }
    }
}

void CheckField_8_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num8 = false;
            i_tmp = i - 1;
            j_tmp = j;
            if (i > 0 && num8 == false) {
                CheckField_8_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num8 = true;
        }
    }
}

void CheckField_9_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0) && (j <= WIDTH - 1)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num9 = false;
            i_tmp = i - 1;
            j_tmp = j + 1;
            if ((i > 0) && (j < WIDTH - 1) && num9 == false) {
                CheckField_9_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num9 = true;
        }
    }
}

void CheckField_4_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if (j >= 0) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num4 = false;
            i_tmp = i;
            j_tmp = j - 1;
            if (j > 0 && num4 == false) {
                CheckField_4_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num4 = true;
        }
    }
}

void CheckField_6_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;
    if (j <= WIDTH - 1) {
        tmpField[i][j] = Field[i][j];

        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num6 = false;
            i_tmp = i;
            j_tmp = j + 1;
            if (j < WIDTH - 1 && num6 == false) {
                CheckField_6_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num6 = true;
        }
    }
}

void CheckField_1_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i <= HEIGHT - 1) && (j >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num1 = false;
            i_tmp = i + 1;
            j_tmp = j - 1;
            if ((i < HEIGHT - 1) && (j > 0) && num1 == false) {
                CheckField_1_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num1 = true;
        }
    }
}

void CheckField_2_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if (i <= HEIGHT - 1) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num2 = false;
            i_tmp = i + 1;
            j_tmp = j;
            if (i < HEIGHT - 1 && num2 == false) {
                CheckField_2_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num2 = true;
        }
    }
}

void CheckField_3_line_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i <= HEIGHT - 1) && (j <= WIDTH - 1)) {
        tmpField[i][j] = Field[i][j];

        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num3 = false;
            i_tmp = i + 1;
            j_tmp = j + 1;
            if ((i < HEIGHT - 1) && (j < WIDTH - 1) && num3 == false) {
                CheckField_3_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num3 = true;
        }
    }
}

void CheckField_7_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0) && (j >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num7 = false;
            i_tmp = i - 1;
            j_tmp = j - 1;
            if ((i_tmp > 0) && (j_tmp > 0) && num7 == false) {
                CheckField_7_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num7 = true;
        }
    }
}

void CheckField_8_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num8 = false;
            i_tmp = i - 1;
            j_tmp = j;
            if (i > 0 && num8 == false) {
                CheckField_8_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num8 = true;
        }
    }
}

void CheckField_9_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0) && (j <= WIDTH - 1)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num9 = false;
            i_tmp = i - 1;
            j_tmp = j + 1;
            if ((i > 0) && (j < WIDTH - 1) && num9 == false) {
                CheckField_9_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num9 = true;
        }
    }
}

void CheckField_4_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if (j >= 0) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num4 = false;
            i_tmp = i;
            j_tmp = j - 1;
            if (j > 0 && num4 == false) {
                CheckField_4_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num4 = true;
        }
    }
}

void CheckField_6_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;
    if (j <= WIDTH - 1) {
        tmpField[i][j] = Field[i][j];

        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num6 = false;
            i_tmp = i;
            j_tmp = j + 1;
            if (j < WIDTH - 1 && num6 == false) {
                CheckField_6_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num6 = true;
        }
    }
}

void CheckField_1_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i <= HEIGHT - 1) && (j >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num1 = false;
            i_tmp = i + 1;
            j_tmp = j - 1;
            if ((i < HEIGHT - 1) && (j > 0) && num1 == false) {
                CheckField_1_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num1 = true;
        }
    }
}

void CheckField_2_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if (i <= HEIGHT - 1) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num2 = false;
            i_tmp = i + 1;
            j_tmp = j;
            if (i < HEIGHT - 1 && num2 == false) {
                CheckField_2_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num2 = true;
        }
    }
}

void CheckField_3_line_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i <= HEIGHT - 1) && (j <= WIDTH - 1)) {
        tmpField[i][j] = Field[i][j];

        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num3 = false;
            i_tmp = i + 1;
            j_tmp = j + 1;
            if ((i < HEIGHT - 1) && (j < WIDTH - 1) && num3 == false) {
                CheckField_3_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num3 = true;
        }
    }
}

void CheckField_7_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0) && (j >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num7 = false;
            i_tmp = i - 1;
            j_tmp = j - 1;
            if ((i_tmp > 0) && (j_tmp > 0) && num7 == false) {
                CheckField_7_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num7 = true;
        }
    }
}

void CheckField_8_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num8 = false;
            i_tmp = i - 1;
            j_tmp = j;
            if (i > 0 && num8 == false) {
                CheckField_8_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num8 = true;
        }
    }
}

void CheckField_9_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0) && (j <= WIDTH - 1)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num9 = false;
            i_tmp = i - 1;
            j_tmp = j + 1;
            if ((i > 0) && (j < WIDTH - 1) && num9 == false) {
                CheckField_9_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num9 = true;
        }
    }
}

void CheckField_4_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if (j >= 0) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num4 = false;
            i_tmp = i;
            j_tmp = j - 1;
            if (j > 0 && num4 == false) {
                CheckField_4_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num4 = true;
        }
    }
}

void CheckField_6_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;
    if (j <= WIDTH - 1) {
        tmpField[i][j] = Field[i][j];

        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num6 = false;
            i_tmp = i;
            j_tmp = j + 1;
            if (j < WIDTH - 1 && num6 == false) {
                CheckField_6_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num6 = true;
        }
    }
}

void CheckField_1_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i <= HEIGHT - 1) && (j >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num1 = false;
            i_tmp = i + 1;
            j_tmp = j - 1;
            if ((i < HEIGHT - 1) && (j > 0) && num1 == false) {
                CheckField_1_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num1 = true;
        }
    }
}

void CheckField_2_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if (i <= HEIGHT - 1) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num2 = false;
            i_tmp = i + 1;
            j_tmp = j;
            if (i < HEIGHT - 1 && num2 == false) {
                CheckField_2_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num2 = true;
        }
    }
}

void CheckField_3_line_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i <= HEIGHT - 1) && (j <= WIDTH - 1)) {
        tmpField[i][j] = Field[i][j];

        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num3 = false;
            i_tmp = i + 1;
            j_tmp = j + 1;
            if ((i < HEIGHT - 1) && (j < WIDTH - 1) && num3 == false) {
                CheckField_3_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num3 = true;
        }
    }
}

void CheckField_7_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0) && (j >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num7 = false;
            i_tmp = i - 1;
            j_tmp = j - 1;
            if ((i_tmp > 0) && (j_tmp > 0) && num7 == false) {
                CheckField_7_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num7 = true;
        }
    }
}

void CheckField_8_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num8 = false;
            i_tmp = i - 1;
            j_tmp = j;
            if (i > 0 && num8 == false) {
                CheckField_8_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num8 = true;
        }
    }
}

void CheckField_9_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0) && (j <= WIDTH - 1)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num9 = false;
            i_tmp = i - 1;
            j_tmp = j + 1;
            if ((i > 0) && (j < WIDTH - 1) && num9 == false) {
                CheckField_9_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num9 = true;
        }
    }
}

void CheckField_4_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if (j >= 0) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num4 = false;
            i_tmp = i;
            j_tmp = j - 1;
            if (j > 0 && num4 == false) {
                CheckField_4_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num4 = true;
        }
    }
}

void CheckField_6_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;
    if (j <= WIDTH - 1) {
        tmpField[i][j] = Field[i][j];

        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num6 = false;
            i_tmp = i;
            j_tmp = j + 1;
            if (j < WIDTH - 1 && num6 == false) {
                CheckField_6_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num6 = true;
        }
    }
}

void CheckField_1_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i <= HEIGHT - 1) && (j >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num1 = false;
            i_tmp = i + 1;
            j_tmp = j - 1;
            if ((i < HEIGHT - 1) && (j > 0) && num1 == false) {
                CheckField_1_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num1 = true;
        }
    }
}

void CheckField_2_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if (i <= HEIGHT - 1) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num2 = false;
            i_tmp = i + 1;
            j_tmp = j;
            if (i < HEIGHT - 1 && num2 == false) {
                CheckField_2_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num2 = true;
        }
    }
}

void CheckField_3_line_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i <= HEIGHT - 1) && (j <= WIDTH - 1)) {
        tmpField[i][j] = Field[i][j];

        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num3 = false;
            i_tmp = i + 1;
            j_tmp = j + 1;
            if ((i < HEIGHT - 1) && (j < WIDTH - 1) && num3 == false) {
                CheckField_3_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num3 = true;
        }
    }
}

void CheckField_7_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0) && (j >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num7 = false;
            i_tmp = i - 1;
            j_tmp = j - 1;
            if ((i_tmp > 0) && (j_tmp > 0) && num7 == false) {
                CheckField_7_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num7 = true;
        }
    }
}

void CheckField_8_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num8 = false;
            i_tmp = i - 1;
            j_tmp = j;
            if (i > 0 && num8 == false) {
                CheckField_8_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num8 = true;
        }
    }
}

void CheckField_9_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0) && (j <= WIDTH - 1)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num9 = false;
            i_tmp = i - 1;
            j_tmp = j + 1;
            if ((i > 0) && (j < WIDTH - 1) && num9 == false) {
                CheckField_9_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num9 = true;
        }
    }
}

void CheckField_4_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if (j >= 0) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num4 = false;
            i_tmp = i;
            j_tmp = j - 1;
            if (j > 0 && num4 == false) {
                CheckField_4_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num4 = true;
        }
    }
}

void CheckField_6_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;
    if (j <= WIDTH - 1) {
        tmpField[i][j] = Field[i][j];

        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num6 = false;
            i_tmp = i;
            j_tmp = j + 1;
            if (j < WIDTH - 1 && num6 == false) {
                CheckField_6_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num6 = true;
        }
    }
}

void CheckField_1_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i <= HEIGHT - 1) && (j >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num1 = false;
            i_tmp = i + 1;
            j_tmp = j - 1;
            if ((i < HEIGHT - 1) && (j > 0) && num1 == false) {
                CheckField_1_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num1 = true;
        }
    }
}

void CheckField_2_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if (i <= HEIGHT - 1) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num2 = false;
            i_tmp = i + 1;
            j_tmp = j;
            if (i < HEIGHT - 1 && num2 == false) {
                CheckField_2_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num2 = true;
        }
    }
}

void CheckField_3_line_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i <= HEIGHT - 1) && (j <= WIDTH - 1)) {
        tmpField[i][j] = Field[i][j];

        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num3 = false;
            i_tmp = i + 1;
            j_tmp = j + 1;
            if ((i < HEIGHT - 1) && (j < WIDTH - 1) && num3 == false) {
                CheckField_3_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num3 = true;
        }
    }
}

void CheckField_7_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0) && (j >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num7 = false;
            i_tmp = i - 1;
            j_tmp = j - 1;
            if ((i_tmp > 0) && (j_tmp > 0) && num7 == false) {
                CheckField_7_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num7 = true;
        }
    }
}

void CheckField_8_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num8 = false;
            i_tmp = i - 1;
            j_tmp = j;
            if (i > 0 && num8 == false) {
                CheckField_8_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num8 = true;
        }
    }
}

void CheckField_9_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i >= 0) && (j <= WIDTH - 1)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num9 = false;
            i_tmp = i - 1;
            j_tmp = j + 1;
            if ((i > 0) && (j < WIDTH - 1) && num9 == false) {
                CheckField_9_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num9 = true;
        }
    }
}

void CheckField_4_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if (j >= 0) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num4 = false;
            i_tmp = i;
            j_tmp = j - 1;
            if (j > 0 && num4 == false) {
                CheckField_4_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num4 = true;
        }
    }
}

void CheckField_6_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;
    if (j <= WIDTH - 1) {
        tmpField[i][j] = Field[i][j];

        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num6 = false;
            i_tmp = i;
            j_tmp = j + 1;
            if (j < WIDTH - 1 && num6 == false) {
                CheckField_6_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num6 = true;
        }
    }
}

void CheckField_1_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i <= HEIGHT - 1) && (j >= 0)) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num1 = false;
            i_tmp = i + 1;
            j_tmp = j - 1;
            if ((i < HEIGHT - 1) && (j > 0) && num1 == false) {
                CheckField_1_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num1 = true;
        }
    }
}

void CheckField_2_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if (i <= HEIGHT - 1) {
        tmpField[i][j] = Field[i][j];
        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num2 = false;
            i_tmp = i + 1;
            j_tmp = j;
            if (i < HEIGHT - 1 && num2 == false) {
                CheckField_2_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num2 = true;
        }
    }
}

void CheckField_3_line(int** Field, int** tmpField, int i, int j) {
    int i_tmp = i;
    int j_tmp = j;

    if ((i <= HEIGHT - 1) && (j <= WIDTH - 1)) {
        tmpField[i][j] = Field[i][j];

        if (tmpField[i][j] == 10) {
            boom = true;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num3 = false;
            i_tmp = i + 1;
            j_tmp = j + 1;
            if ((i < HEIGHT - 1) && (j < WIDTH - 1) && num3 == false) {
                CheckField_3_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_7_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_8_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_9_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_4_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_6_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_1_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_2_line_line(Field, tmpField, i_tmp, j_tmp);
                CheckField_3_line_line(Field, tmpField, i_tmp, j_tmp);
            }
        }
        else {
            tmpField[i][j] = Field[i][j];
            num3 = true;
        }
    }
}

void CheckField_7(int** Field, int** tmpField, int i, int j) {
    bool num = false;
    while (((i >= 0) && (j >= 0)) && num == false) {
        tmpField[i][j] == Field[i][j];
        CheckField_7_line(Field, tmpField, i, j);
        CheckField_8_line(Field, tmpField, i, j);
        CheckField_9_line(Field, tmpField, i, j);
        CheckField_4_line(Field, tmpField, i, j);
        CheckField_6_line(Field, tmpField, i, j);
        CheckField_1_line(Field, tmpField, i, j);
        CheckField_2_line(Field, tmpField, i, j);
        CheckField_3_line(Field, tmpField, i, j);
        if (tmpField[i][j] == 10) {
            boom = true;
            num = true;
            break;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num = false;
            i--;
            j--;
        }
        else {
            tmpField[i][j] = Field[i][j];
            num = true;
            break;
        }
    }
}

void CheckField_8(int** Field, int** tmpField, int i, int j) {
    bool num = false;
    while (i > 0 && num == false) {
        tmpField[i][j] == Field[i][j];
        CheckField_7_line(Field, tmpField, i, j);
        CheckField_8_line(Field, tmpField, i, j);
        CheckField_9_line(Field, tmpField, i, j);
        CheckField_4_line(Field, tmpField, i, j);
        CheckField_6_line(Field, tmpField, i, j);
        CheckField_1_line(Field, tmpField, i, j);
        CheckField_2_line(Field, tmpField, i, j);
        CheckField_3_line(Field, tmpField, i, j);
        if (tmpField[i][j] == 10) {
            boom = true;
            num = true;
            break;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num = false;
            i--;
        }
        else {
            tmpField[i][j] = Field[i][j];
            num = true;
            break;
        }
    }
}

void CheckField_9(int** Field, int** tmpField, int i, int j) {
    bool num = false;
    while (((i > 0) && (j < WIDTH - 1)) && num == false) {
        tmpField[i][j] == Field[i][j];
        CheckField_7_line(Field, tmpField, i, j);
        CheckField_8_line(Field, tmpField, i, j);
        CheckField_9_line(Field, tmpField, i, j);
        CheckField_4_line(Field, tmpField, i, j);
        CheckField_6_line(Field, tmpField, i, j);
        CheckField_1_line(Field, tmpField, i, j);
        CheckField_2_line(Field, tmpField, i, j);
        CheckField_3_line(Field, tmpField, i, j);
        if (tmpField[i][j] == 10) {
            boom = true;
            num = true;
            break;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num = false;
            i--;
        }
        else {
            tmpField[i][j] = Field[i][j];
            num = true;
            break;
        }
    }
}

void CheckField_4(int** Field, int** tmpField, int i, int j) {
    bool num = false;
    while (j > 0 && num == false) {
        tmpField[i][j] == Field[i][j];
        CheckField_7_line(Field, tmpField, i, j);
        CheckField_8_line(Field, tmpField, i, j);
        CheckField_9_line(Field, tmpField, i, j);
        CheckField_4_line(Field, tmpField, i, j);
        CheckField_6_line(Field, tmpField, i, j);
        CheckField_1_line(Field, tmpField, i, j);
        CheckField_2_line(Field, tmpField, i, j);
        CheckField_3_line(Field, tmpField, i, j);
        if (tmpField[i][j] == 10) {
            boom = true;
            num = true;
            break;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num = false;
            j--;
        }
        else {
            tmpField[i][j] = Field[i][j];
            num = true;
            break;
        }
    }
}

void CheckField_6(int** Field, int** tmpField, int i, int j) {
    bool num = false;
    while (j < WIDTH - 1 && num == false) {
        tmpField[i][j] == Field[i][j];
        CheckField_7_line(Field, tmpField, i, j);
        CheckField_8_line(Field, tmpField, i, j);
        CheckField_9_line(Field, tmpField, i, j);
        CheckField_4_line(Field, tmpField, i, j);
        CheckField_6_line(Field, tmpField, i, j);
        CheckField_1_line(Field, tmpField, i, j);
        CheckField_2_line(Field, tmpField, i, j);
        CheckField_3_line(Field, tmpField, i, j);
        if (tmpField[i][j] == 10) {
            boom = true;
            num = true;
            break;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num = false;
            j++;
        }
        else {
            tmpField[i][j] = Field[i][j];
            num = true;
            break;
        }
    }
}

void CheckField_1(int** Field, int** tmpField, int i, int j) {
    bool num = false;
    while (((i <= HEIGHT - 1) && (j >= 0)) && num == false) {
        tmpField[i][j] == Field[i][j];
        CheckField_7_line(Field, tmpField, i, j);
        CheckField_8_line(Field, tmpField, i, j);
        CheckField_9_line(Field, tmpField, i, j);
        CheckField_4_line(Field, tmpField, i, j);
        CheckField_6_line(Field, tmpField, i, j);
        CheckField_1_line(Field, tmpField, i, j);
        CheckField_2_line(Field, tmpField, i, j);
        CheckField_3_line(Field, tmpField, i, j);
        if (tmpField[i][j] == 10) {
            boom = true;
            num = true;
            break;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num = false;
            i++;
            j--;
        }
        else {
            tmpField[i][j] = Field[i][j];
            num = true;
            break;
        }
    }
}

void CheckField_2(int** Field, int** tmpField, int i, int j) {
    bool num = false;
    while (i < HEIGHT - 1 && num == false) {
        tmpField[i][j] == Field[i][j];
        CheckField_7_line(Field, tmpField, i, j);
        CheckField_8_line(Field, tmpField, i, j);
        CheckField_9_line(Field, tmpField, i, j);
        CheckField_4_line(Field, tmpField, i, j);
        CheckField_6_line(Field, tmpField, i, j);
        CheckField_1_line(Field, tmpField, i, j);
        CheckField_2_line(Field, tmpField, i, j);
        CheckField_3_line(Field, tmpField, i, j);
        if (tmpField[i][j] == 10) {
            boom = true;
            num = true;
            break;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num = false;
            i++;
        }
        else {
            tmpField[i][j] = Field[i][j];
            num = true;
            break;
        }
    }
}

void CheckField_3(int** Field, int** tmpField, int i, int j) {
    bool num = false;
    while (((i < HEIGHT - 1) && (j < WIDTH - 1)) && num == false) {
        tmpField[i][j] == Field[i][j];
        CheckField_7_line(Field, tmpField, i, j);
        CheckField_8_line(Field, tmpField, i, j);
        CheckField_9_line(Field, tmpField, i, j);
        CheckField_4_line(Field, tmpField, i, j);
        CheckField_6_line(Field, tmpField, i, j);
        CheckField_1_line(Field, tmpField, i, j);
        CheckField_2_line(Field, tmpField, i, j);
        CheckField_3_line(Field, tmpField, i, j);
        if (tmpField[i][j] == 10) {
            boom = true;
            num = true;
            break;
        }
        else if (tmpField[i][j] == 0 || tmpField[i][j] == 11) {
            tmpField[i][j] = 11;
            num = false;
            i++;
            j++;
        }
        else {
            tmpField[i][j] = Field[i][j];
            num = true;
            break;
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
    }
}

void CheckField(int** Field, int** tmpField, int i, int j) {
    CheckField_7(Field, tmpField, i, j);
    CheckField_8(Field, tmpField, i, j);
    CheckField_9(Field, tmpField, i, j);
    CheckField_4(Field, tmpField, i, j);
    CheckField_6(Field, tmpField, i, j);
    CheckField_1(Field, tmpField, i, j);
    CheckField_2(Field, tmpField, i, j);
    CheckField_3(Field, tmpField, i, j);
}

int main() {
    setlocale(LC_ALL, "Russian"); // задаём русский текст
    system("chcp 1251"); // настраиваем кодировку консоли
    system("cls");
    int** Field = CreateField(HEIGHT, WIDTH);
    int** tmpField = CreateField(HEIGHT, WIDTH);
    FillField(Field);
    CheckMines(Field);
    for (int i = 0; i < ((WIDTH / 2) - (WIDTH / 5)); i++) {
        cout << " ";
    }
    cout << " Игра сапер: " << endl;
    cout << endl;
    ShowField(tmpField);
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
        CheckField(Field, tmpField, i, j);
        for (int i = 0; i < ((WIDTH / 2) - (WIDTH / 5)); i++) {
            cout << " ";
        }
        cout << " Игра сапер: " << endl;
        cout << endl;
        ShowField(tmpField);
        CheckFieldWin(Field, tmpField);
        if (win || boom) system("cls");
    } while (!(win || boom));
    for (int i = 0; i < ((WIDTH / 2) - (WIDTH / 5)); i++) {
        cout << " ";
    }
    cout << " Игра сапер: " << endl;
    cout << endl;
    if (boom) {
        ShowField(tmpField);
        for (int i = 0; i < ((WIDTH / 2) - (WIDTH / 4)); i++) {
            cout << " ";
        }
        cout << endl;
        cout << " Вы проиграли!!!" << endl;
    }
    if (win) {
        ShowField(Field);
        for (int i = 0; i < ((WIDTH / 2) - (WIDTH / 4)); i++) {
            cout << " ";
        }
        cout << endl;
        cout << " Вы победили!!!" << endl;
    }
    DeleteField(Field);
    DeleteField(tmpField);
    return 0;
}