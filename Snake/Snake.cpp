﻿#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 10;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int lastDir;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void setcur(int x, int y)//установка курсора на позицию  x y
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void Setup() {
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);   //Получение хендла
    CONSOLE_CURSOR_INFO cursor = { 1, false };   // Число от 1 до 100 размер курсора в процентах
    // false\true - видимость
    SetConsoleCursorInfo(hCons, &cursor);  //Применение заданных параметров курсора
    gameOver = false;
    dir = STOP;
    x = width / 2 - 1;
    y = height / 2 - 1;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    Sleep(150);
    //system("cls");
    setcur(0, 0);
    for (int i = 0; i < width + 1; i++) 
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1)        cout << "#";
            if (i == y && j == x)                cout << "0";
            else if (i == fruitY && j == fruitX) cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        print = true;
                        cout << "o";
                    }
                }
                if (!print) cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 1; i++)
        cout << "#";
    cout << endl;
    cout << "SCORE: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        lastDir = dir;
        switch (_getch()) {
        case 'a':
            if (lastDir != RIGHT) dir = LEFT;
            break;
        case 'd':
            if (lastDir != LEFT) dir = RIGHT;
            break;
        case 'w':
            if (lastDir != DOWN) dir = UP;
            break;
        case 's':
            if (lastDir != UP) dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:
        if (lastDir != RIGHT) x--;
        else x++;
        break;
    case RIGHT:
        if (lastDir != LEFT) x++;
        else x--;
        break;
    case UP:
        if (lastDir != DOWN) y--;
        else y++;
        break;
    case DOWN:
        if (lastDir != UP) y++;
        else y--;
        break;
    }

    //if (x > width || x < 0 || y > height || y < 0) gameOver = true;
    if (x >= width - 1) {
        x = 0;
    }
    else if (x < 0) {
        x = width - 2;
    }

    if (y >= height) {
        y = 0;
    }
    else if (y < 0) {
        y = height - 1;
    }

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) gameOver = true;
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }

    if (gameOver == true) cout << "YOU LOSE!" << endl;
}

int main()
{
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
    }
    return 0;
}