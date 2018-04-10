using namespace std;
void curser(int direction);
void showMap(int line);
void showLine(int line, int mode);
bool attack(int mode);
void changeColorIfInCurser(int mode, int line, int x);
bool chechWin(int T);
void generateMap();
bool check(int y, int x, int dir, int ship, int len, bool first);
bool check2(int y, int x, int dir, int ship, int len, bool first);
bool continueOrN();
void setUserMap();
bool setShip(int ship);
void shot(int mode, int y, int x);

bool setShip(int ship) // ghara dadane keshti dar map
{
	if (!check2(curserCellY, curserCellX, curserDir, ship, curserLen, true))
	{
		if (curserDir == 0)
		{
			for (int i = 0; i <= curserLen; i++)
			{
				mapUser[curserCellY][curserCellX + i] = 3;
			}
		}
		if (curserDir == 1)
		{
			for (int i = 0; i <= curserLen; i++)
			{
				mapUser[curserCellY + i][curserCellX] = 4;
			}
		}
		shipTU[ship]--;
		return true;
	}
	else return false;
}
void setUserMap() // baraye chidane map user
{
	int input;
	bool err = false;
	for (int i = 0; i < 4; i++)
	{
		curserLen = shipLen[i];
		while (shipTU[i]) // ta vaghti tedad ship 0 nist
		{
			if (systemCls)
			{
				system("cls");
				systemCls = false;
				showMap(0);
				printf("%s", "Press enter to change diresction \nPress space to set ship ");
				if (err) printf("\n%s", "you can't set ship in this cell !!! ");
				err = false;
			}
			input = _getch();
			if (input == 77 || input == 75 || input == 72 || input == 80)
			{
				curser(input);
			}
			else if (input == 32)
			{
				if (setShip(i)) curser(77); // i = model keshti dar arraye ship
				else
				{
					err = true;
					curser(77);
				}
			}
			else if (input == 13)
			{
				if (curserDir == 0)
				{
					if (curserCellY + curserLen > 9) curserCellY -= curserLen; // for debug //vaghti curserX col 9 bod bareye taghire jahat be andaze len aghab miad
					curserDir = 1;
				}
				else
				{
					if (curserCellX + curserLen > 9) curserCellX -= curserLen; // for debug
					curserDir = 0;
				}
				systemCls = true;
			}
			else if (input == 27)
			{
				exit(0);
			}//end else if
		}//end while
	}//end for
	set = false;
	curserLen = 0;
}//end function setship
bool continueOrN() // check kardane tedade keshti hay ke bayad bogzarim agar 0 bashad yani generate kardan tamom shode
{
	for (int i = 0; i < 4; i++)
	{
		if (shipT[i] != 0) return true;
	}
	return false;
}
void generateMap() // generate kardane mape pc
{
	int shipRand, xRand, yRand, dirRand;
	while (continueOrN())
	{
		do{
			shipRand = rand() % 4;
		} while (shipT[shipRand] == 0);

		shipT[shipRand]--;

		int len = shipLen[shipRand];
		do
		{
			dirRand = rand() % 2; // 0 ofoghi // 1amodi
			if (dirRand == 0)
			{
				xRand = (rand() % (10 - len)) + len; // adadi az length keshti ta 9 midahad // braye chidan keshti az akhar be aval
				yRand = rand() % 10;
			}
			else if (dirRand == 1)
			{
				yRand = (rand() % (10 - len)) + len; // adadi az length keshti ta 9 midahad // braye chidan keshti az akhar be aval
				xRand = rand() % 10;
			}
		} while (check(yRand, xRand, dirRand, shipRand, len, true)); // check vaghti true ast ke ghavanin rayat nashode bashad
		if (len == 0)
		{
			mapPC[yRand][xRand] = 6;
		}
		else if (dirRand == 0)
		{
			for (int i = len; i >= 0; i--)
			{
				mapPC[yRand][xRand - i] = 3; // 3 baraye keshti ofghi ast
			}
		}
		else if (dirRand == 1)
		{
			for (int i = len; i >= 0; i--)
			{
				mapPC[yRand - i][xRand] = 4; // 4 baraye keshti amodi
			}
		}
	}
}
bool check(int y, int x, int dir, int ship, int len, bool first) //check kardane atrafe keshti // baraye functione generate
{
	if (dir == 0)
	{
		if (x - len > 0 && first)
		{
			if (mapPC[y][x - len - 1] != 0) return true;
			if (y > 0)	 if (mapPC[y - 1][x - len - 1] != 0) return true;// for debug access vaiolation
			if (y < 9)	 if (mapPC[y + 1][x - len - 1] != 0)	return true;// for debug access vaiolation
		}

		if (x  < 9 && first)
		{
			if (mapPC[y][x + 1] != 0) return true;
			if (y > 0)	 if (mapPC[y - 1][x + 1] != 0) return true;// for debug access vaiolation
			if (y < 9)	 if (mapPC[y + 1][x + 1] != 0)	return true;// for debug access vaiolation
		}

		if (mapPC[y][x - len] != 0) return true;
		if (y > 0)	 if (mapPC[y - 1][x - len] != 0)	return true;// for debug access vaiolation
		if (y < 9)	 if (mapPC[y + 1][x - len] != 0)	return true;// for debug access vaiolation

		if (len == 0)	return false;

		else return check(y, x, dir, ship, --len, false);
	}
	if (dir == 1)
	{
		if (y - len > 0 && first)
		{
			if (mapPC[y - len - 1][x] != 0) return true;
			if (x > 0)	 if (mapPC[y - len - 1][x - 1] != 0) return true;// if (x > 0) for debug access vaiolation
			if (x < 9)	 if (mapPC[y - len - 1][x + 1] != 0)	return true;// if (x < 9) for debug access vaiolation
		}

		if (y < 9 && first)
		{
			if (mapPC[y + 1][x] != 0) return true;
			if (x > 0)	 if (mapPC[y + 1][x - 1] != 0) return true;// for debug access vaiolation
			if (x < 9)	 if (mapPC[y + 1][x + 1] != 0)	return true;// for debug access vaiolation
		}

		if (y - len >= 0) if (mapPC[y - len][x] != 0) return true;
		if (x > 0)	 if (mapPC[y - len][x - 1] != 0)	return true;// for debug access vaiolation
		if (x < 9)	 if (mapPC[y - len][x + 1] != 0)	return true;// for debug access vaiolation

		if (len == 0)	return false;

		else return check(y, x, dir, ship, --len, false);
	}
	return false;
}
bool check2(int y, int x, int dir, int ship, int len, bool first) //check kardane atrafe keshti barye user
{
	if (dir == 0)
	{
		if (x + len < 9 && first)
		{
			if (mapUser[y][x + len + 1] != 0) return true;
			if (y > 0)	 if (mapUser[y - 1][x + len + 1] != 0) return true;// for debug access vaiolation
			if (y < 9)	 if (mapUser[y + 1][x + len + 1] != 0)	return true;// for debug access vaiolation
		}

		if (x > 0 && first)
		{
			if (mapUser[y][x - 1] != 0) return true;
			if (y > 0)	 if (mapUser[y - 1][x - 1] != 0) return true;// for debug access vaiolation
			if (y < 9)	 if (mapUser[y + 1][x - 1] != 0)	return true;// for debug access vaiolation
		}

		if (mapUser[y][x + len] != 0) return true;
		if (y > 0)	 if (mapUser[y - 1][x + len] != 0)	return true;// for debug access vaiolation
		if (y < 9)	 if (mapUser[y + 1][x + len] != 0)	return true;// for debug access vaiolation

		if (len == 0)	return false;

		else return check2(y, x, dir, ship, --len, false);
	}
	if (dir == 1)
	{
		if (y + len < 9 && first)
		{
			if (mapUser[y + len + 1][x] != 0) return true;
			if (x > 0)	 if (mapUser[y + len + 1][x - 1] != 0) return true;// if (x > 0) for debug access vaiolation
			if (x < 9)	 if (mapUser[y + len + 1][x + 1] != 0)	return true;// if (x < 9) for debug access vaiolation
		}

		if (y > 0 && first)
		{
			if (mapUser[y - 1][x] != 0) return true;
			if (x > 0)	 if (mapUser[y - 1][x - 1] != 0) return true;// for debug access vaiolation
			if (x < 9)	 if (mapUser[y - 1][x + 1] != 0)	return true;// for debug access vaiolation
		}

		if (y + len < 10) if (mapUser[y + len][x] != 0) return true;
		if (x > 0)	 if (mapUser[y + len][x - 1] != 0)	return true;// for debug access vaiolation
		if (x < 9)	 if (mapUser[y + len][x + 1] != 0)	return true;// for debug access vaiolation

		if (len == 0)	return false;

		else return check2(y, x, dir, ship, --len, false);
	}
	return false;
}
void changeColorIfInCurser(int mode, int line, int x)  // taghire range screen agar curser darone khaneye ke mikhahim chap konim bashad
{
	if (set && (curserCellX == x &&curserCellY == line)) // set vaghti true ast ke user dar hale chidane map ast
	{
		SetConsoleTextAttribute(hstdout, 33);
	}
	else if (set && curserDir == 0 && (curserCellX + curserLen >= x && curserCellX <= x &&curserCellY == line))
	{
		SetConsoleTextAttribute(hstdout, 33);
	}
	else if (set && curserDir == 1 && (curserCellX == x && curserCellY <= line && curserCellY + curserLen >= line))
	{
		SetConsoleTextAttribute(hstdout, 33);
	}
	else if (!set &&
		(((curserCellX == x &&curserCellY == line) && mode == 2) || (randomX == x &&randomY == line) && mode == 1))
	{
		SetConsoleTextAttribute(hstdout, 33);
	}
}
bool chechWin(int T) // return true =continue game // check kardane bord va bakht
{
	int map;
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (T == 1) map = mapUser[y][x];
			else if (T == 2) map = mapPC[y][x];

			if (map == 3 || map == 4 || map == 6) return true; // hanoz kheshtiei vojod darad ke tir nakhorde
		}
	}
	return false;
}
void showLine(int line, int mode) // namayesh khat be khate map
{
	int map;
	printf("%c", 'A' + line);
	SetConsoleTextAttribute(hstdout, 15);
	printf(" %c", '|');
	for (int x = 0; x < 10; x++)
	{
		if (mode == 1) map = mapUser[line][x];
		else if (mode == 2) map = mapPC[line][x];
		switch (map)
		{
		case 0:
			changeColorIfInCurser(mode, line, x); // my function
			printf(" ");
			break;
		case 1:
			SetConsoleTextAttribute(hstdout, 4);
			changeColorIfInCurser(mode, line, x); // my function
			printf("%c", 'o');
			break;
		case 2:
			SetConsoleTextAttribute(hstdout, 02);
			changeColorIfInCurser(mode, line, x); // my function
			printf("%c", 'X');
			break;
		case 3: // keshti ro be pain // jahat baraye rahati dar check kardane atraf
			if (mode == 1 || ok == false) SetConsoleTextAttribute(hstdout, 22);
			changeColorIfInCurser(mode, line, x); // my function
			printf(" ");//
			break;
		case 4: // keshti ba jahate pain
			if (mode == 1 || ok ==false)SetConsoleTextAttribute(hstdout, 22);
			changeColorIfInCurser(mode, line, x); // my function
			printf(" ");
			break;
		case 5: // functione shot bad az khali kardan 5 migozarad
			SetConsoleTextAttribute(hstdout, 03);
			changeColorIfInCurser(mode, line, x); // my function
			printf("%c", 'o');
			break;
		case 6: // keshti bedone jahat // yek celloli
			if (mode == 1 || ok == false) SetConsoleTextAttribute(hstdout, 22);
			changeColorIfInCurser(mode, line, x); // my function
			printf(" ");//
		}//end switch case
		SetConsoleTextAttribute(hstdout, 15);
		printf("%c", '|');
	}// end for
}
void showMap(int line) // namayeshe khat be khate naghshe be sorate recursive
{
	SetConsoleTextAttribute(hstdout, 3);
	if (line == 0)
	{
		// vaghti set true ast yani user dar hale chidane map ast
		if (!set) printf("%s%s%s%s%s\n%s\n", userName, "'s Map", "                     ",PCName,"'s Map", "   1 2 3 4 5 6 7 8 9 10     1 2 3 4 5 6 7 8 9 10");// vaghti user dar hale chidane map nist => mape pc ro neshon nade
		else printf("%s%s%s", userName, "'s Map\n", "   1 2 3 4 5 6 7 8 9 10\n");
	}
	SetConsoleTextAttribute(hstdout, 3);
	showLine(line, 1);
	if (!set)
	{
		printf("  ");
		showLine(line, 2); // vaghti user dar hale chidane map nist => mape pc ro neshon nade
	}
	if (!set) printf("%s", "\n  ---------------------    ---------------------\n");
	else printf("%s", "\n  ---------------------\n");

	if (line < 9) showMap(++line);
}
bool attack(int mode) // mode 1 = turn user // mode 2= turn pc
{
	int map;
	if (mode == 1)	map = mapPC[curserCellY][curserCellX];
	else if (mode == 2)
	{
		do
		{
			randomY = rand() % 10;
			randomX = rand() % 10 ;
			map = mapUser[randomY][randomX];
		} while (map != 3 && map != 0 && map != 4 && map != 6);
		printf("%s", "turn pc");
		Sleep(1000);
	}

	if (map == 3 || map == 4 || map == 0 || map == 6)
	{
		systemCls = true;
		if (map == 3 || map == 4 || map == 6)
		{
			if (mode == 1)
			{
				shot(mode, curserCellY, curserCellX);
				mapPC[curserCellY][curserCellX] = 2;
			}
			else if (mode == 2)
			{
				shot(mode, randomY, randomX);
				mapUser[randomY][randomX] = 2;
			}
			//	if (mode == 1)	curser(77);
			return true;
		}
		else if (map == 0)
		{
			if (mode == 1)	mapPC[curserCellY][curserCellX] = 1;
			else if (mode == 2)	mapUser[randomY][randomX] = 1;
			if (turn == 1)	turn = 2;
			else if (turn == 2) turn = 1;
			//	if (mode == 1)	curser(77);
			return false;
		}
	}
	else
	{
		if (mode == 1) curser(77); // agar hadaf user roye celloli ke ghablan tir khorde bod
		systemCls = true;
	}

	return true;
}
void shot(int mode, int y, int x) //khali kardane cellol hy ke keshti dar anja nist
{
	int **map = new int*[10];
	for (int i = 0; i < 10; i++)
	{
		map[i] = new int[10];
		if (mode == 1) map[i] = &mapPC[i][0];
		if (mode == 2) map[i] = &mapUser[i][0];
	}
	if (y > 0 && x > 0) if (map[y - 1][x - 1] != 1) map[y - 1][x - 1] = 5;
	if (y < 9 && x<9) if (map[y + 1][x + 1] != 1) map[y + 1][x + 1] = 5;
	if (y>0 && x < 9) if (map[y - 1][x + 1] != 1)map[y - 1][x + 1] = 5;
	if (y<9 && x>0) if (map[y + 1][x - 1] != 1)map[y + 1][x - 1] = 5;
	bool allBoatDistroy = true; // agar hameye keshti kharab nashode bod false mishavad
	int startBoat = -1;
	int endBoat = -1;
	if (map[y][x] == 3) // keshti ofoghi
	{
		if (x > 0)
		{
			if (map[y][x - 1] == 3) allBoatDistroy = false;
			else if (map[y][x - 1] == 2)
			{
				startBoat = x - 2;
				for (int i = 2; i < 4 && x - i >= 0; i++)
				{
					if (map[y][x - i] == 0 || map[y][x - i] == 1)
					{
						startBoat = x - i;
						break;
					}
					else if (map[y][x - i] == 2) startBoat = x - i;
					else if (map[y][x - i] == 3)
					{
						allBoatDistroy = false;
						break;
					}
				}
			}//end else if
			else if (map[y][x - 1] == 0 || map[y][x - 1] == 1) startBoat = x - 1;
		} // end if (x>0)
		if (x < 9)
		{
			if (map[y][x + 1] == 3) allBoatDistroy = false;
			else if (map[y][x + 1] == 2)
			{
				endBoat = x + 2;
				for (int i = 2; i < 4 && x + i <= 9; i++)
				{
					if (map[y][x + i] == 0 || map[y][x + i] == 1)
					{
						endBoat = x + i;
						break;
					}

					else if (map[y][x + i] == 2) endBoat = x + i;
					else if (map[y][x + i] == 3)
					{
						allBoatDistroy = false;
						break;
					}
				}
			}//end else if map==3
			else if (map[y][x + 1] == 0 || map[y][x + 1] == 1) endBoat = x + 1;
		}//end if(x<9)
	}//end if map==3

	else if (map[y][x] == 4) // keshti amodi
	{
		if (y > 0)
		{
			if (map[y - 1][x] == 4) allBoatDistroy = false;
			else if (map[y - 1][x] == 2)
			{
				startBoat = y - 1;
				for (int i = 2; i < 4 && y - i >= 0; i++)
				{
					if (map[y - i][x] == 0)
					{
						startBoat = y - i;
						break;
					}
					else if (map[y - i][x] == 2) startBoat = x - i;
					else if (map[y - i][x] == 4)
					{
						allBoatDistroy = false;
						break;
					}
				}
			}//end else if
			else if (map[y - 1][x] == 0) startBoat = y - 1;
		} // end if (x>0)
		if (y < 9)
		{
			if (map[y + 1][x] == 4) allBoatDistroy = false;
			else if (map[y + 1][x] == 2)
			{
				endBoat = y + 1;
				for (int i = 2; i < 4 && y + i <= 9; i++)
				{
					if (map[y + i][x] == 0)
					{
						endBoat = y + i;
						break;
					}

					else if (map[y + i][x] == 2) endBoat = y + i;
					else if (map[y + i][x] == 4)
					{
						allBoatDistroy = false;
						break;
					}
				}
			}//end else if map==4
			else if (map[y + 1][x] == 0) endBoat = y + 1;
		}//end if(y<9)
	}//end if map==4

	bool temp = false;
	if (map[y][x] == 6) temp = true;
	if (temp && x > 0) if (map[y][x - 1] == 0) map[y][x - 1] = 5;
	if (temp && x < 9) if (map[y][x + 1] == 0) map[y][x + 1] = 5;
	if (temp && y > 0) if (map[y - 1][x] == 0) map[y - 1][x] = 5;
	if (temp && y < 9) if (map[y + 1][x] == 0) map[y + 1][x] = 5;
	if (temp) allBoatDistroy = false;

	if (map[y][x] == 3 && allBoatDistroy && (endBoat != -1 || x == 9) && (startBoat != -1 || x == 0))
	{
		if (startBoat != -1) if (map[y][startBoat] == 0) map[y][startBoat] = 5;
		if (endBoat != -1) if (map[y][endBoat] == 0) map[y][endBoat] = 5;
		if (y > 0) if (map[y - 1][startBoat] == 0)  map[y - 1][startBoat] = 5;
		if (y < 9) if (map[y + 1][endBoat] == 0)  map[y + 1][endBoat] = 5;
	}
	else if (map[y][x] == 4 && allBoatDistroy && (endBoat != -1 || y == 9) && (startBoat != -1 || y == 0))
	{
		if (startBoat != -1) if (map[startBoat][x] == 0) map[startBoat][x] = 5;
		if (endBoat != -1) if (map[endBoat][x] == 0) map[endBoat][x] = 5;
		if (y > 0)  if (map[startBoat][x - 1] == 0) map[startBoat][x - 1] = 5;
		if (y < 9)  if (map[endBoat][x + 1] == 0) map[endBoat][x + 1] = 5;
	}
}
void curser(int direction) // taghire jaye curser
{
	switch (direction)
	{
	case 72://up
		if (curserDir == 0)
		{
			if (curserCellY - 1 >= 0)
			{
				curserCellY -= 1;
			}
			else if (curserCellY - 1 <= -1)
			{
				curserCellY = 9;
			}
		}
		if (curserDir == 1)
		{
			if (curserCellY - 1 >= 0)
			{
				curserCellY -= 1;
			}
			else if (curserCellY - 1 <= -1)
			{
				curserCellY = 9 - curserLen;
			}
		}
		systemCls = true;
		break;
	case 80://down
		if (curserDir == 0)
		{
			if (curserCellY + 1 < 10)
			{
				curserCellY += 1;
			}
			else if (curserCellY + 1 >= 10)
			{
				curserCellY = 0;
			}
		}
		if (curserDir == 1)
		{
			if (curserCellY + curserLen + 1 < 10)
			{
				curserCellY += 1;
			}
			else if (curserCellY + curserLen + 1 >= 10)
			{
				curserCellY = 0;
			}
		}
		systemCls = true;
		break;
	case 77://right
		if (curserDir == 0)
		{
			if (curserCellX + 1 <= 10)
			{
				if (curserCellX + curserLen + 1 >= 10 && curserCellY + 1 < 10)
				{
					curserCellY += 1;
					curserCellX = 0;
				}
				else if (curserCellX + curserLen + 1 >= 10 && curserCellY == 9)
				{
					curserCellX = 0;
					curserCellY = 0;
				}
				else if (curserCellX + curserLen + 1 < 10)
				{
					curserCellX += 1;
				}
			}
		}
		if (curserDir == 1)
		{
			if (curserCellX + 1 <= 10)
			{
				if (curserCellX + 1 >= 10 && curserCellY + curserLen + 1 < 10)
				{
					curserCellY += 1;
					curserCellX = 0;
				}
				else if (curserCellX + 1 >= 10 && curserCellY + curserLen >= 9)
				{
					curserCellX = 0;
					curserCellY = 0;
				}
				else if (curserCellX + 1 < 10)
				{
					curserCellX += 1;
				}
			}
		}
		systemCls = true;
		break;
	case 75://left
		if (curserDir == 0)
		{
			if (curserCellX - 1 >= -1)
			{
				if (curserCellX >= 0 && curserCellY == 0)
				{
					curserCellX = 9 - curserLen;
					curserCellY = 9;
				}
				else if (curserCellX == 0 && curserCellY > 0)
				{
					curserCellX = 9 - curserLen;
					curserCellY -= 1;
				}
				else if (curserCellX >= 0 && curserCellY > 0)
				{
					curserCellX -= 1;
				}
			}
		}
		if (curserDir == 1)
		{
			if (curserCellX - 1 >= -1)
			{
				if (curserCellX == 0 && curserCellY == 0)
				{
					curserCellX = 9;
					curserCellY = 9 - curserLen;
				}
				else if (curserCellX == 0 && curserCellY > 0)
				{
					curserCellX = 9;
					curserCellY -= 1;
				}
				else if (curserCellX >= 0)
				{
					curserCellX -= 1;
				}
			}
		}
		systemCls = true;
		break;
	}
}