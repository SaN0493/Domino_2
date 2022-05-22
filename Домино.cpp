#include <iostream>
#include <windows.h>
#include <ctime>
#include "Prototypes.h"
#include "Constants.h"

//Для цветного текста
#include <conio.h>
#include <stdio.h>

#define random(a,b) a+rand()%b+1-a;
using namespace std;

int** creatBox(int domino) {
	int** box = new int*[domino];
	for (int i = 0; i < domino; i++) {
		box[i] = new int[2];
	}
	for (int i = 0, k = 0, v = 0; i < domino; i++) {
		for (int j = 0; j < 2; j++) {
			if (j == 0)box[i][j] = k;
			else box[i][j] = v++;
			if (v == 7) {
				k++;
				v = k;
			}
		}
		
	}
	return box;
}
void blendBox(int** box) {
	int size = _msize(box) / sizeof(box[0]);
	int index = 0;
	for (int i = 0; i < size; i++){
		index = random(i, size - 1);
		swap(box[i], box[index]);
	}
}
void createPl(int** &pl) {
	int size = _msize(pl) / sizeof(pl[0]);
	for (int i = 0; i < size; i++) {
		pl[i] = new int[2];
	}
}
void takeBox(int**& box,int**& pl, int n) {
	int sizebox = _msize(box) / sizeof(box[0]);
	int sizepl = _msize(pl) / sizeof(pl[0]);
	int** bufpl = new int*[sizepl+n];
	int** bufbox = new int*[sizebox-n];
	for (int i = 0; i < sizepl + n; i++) {
		bufpl[i] = new int[2];
	}
	for (int i = 0; i < sizebox-n; i++) {
		bufbox[i] = new int[2];
	}
	for (int i = 0; i < sizepl; i++) {
		bufpl[i][0] = pl[i][0];
		bufpl[i][1] = pl[i][1];
	}
	for (int i = 0, j = sizepl; i < n; j++, i++) {
		bufpl[j][0] = box[i][0];
		bufpl[j][1] = box[i][1];
	}
	delete[]pl;
	pl = bufpl;
	for (int i = 0, a = n; a < sizebox; a++, i++) {
		bufbox[i][0] = box[a][0];
		bufbox[i][1] = box[a][1];
	}
	delete[]box;
	box = bufbox;
}
void initPole(int pole[16][26]) {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j <= 26; j++) {
			pole[i][j] = 8;

		}
	}
}
int whoIsFirst(int** pl1,int** pl2) {
	int sizepl1_1 = _msize(pl1) / sizeof(pl1[0]);
	int sizepl2_1 = _msize(pl2) / sizeof(pl2[0]);
	int mini1 = pl1[0][0];
	int mini2 = pl2[0][0];
	for (int i = 0; i < sizepl1_1; i++) {
		for (int j = 0; j < 1; j++) {
			if (pl1[i][j] == pl1[i][j + 1]) {
				if (pl1[i][j] < mini1) mini1 = pl1[i][j];
			}
		}
	}
	for (int i = 0; i < sizepl2_1; i++) {
		for (int j = 0; j < 1; j++) {
			if (pl2[i][j] == pl2[i][j + 1]) {
				if (pl2[i][j] < mini2) mini2 = pl2[i][j];
			}
		}
	}
	if (mini1 < mini2)return 1;
	else return 2;
}
void showPole(int pole[16][26]) {
	cout << "   X  " << "\t";
	for (int i = 0; i < 26; i++) {
		if (i < 10) cout << "  "<<i;
		else cout<< " " << i;
	}
	cout << endl;
	cout << "Y\t ";
	for (int i = 0; i < 79; i++) {
		cout << "-";
	}
	cout << endl;
	for (int k = 0;;) {
		for (int i = 0; i < 16; i++) {
			cout << k << "\t";
			cout << "| ";
			for (int j = 0; j < 26; j++) {
				if (pole[i][j] == 8)cout << ".  ";
				else cout << pole[i][j] << "  ";
			}
			cout << "|";
			cout <<"\t"<<  k++ << endl;
		}
		if (k = 10)break;
	}
	cout << "  \t";
	for (int i = 0; i < 79; i++) {
		cout << "-";
	}
	cout << endl<< "\t";
	for (int i = 0; i < 26; i++) {
		if (i < 10) cout << "  " << i;
		else cout << " " << i;
	}
}
void showPl(int** pl) {
	int size = _msize(pl) / sizeof(pl[0]);
	cout << "Nomber = ";
	for (int i = 0; i < size; i++) {
		cout << i + 1 << "\t  ";
	}
	cout << endl << "\t";
	for (int i = 0; i < size; i++) {
		cout << " " << pl[i][0] << "|" << pl[i][1] << "\t";
	}
}
int proverkaHoda(int pole[16][26], int x, int y,int xx,int yy) {
	if (pole[y][x] == 8 && pole[yy][xx] == 8) return 1;
	else return 0;
}
int proverkaHoda2(int pole[16][26],int** pl, int n, int x, int y, int xx,int yy) {
	int c=0;
	if (pole[y][x+1] != 8)c++;
	if (pole[y][x-1] != 8)c++;
	if (pole[y+1][x] != 8)c++;
	if (pole[y-1][x] != 8)c++;
	if (c >= 2)return 0;
	if (pole[yy][xx + 1] != 8)c++;
	if (pole[yy][xx - 1] != 8)c++;
	if (pole[yy + 1][xx] != 8)c++;
	if (pole[yy - 1][xx] != 8)c++;
	if (c >= 2)return 0;
	if (pole[y][x - 1] != 8) {
		if (pole[y - 1][x - 1] == 8 && pole[y + 1][x - 1] == 8) {
			if (pole[y][x - 1] == pl[n][0] || pole[y][x - 1] == pl[n][1]) {
				if (pole[y][x - 1] == pl[n][1]) {
					swap(pl[n][0], pl[n][1]);
				}
				return 2;
			}
		}
		else if (pole[y - 1][x - 1] != 8 && pole[y + 1][x - 1] == 8) {
			if (pole[y][x - 2] == 8) {
				if (pole[y][x - 1] == pl[n][0] || pole[y][x - 1] == pl[n][1]) {
					if (pole[y][x - 1] == pl[n][1]) {
						swap(pl[n][0], pl[n][1]);
					}
					return 2;
				}
			}
		}
		else if (pole[y - 1][x - 1] == 8 && pole[y + 1][x - 1] != 8) {
			if (pole[y][x - 2] == 8) {
				if (pole[y][x - 1] == pl[n][0] || pole[y][x - 1] == pl[n][1]) {
					if (pole[y][x - 1] == pl[n][1]) {
						swap(pl[n][0], pl[n][1]);
					}
					return 2;
				}
			}
		}
		else return 0;
	}
	if (pole[y][x + 1] != 8) {
		if (pole[y - 1][x + 1] == 8 && pole[y + 1][x + 1] == 8) {
			if (pole[y][x+1] == pl[n][0] || pole[y][x+1] == pl[n][1]) {
				if (pole[y][x+1] == pl[n][1]) {
					swap(pl[n][0], pl[n][1]);
				}
				return 2;
			}
		}
		else if (pole[y - 1][x + 1] != 8 && pole[y + 1][x + 1] == 8) {
			if (pole[y][x+2] == 8) {
				if (pole[y][x+1] == pl[n][0] || pole[y][x+1] == pl[n][1]) {
					if (pole[y][x+1] == pl[n][1]) {
						swap(pl[n][0], pl[n][1]);
					}
					return 2;
				}
			}
		}
		else if (pole[y - 1][x + 1] == 8 && pole[y + 1][x + 1] != 8) {
			if (pole[y][x+2] == 8) {
				if (pole[y][x+1] == pl[n][0] || pole[y][x+1] == pl[n][1]) {
					if (pole[y][x+1] == pl[n][1]) {
						swap(pl[n][0], pl[n][1]);
					}
					return 2;
				}
			}
		}
		else return 0;
	}
	if (pole[y - 1][x] != 8) {
		if (pole[y - 1][x - 1] == 8 && pole[y - 1][x + 1] == 8) {
			if (pole[y - 1][x] == pl[n][0] || pole[y - 1][x] == pl[n][1]) {
				if (pole[y - 1][x] == pl[n][1]) {
					swap(pl[n][0], pl[n][1]);
				}
				return 2;
			}
		}
		else if (pole[y - 1][x - 1] != 8 && pole[y - 1][x + 1] == 8) {
			if (pole[y - 2][x] == 8) {
				if (pole[y - 1][x] == pl[n][0] || pole[y - 1][x] == pl[n][1]) {
					if (pole[y - 1][x] == pl[n][1]) {
						swap(pl[n][0], pl[n][1]);
					}
					return 2;
				}
			}
		}
		else if (pole[y - 1][x - 1] == 8 && pole[y - 1][x + 1] != 8) {
			if (pole[y - 2][x] == 8) {
				if (pole[y - 1][x] == pl[n][0] || pole[y - 1][x] == pl[n][1]) {
					if (pole[y - 1][x] == pl[n][1]) {
						swap(pl[n][0], pl[n][1]);
					}
					return 2;
				}
			}
		}
		else return 0;
		
	}
	if (pole[y + 1][x] != 8) {
		if (pole[y + 1][x - 1] == 8 && pole[y + 1][x + 1] == 8) {
			if (pole[y + 1][x] == pl[n][0] || pole[y + 1][x] == pl[n][1]) {
				if (pole[y + 1][x] == pl[n][1]) {
					swap(pl[n][0], pl[n][1]);
				}
				return 2;
			}
		}
		else if (pole[y + 1][x - 1] != 8 && pole[y + 1][x + 1] == 8) {
			if (pole[y + 2][x] == 8) {
				if (pole[y + 1][x] == pl[n][0] || pole[y + 1][x] == pl[n][1]) {
					if (pole[y + 1][x] == pl[n][1]) {
						swap(pl[n][0], pl[n][1]);
					}
					return 2;
				}
			}
		}
		else if (pole[y + 1][x - 1] == 8 && pole[y + 1][x + 1] != 8) {
			if (pole[y + 2][x] == 8) {
				if (pole[y + 1][x] == pl[n][0] || pole[y + 1][x] == pl[n][1]) {
					if (pole[y + 1][x] == pl[n][1]) {
						swap(pl[n][0], pl[n][1]);
					}
					return 2;
				}
			}
		}
		else return 0;

	}
	return 0;
}
void delDomino(int**& pl, int n) {
	int size = _msize(pl) / sizeof(pl[0]);
	int size2 = size - 1;
	int** buf = new int*[size2];
	for (int i = 0; i < size2; i++) {
		buf[i] = new int[2];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2; j++) {
		buf[i][j] = pl[i][j];
		}
	}
	for (int i = n, k = n + 1; k < size; k++, i++) {
		for (int j = 0; j < 2; j++) {
		buf[i][j] = pl[k][j];
		}
	}
	delete[]pl;
	pl = buf;
}
void hod(int pole[16][26], int**& pl, int n, int x, int y,int xx,int yy) {
	pole[y][x] = pl[n][0];
	pole[yy][xx] = pl[n][1];

	delDomino(pl, n);
}
int coutPl1(int pole[16][26], int**& pl1,int**& box, bool flag,int& i2) {
	int size;
	int x, y, n,xx,yy;
	int p = 0;
	int u = 0;
	for (; p == 0;) {
	int sizepl = _msize(pl1) / sizeof(pl1[0]);
	int sizebox = _msize(box) / sizeof(box[0]);
		system("cls");
		showPole(pole);
		cout << endl << endl << endl << endl;
		cout << "Player1 : " << endl;
		showPl(pl1);
		cout << endl << endl << endl << endl;
		cout << "Bazar, input 100" << endl << endl;
		cout << "Input Number Domino Pl1= ";
		cin >> n;
		if (n <= 0 || n > sizepl && n != 100) {
			cout << "\nWrong number!!\n Please repet!\nTo continue press enter";
			if (_getch() == 13) {
				continue;
			}
		}
		else if (n == 100) {
			if (u == 3 && sizebox>0) {
				cout << "\nYou skip a trun. Sorry...\nTo continue press enter";
				if (_getch() == 13) {
					break;
				}
			}
			u++;
			if (sizebox == 0) {
				cout << "\nDomino are over. =( \nTo continue press enter";
				if (_getch() == 13) {
					break;
				}
			}
			else {
				takeBox(box, pl1, 1);
				continue;
			}
		}
		cout << "Input cor.X Pl1= ";
		cin >> x;
		if (x < 0 || x >= 26) {
			cout << "\nWrong number!!\n Please repet!\nTo continue press enter";
			if (_getch() == 13) {
				continue;
			}
		}
		else {
			cout << "Input cor.Y Pl1= ";
			cin >> y;
		}
		if (y < 0 || y >= 16) {
			cout << "\nWrong number!!\n Please repet!\nTo continue press enter";
			if (_getch() == 13) {
				continue;
			}
		}
		else {
			cout << "Point direction twice Pl1= ";
			int key = _getch();
			switch(_getch()) {
			case 72://вверз
				xx = x;
				yy = y - 1;
				if (yy < 0) 
				break;
			case 80://вниз
				xx = x;
				yy = y + 1;
				break;
			case 75://влево
				xx = x - 1;
				yy = y;
				break;
			case 77://вправо
				xx = x + 1;
				yy = y;
				break;
			default:
					continue;
				
			}
		}
		if (x > 0 && x < 26 && y>0 && y < 16 && xx>0 && xx < 26 && yy>0 && yy < 16) {
			int i = proverkaHoda(pole, x, y, xx, yy);
			if (i == 1) i = proverkaHoda2(pole, pl1, n - 1, x, y, xx, yy);
			if (i2 != 0 && i == 0) {
				p = 0;
				cout << "\nNo move possibe\nPlease repet!\nTo continue press enter";
				if (_getch() == 13) {
					continue;
				}

			}
			if (i == 2 || i2 == 0) {
				hod(pole, pl1, n - 1, x, y, xx, yy);
				p = 1;
			}
		}
		else {
			cout << "\nNo move possibe\nPlease repet!\nTo continue press enter!";
			if (_getch() == 13) {
				continue;
			}
		}
	}
	size = _msize(pl1) / sizeof(pl1[0]);
	if (size == 0)return 0;
	else return 2;
}
int coutPl2(int pole[16][26], int**& pl2,int**& box, bool flag) 
{
	int size;
	int x2, y2, n2,n3,xx2,yy2;
	int p = 0;
	int u = 0;
	for (; p == 0;) {
		int sizepl = _msize(pl2) / sizeof(pl2[0]);
		int sizebox = _msize(box) / sizeof(box[0]);
		system("cls");
		showPole(pole);
		cout << endl << endl << endl << endl;
		cout << "Player2 : " << endl;
		showPl(pl2);
		cout << endl << endl << endl << endl;
		cout << "Bazar, imput 100" << endl << endl;
		cout << "Imput Nomber Domino Pl2= ";
		cin >> n2;
		if (n2 <= 0 || n2 > sizepl && n2 != 100) {
			cout << "\nWrong number!!\n Please repet!\nTo continue press enter!";
			if (_getch() == 13) {
				continue;
			}
		}
		else if (n2 == 100)
		{
			if (u == 3) {
				cout << "\nYou skip a trun. Sorry...\nTo continue press enter!";
				if (_getch() == 13) {
					break;
				}
			}
			u++;
			if (sizebox == 0) {
				cout << "\nDomino are over. =( \nTo continue press enter!";
				if (_getch() == 13) {
					break;
				}

			}
			else {
				takeBox(box, pl2, 1);
				continue;
			}
		}
		cout << "Input cor.X Pl2= ";
		cin >> x2;
		if (x2 < 0 || x2 >= 26) {
			cout << "\nWrong number!!\n Please repet!\nTo continue press enter!";
			if (_getch() == 13) {
				continue;
			}
		}
		else {
			cout << "Input cor.Y Pl2= ";
			cin >> y2;
		}
		if (y2 < 0 || y2 >= 16) {
			cout << "\nWrong number!!\n Please repet!\nTo continue press enter!";
			if (_getch() == 13) {
				continue;
			}
		}
		else {
			cout << "Point direction twice Pl2= ";
			int key = _getch();
			switch (_getch()) {
			case 72://вверз
				xx2 = x2;
				yy2 = y2 - 1;
				break;
			case 80://вниз
				xx2 = x2;
				yy2 = y2 + 1;
				break;
			case 75://влево
				xx2 = x2 - 1;
				yy2 = y2;
				break;
			case 77://вправо
				xx2 = x2 + 1;
				yy2 = y2;
				break;
			default:
				continue;
			}
		}
		if (x2 > 0 && x2 < 26 && y2>0 && y2 < 16 && xx2>0 && xx2 < 26 && yy2>0 && yy2 < 16) {
			int i = proverkaHoda(pole, x2, y2, xx2, yy2);
			if (i == 1) i = proverkaHoda2(pole, pl2, n2 - 1, x2, y2, xx2, yy2);
			if (i == 0) {
				p = 0;
				cout << "\nNo move possibe\nPlease repet!\nTo continue press enter!";
				if (_getch() == 13) {
					continue;
				}
			}
			if (i == 2) {
				hod(pole, pl2, n2 - 1, x2, y2, xx2, yy2);
				p = 1;
			}
		}
		else {
			cout << "\nNo move possibe\nPlease repet!\nTo continue press enter!";
			if (_getch() == 13) {
				continue;
			}
		}
	}
	size = _msize(pl2) / sizeof(pl2[0]);
	if (size == 0)return 1;
	else return 2;
}

int main()
{
	srand(time(NULL));
	sizeWindow(WIDTH, HIGHT, TOP, LEFT);
	menu(xb, yb);
	int domino = 28;
	int** box = creatBox(domino);
	blendBox(box);
	int pole[16][26];
	int** pl1 = new int*[0];
	int** pl2 = new int*[0];
	createPl(pl1);
	createPl(pl2);
	takeBox(box, pl1,7);
	takeBox(box, pl2,7);
	initPole(pole);
	int status = 2;
	bool flag=true;
	int i = 0;
	int w = whoIsFirst(pl1,pl2);
	if (w == 2)swap(pl1, pl2);
	int qw = 2;
	int key;
	//-0 - выиграл игрок №1
	//-1 - выиграл игрок №2
	//-2 - идет игра
	//-3 - Ничья
	for (; status == 2;) {
		if(flag==true)
		{
			status = coutPl1(pole,pl1,box,flag,i);
			flag = false;
			if (status == 0)	break;
		}
		else 
		{
			status = coutPl2(pole, pl2, box, flag);
			flag = true;
			if (status == 1) break;
		}
		i++;
		if (i == 50) {
			status == 3;
			break;
		}
	}
	key= _getch();
	if (status == 0) {
		system("cls");
		gotoxy(64, 13);
		cout << "Player number 1 WINNER!!!";
		gotoxy(64, 15);
		cout << "Enter any number to exit";
		cin >> qw;
	}
	else if (status == 1) {
		system("cls");
		gotoxy(64, 13);
		cout << "Player number 2 WINNER!!!";
		gotoxy(64, 15);
		cout << "Enter any number to exit";
		cin >> qw;
	}
	else {
		system("cls");
		gotoxy(73, 13);
		cout << "DRAW!!!";
		gotoxy(64, 15);
		cout << "Enter any number to exit";
		cin >> qw;
	}
}

	
