//Присвоение тексту нужного цвета
void setColour(int text);

//Размещение в координатах
void gotoxy(int x, int y);

//Размещение в координатах c цветом
void gotoxy(int x, int y, int color);

//Menu
void rules();
//void newGame();
int menu(int x, int y);
void blackMenu();
void sizeWindow(int width, int hight, int top, int left);

int** creatBox(int domino);
void blendBox(int** box);
void createPl(int**& pl);
void takeBox(int**& box, int**& pl, int n);
void initPole(int pole[16][26]);
int whoIsFirst(int** pl1, int** pl2);
void showPole(int pole[16][26]);
void showPl(int** pl);
int proverkaHoda(int pole[16][26], int x, int y, int xx, int yy);
int proverkaHoda2(int pole[16][26], int** pl, int n, int x, int y, int xx, int yy);
void delDomino(int**& pl, int n);
void hod(int pole[16][26], int**& pl, int n, int x, int y, int xx, int yy);
int coutPl1(int pole[16][26], int**& pl1, int**& box, bool flag, int& i2);
int coutPl2(int pole[16][26], int**& pl2, int**& box, bool flag);