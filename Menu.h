#include <iostream>
#include <windows.h>
#include <ctime>
#include "Prototypes.h"
#include "Constants.h"

//Для цветного текста
#include <conio.h>
#include <stdio.h>

using namespace std;

void rules() {
    system("cls");
    gotoxy(60,15,White);
    cout << "Pliz, Play fair =)\n";
    gotoxy(60, 16, White);
    cout << "\tGood lick!";
    int key;
    while (true) {
        key = _getch();
        if (key == 27)
        {
            system("cls");
            return;
            menu(xb, yb);
        }
    }
}

int menu(int x = xb, int y = yb) {
    system("cls");
    int key;
    int a = 1;
    while (true) {
        blackMenu();
        gotoxy(64, 13);
        cout << "____Domino____";
        gotoxy(x, y);
        if (y == yb) cout << "NEW GAME";
        else if (y == yb + 2) cout << "OPTIONS";
        else if (y == yb + 4) cout << "EXIT";
        key = _getch();
        switch (key) {
        case 80:
            y += 2;
            break;
        case 72:
            y -= 2;
            break;
        case 27:
            exit(0);
        case 13:
            if (y == yb) return a = 2;
            else if (y == yb + 2) rules();
            else if (y == yb + 4)
            {
                setColour(Black);
                exit(0);
            }
        }
        if (y < yb) y += 6;
        else if (y > yb + 4) y -= 6;
    }
}

void blackMenu() {
    setColour(White);
    int x = xb;
    int y = yb;
    gotoxy(x, y);
    cout << "NEW GAME";
    y += 2;
    gotoxy(x, y);
    cout << "OPTIONS";
    y += 2;
    gotoxy(x, y);
    cout << "EXIT";
}