#include <iostream>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;
HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
int **mapUser = new int*[10];
int **mapPC = new int*[10];
int curserCellX = 0;
int curserCellY = 0;
int curserLen;
bool ok; // end game = false
int curserDir = 0; // 0 ofoghi // 1 amodi
bool set = true; // ture =karbar dar hal chidane map ast
bool systemCls = true;
char userName[1000],PCName[1000];
int randomY, randomX; // cellol random baraye attack zadane pc 
int turn = 1; // nobate 0 1 baraye pc va user
int ship[4] = { 1, 2, 3, 4 };
int shipT[4] = { 4, 3, 2, 1 }; //tedade har keshti baraye generate kardane pc
int shipTU[4] = { 4, 3, 2, 1 }; // tedade har keshti baraye chidane user
int shipLen[4] = { 0, 1, 2, 3 }; // tole keshti

void executeGame();
void setUserMap();

#include"Header1.h"
int main()
{
	srand((unsigned)time(0));

	for (int i = 0; i < 10; i++) // i =x // j=y
	{
		mapPC[i] = new int[10];
		mapUser[i] = new int[10];
	}

	for (int i = 0; i < 10; i++) // khali chidane map
	for (int j = 0; j < 10; j++)
		mapPC[i][j] = 0;

	for (int i = 0; i < 10; i++) // khali chidane map // gharar dadane 0 dar map
	for (int j = 0; j < 10; j++)
		mapUser[i][j] = 0;
	// 0 khali // 1 tir khata khorde // 2 tir dorost khorde ( X zarbdar ) // 3 boat ofoghi // 4 boat amodi

	cout << "Enter your name \n";
	cin >> userName;

	cout << "Enter your name(PC) \n";
	cin >> PCName;

	setUserMap(); // chidane mape user
	generateMap(); // chidane mape pc

	turn = rand() % 2 + 1; // nobate shansi
	executeGame();//ejraye bazi
	system("pause");
}

void executeGame() // control vorodi ha va tashikhs bord va bakht
{
	int input;
	ok = true;
	while (ok)
	{
		//turn = 1; hamishe nobate user
		if (systemCls)
		{
			system("cls");
			systemCls = false;
			showMap(0);
		}

		if (!chechWin(2))
		{
			systemCls = false;
			ok = false;
			system("cls");
			showMap(0);
			cout << userName << " won\n" << PCName << " Lost\n";
			break;
		}
		if (!chechWin(1))
		{
			systemCls = false;
			ok = false;
			system("cls");
			showMap(0);
			cout << PCName << " won\n"<< userName << " Lost\n";
			break;
		}
		if (turn == 2)
		{
			attack(turn);
		}
		else
		{
			input = _getch();
			if (input == 77 || input == 75 || input == 72 || input == 80)
			{
				curser(input);
			}
			else if (input == 32)
			{
				attack(turn);
			}
			else if (input == 27)
			{
				exit(0);
			}
		}
	} //end while
}