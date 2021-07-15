#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstring>

#define LUNGIME 8
#define PionNEGRU1 11 //
#define PionNEGRU2 12 //
#define PionNEGRU3 13 //
#define PionNEGRU4 14 //
#define PionNEGRU5 15 //
#define PionNEGRU6 16 //
#define PionNEGRU7 17 //
#define PionNEGRU8 18 //
#define PionALB -1
#define TurnNEGRU1 21 //
#define TurnNEGRU2 22 //
#define TurnALB -2
#define CalALB -3
#define CalNEGRU1 31 //
#define CalNEGRU2 32 //
#define NebunNEGRU1 41 //
#define NebunNEGRU2 42 //
#define NebunALB -4
#define ReginaALB -5
#define ReginaNEGRU 5 //
#define RegeNEGRU 6 //
#define RegeALB -6
#define size_struct 40
#define step_struct 40

using namespace sf;
//using namespace std;

/*struct poz
{
	int x, y;
}oldPoz, regeleAlb, regeleNegru, pionNegru1, pionNegru2, pionNegru3, pionNegru4 pionNegru5, pionNegru6, pionNegru7, pionNegru8, transformA, transformN;*/

struct poz {
	int x, y;
}poz_mas[size_struct];

struct Step {
	int point;	
	int name;
	int deistvie; // 0 - ходить, 1 - бить
	int marker;
	int oldx;
	int oldy;
	int life;
}step_mas[step_struct];

/*poz_mas[0] = pionNegru1
poz_mas[1] = pionNegru2
poz_mas[2] = pionNegru3
poz_mas[3] = pionNegru4
poz_mas[4] = pionNegru5
poz_mas[5] = pionNegru6
poz_mas[6] =  pionNegru7
poz_mas[7] = pionNegru8
poz_mas[8] = calNegru1
poz_mas[9] = calNegru2
poz_mas[10] = turnNegru1
poz_mas[11] = turnNegru2
poz_mas[12] = nebunNegru1
poz_mas[13] = nebunNegru2
poz_mas[14] = reginaNegru
poz_mas[15] = regeNegru

poz_mas[16] = regeleAlb
poz_mas[17] = regeleNegru
poz_mas[18] = oldPoz 
poz_mas[19] = transformA
poz_mas[20] = transformN
*/

const int Size_Board = 8;
int  size = 75, move = 0, x, y, n = 0;
int board[8][8] =
{ 21, 31, 41, 5, 6, 42, 32, 22,
  11, 12, 13, 14, 15, 16, 17, 18,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
 -1,-1,-1,-1,-1,-1,-1,-1,
 -2,-3,-4,-5,-6,-4,-3,-2, };

int turnAlbDreapta = 0, turnAlbStanga = 0, regeAlb = 0;
int turnNegruDreapta = 0, turnNegruStanga = 0, regeNegru = 0;

int mutare = 0; // 0 - ход белыми, 1 - ход черными

int sahAlb = 0, sahNegru = 0, sahPionNegru = 0;

int transformareAlb = 0, transformareNegru = 0;

int PionA(int ox, int oy, int nx, int ny)
{
	if (poz_mas[18].y == 6)
	{
		if ((ny == oy - 1 && nx == ox && board[oy - 1][ox] == 0) || (ny == oy - 2 && nx == ox && board[oy - 1][ox] == 0 && board[oy - 2][ox] == 0))
		{
			return 1;
		}
	}
	else if (ny == oy - 1 && nx == ox && board[oy - 1][ox] == 0)
	{
		return 1;
	}
	if (board[oy - 1][ox - 1] > 0)
	{
		if (ny == oy - 1 && nx == ox - 1)
		{
			return 1;
		}
	}
	if (board[oy - 1][ox + 1] > 0)
	{
		if (ny == oy - 1 && nx == ox + 1)
		{
			return 1;
		}
	}
	return 0;
}

int PionN(int ox, int oy, int nx, int ny)
{
	if (poz_mas[18].y == 1)
	{
		if ((ny == oy + 1 && nx == ox && board[oy + 1][ox] == 0) || (ny == oy + 2 && nx == ox && board[oy + 1][ox] == 0 && board[oy + 2][ox] == 0))
		{
			return 1;
		}
	}
	else if (ny == oy + 1 && nx == ox && board[oy + 1][ox] == 0)
	{
		return 1;
	}
	if (board[oy + 1][ox - 1] < 0) // бить левее 
	{
		if (ny == oy + 1 && nx == ox - 1)
		{
			return 1;
		}
	}
	if (board[oy + 1][ox + 1] < 0) // бить правее
	{
		if (ny == oy + 1 && nx == ox + 1)
		{
			return 1;
		}
	}
	return 0;
}

int TurnA(int ox, int oy, int nx, int ny)
{
	for (int i = ox - 1; i >= 0; i--) // spre stanga
	{
		if (board[oy][i] >= 0 && (nx == i && ny == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--) // sus
	{
		if (board[i][ox] >= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i <= 7; i++) // spre dreapta
	{
		if (board[oy][i] >= 0 && (ny == oy && nx == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i <= 7; i++) // jos
	{
		if (board[i][ox] >= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	return 0;
}

int TurnN(int ox, int oy, int nx, int ny)
{
	for (int i = ox - 1; i >= 0; i--) // spre stanga
	{
		if (board[oy][i] <= 0 && (nx == i && ny == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--) // sus
	{
		if (board[i][ox] <= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i <= 7; i++) // spre dreapta
	{
		if (board[oy][i] <= 0 && (ny == oy && nx == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i <= 7; i++) // jos
	{
		if (board[i][ox] <= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	return 0;
}

int NebunA(int ox, int oy, int nx, int ny)
{
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) // spre stanga sus
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--) // spre dreapta sus
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++) // spre stanga jos
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= 7; i++)  // spre dreapta jos
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int NebunN(int ox, int oy, int nx, int ny)
{
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) // spre stanga sus
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--) // spre dreapta sus
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++) // spre stanga jos
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= 7; i++)  // spre dreapta jos
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int ReginaA(int ox, int oy, int nx, int ny)
{
	for (int i = ox - 1; i >= 0; i--) // spre stanga
	{
		if (board[oy][i] >= 0 && (nx == i && ny == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--) // sus
	{
		if (board[i][ox] >= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i <= 7; i++) // spre dreapta
	{
		if (board[oy][i] >= 0 && (ny == oy && nx == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i <= 7; i++) // jos
	{
		if (board[i][ox] >= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) // spre stanga sus
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--) // spre dreapta sus
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++) // spre stanga jos
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= 7; i++)  // spre dreapta jos
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int ReginaN(int ox, int oy, int nx, int ny)
{
	for (int i = ox - 1; i >= 0; i--) // spre stanga
	{
		if (board[oy][i] <= 0 && (nx == i && ny == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--) // sus
	{
		if (board[i][ox] <= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i <= 7; i++) // spre dreapta
	{
		if (board[oy][i] <= 0 && (ny == oy && nx == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i <= 7; i++) // jos
	{
		if (board[i][ox] <= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) // spre stanga sus
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--) // spre dreapta sus
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++) // spre stanga jos
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= 7; i++)  // spre dreapta jos
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int CalA(int ox, int oy, int nx, int ny)
{
	if (oy - 2 >= 0 && ox - 1 >= 0 && ny == oy - 2 && nx == ox - 1 && board[ny][nx] >= 0)
	{
		return 1; // stanga sus
	}
	if (oy - 2 >= 0 && ox + 1 < LUNGIME && ny == oy - 2 && nx == ox + 1 && board[ny][nx] >= 0)
	{
		return 1; // dreapta sus
	}
	if (oy - 1 >= 0 && ox + 2 < LUNGIME && ny == oy - 1 && nx == ox + 2 && board[ny][nx] >= 0)
	{
		return 1; // dreapta 1
	}
	if (oy + 1 >= 0 && ox + 2 < LUNGIME && ny == oy + 1 && nx == ox + 2 && board[ny][nx] >= 0)
	{
		return 1; // dreapta 2
	}
	if (oy + 2 < LUNGIME && ox + 1 < LUNGIME && ny == oy + 2 && nx == ox + 1 && board[ny][nx] >= 0)
	{
		return 1; // jos 1
	}
	if (oy + 2 < LUNGIME && ox - 1 >= 0 && ny == oy + 2 && nx == ox - 1 && board[ny][nx] >= 0)
	{
		return 1; //jos 2
	}
	if (oy + 1 < LUNGIME && ox - 2 >= 0 && ny == oy + 1 && nx == ox - 2 && board[ny][nx] >= 0)
	{
		return 1; // stanga 1
	}
	if (oy - 1 >= 0 && ox - 2 >= 0 && ny == oy - 1 && nx == ox - 2 && board[ny][nx] >= 0)
	{
		return 1;
	}
	return 0;
}

int CalN(int ox, int oy, int nx, int ny)
{
	if (oy - 2 >= 0 && ox - 1 >= 0 && ny == oy - 2 && nx == ox - 1 && board[ny][nx] <= 0)
	{
		return 1; // stanga sus
	}
	if (oy - 2 >= 0 && ox + 1 < LUNGIME && ny == oy - 2 && nx == ox + 1 && board[ny][nx] <= 0)
	{
		return 1; // dreapta sus
	}
	if (oy - 1 >= 0 && ox + 2 < LUNGIME && ny == oy - 1 && nx == ox + 2 && board[ny][nx] <= 0)
	{
		return 1; // dreapta 1
	}
	if (oy + 1 >= 0 && ox + 2 < LUNGIME && ny == oy + 1 && nx == ox + 2 && board[ny][nx] <= 0)
	{
		return 1; // dreapta 2
	}
	if (oy + 2 < LUNGIME && ox + 1 < LUNGIME && ny == oy + 2 && nx == ox + 1 && board[ny][nx] <= 0)
	{
		return 1; // jos 1
	}
	if (oy + 2 < LUNGIME && ox - 1 >= 0 && ny == oy + 2 && nx == ox - 1 && board[ny][nx] <= 0)
	{
		return 1; //jos 2
	}
	if (oy + 1 < LUNGIME && ox - 2 >= 0 && ny == oy + 1 && nx == ox - 2 && board[ny][nx] <= 0)
	{
		return 1; // stanga 1
	}
	if (oy - 1 >= 0 && ox - 2 >= 0 && ny == oy - 1 && nx == ox - 2 && board[ny][nx] <= 0)
	{
		return 1;
	}
	return 0;
}


int PionASah(int posx, int posy, int regex, int regey)
{
	if (board[posy - 1][posx - 1] >= 0)
	{
		if (posy - 1 == regey && posx - 1 == regex)
		{
			return 1;
		}
	}
	if (board[posy - 1][posx + 1] >= 0)
	{		
		if (posy - 1 == regey && posx + 1 == regex)
		{
			return 1;
		}
	}
	return 0;
}

int TurnASah(int ox, int oy, int regex, int regey)
{
	for (int i = ox - 1; i >= 0; i--) // spre stanga
	{
		if (board[oy][i] >= 0 && (regex == i && regey == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--) // sus
	{
		if (board[i][ox] >= 0 && (regey == i && regex == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i < LUNGIME; i++) // spre dreapta
	{
		if (board[oy][i] >= 0 && (regey == oy && regex == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i < LUNGIME; i++) // jos
	{
		if (board[i][ox] >= 0 && (regey == i && regex == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	return 0;
}

int NebunASah(int ox, int oy, int regex, int regey)
{
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) // spre stanga sus
	{
		if (board[i][j] >= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--) // spre dreapta sus
	{
		if (board[i][j] >= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++) // spre stanga jos
	{
		if (board[i][j] >= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= 7; i++)  // spre dreapta jos
	{
		if (board[i][j] >= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int ReginaASah(int ox, int oy, int regex, int regey)
{
	for (int i = ox - 1; i >= 0; i--) // spre stanga
	{
		if (board[oy][i] >= 0 && (regex == i && regey == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--) // sus
	{
		if (board[i][ox] >= 0 && (regey == i && regex == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i < LUNGIME; i++) // spre dreapta
	{
		if (board[oy][i] >= 0 && (regey == oy && regex == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i < LUNGIME; i++) // jos
	{
		if (board[i][ox] >= 0 && (regey == i && regex == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) // вверху слева
	{
		if (board[i][j] >= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--) // вверху справа
	{
		if (board[i][j] >= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++) // в нижнем левом углу
	{
		if (board[i][j] >= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i < LUNGIME; i++)  //в правом нижнем углу
	{
		if (board[i][j] >= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int CalASah(int ox, int oy, int regex, int regey)
{
	if (oy - 2 >= 0 && ox - 1 >= 0 && regey == oy - 2 && regex == ox - 1 && board[regey][regex] >= 0)
	{
		return 1; // stanga sus
	}
	if (oy - 2 >= 0 && ox + 1 < LUNGIME && regey == oy - 2 && regex == ox + 1 && board[regey][regex] >= 0)
	{
		return 1; // dreapta sus
	}
	if (oy - 1 >= 0 && ox + 2 < LUNGIME && regey == oy - 1 && regex == ox + 2 && board[regey][regex] >= 0)
	{
		return 1; // dreapta 1
	}
	if (oy + 1 >= 0 && ox + 2 < LUNGIME && regey == oy + 1 && regex == ox + 2 && board[regey][regex] >= 0)
	{
		return 1; // dreapta 2
	}
	if (oy + 2 < LUNGIME && ox + 1 < LUNGIME && regey == oy + 2 && regex == ox + 1 && board[regey][regex] >= 0)
	{
		return 1; // jos 1
	}
	if (oy + 2 < LUNGIME && ox - 1 >= 0 && regey == oy + 2 && regex == ox - 1 && board[regey][regex] >= 0)
	{
		return 1; //jos 2
	}
	if (oy + 1 < LUNGIME && ox - 2 >= 0 && regey == oy + 1 && regex == ox - 2 && board[regey][regex] >= 0)
	{
		return 1; // stanga 1
	}
	if (oy - 1 >= 0 && ox - 2 >= 0 && regey == oy - 1 && regex == ox - 2 && board[regey][regex] >= 0)
	{
		return 1;
	}
	return 0;
}

int RegeASah(int ox, int oy, int regex, int regey)
{
	if (ox - 1 >= 0 && oy - 1 >= 0 && regey == oy - 1 && regex == ox - 1 && board[regey][regex] <= 0)
	{
		return 1;
	}
	if (oy - 1 >= 0 && regex == ox && regey == oy - 1 && board[regey][regex] <= 0)
	{
		return 1;
	}
	if (oy - 1 >= 0 && ox + 1 < LUNGIME && regex == ox + 1 && regey == oy - 1 && board[regey][regex] <= 0)
	{
		return 1;
	}
	if (ox + 1 < LUNGIME && regey == oy && regex == ox + 1 && board[regey][regex] <= 0)
	{
		return 1;
	}
	if (ox + 1 < LUNGIME && oy + 1 < LUNGIME && regey == oy + 1 && regex == ox + 1 && board[regey][regex] <= 0)
	{
		return 1;
	}
	if (oy + 1 < LUNGIME && regey == oy + 1 && regex == ox && board[regey][regex] <= 0)
	{
		return 1;
	}
	if (ox - 1 >= 0 && oy + 1 < LUNGIME && regex == ox - 1 && regey == oy + 1 && board[regey][regex] <= 0)
	{
		return 1;
	}
	if (ox - 1 >= 0 && regey == oy && regex == ox - 1 && board[regey][regex] <= 0)
	{
		return 1;
	}
	return 0;
}


int PionNSah(int ox, int oy, int regex, int regey)
{
	if (board[oy + 1][ox - 1] <= 0)
	{
		if (regey == oy + 1 && regex == ox - 1)
		{
			return 1;
		}
	}
	if (board[oy + 1][ox + 1] <= 0)
	{
		if (regey == oy + 1 && regex == ox + 1)
		{
			return 1;
		}
	}
	return 0;
}

int TurnNSah(int ox, int oy, int regex, int regey)
{
	for (int i = ox - 1; i >= 0; i--) // Слева
	{
		if (board[oy][i] <= 0 && (regex == i && regey == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--) // вверх
	{
		if (board[i][ox] <= 0 && (regey == i && regex == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i < LUNGIME; i++) // Направо
	{
		if (board[oy][i] <= 0 && (regey == oy && regex == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i < LUNGIME; i++) // вниз
	{
		if (board[i][ox] <= 0 && (regey == i && regex == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	return 0;
}

int NebunNSah(int ox, int oy, int regex, int regey)
{
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) // вверху слева
	{
		if (board[i][j] <= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--) // вверху справа
	{
		if (board[i][j] <= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++) // в нижнем левом углу
	{
		if (board[i][j] <= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= 7; i++)  // в правом нижнем углу
	{
		if (board[i][j] <= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int ReginaNSah(int ox, int oy, int regex, int regey)
{
	for (int i = ox - 1; i >= 0; i--) // Слева
	{
		if (board[oy][i] <= 0 && (regex == i && regey == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--) // вверх
	{
		if (board[i][ox] <= 0 && (regey == i && regex == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i < LUNGIME; i++) // Направо
	{
		if (board[oy][i] <= 0 && (regey == oy && regex == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i < LUNGIME; i++) // вниз
	{
		if (board[i][ox] <= 0 && (regey == i && regex == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) // вверху слева
	{
		if (board[i][j] <= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--) // вверху справа
	{
		if (board[i][j] <= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++) // в нижнем левом углу
	{
		if (board[i][j] <= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i < LUNGIME; i++)  // в правом нижнем углу
	{
		if (board[i][j] <= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int CalNSah(int ox, int oy, int regex, int regey)
{
	if (oy - 2 >= 0 && ox - 1 >= 0 && regey == oy - 2 && regex == ox - 1 && board[regey][regex] <= 0)
	{
		return 1; // stanga sus
	}
	if (oy - 2 >= 0 && ox + 1 < LUNGIME && regey == oy - 2 && regex == ox + 1 && board[regey][regex] <= 0)
	{
		return 1; // dreapta sus
	}
	if (oy - 1 >= 0 && ox + 2 < LUNGIME && regey == oy - 1 && regex == ox + 2 && board[regey][regex] <= 0)
	{
		return 1; // dreapta 1
	}
	if (oy + 1 >= 0 && ox + 2 < LUNGIME && regey == oy + 1 && regex == ox + 2 && board[regey][regex] <= 0)
	{
		return 1; // dreapta 2
	}
	if (oy + 2 < LUNGIME && ox + 1 < LUNGIME && regey == oy + 2 && regex == ox + 1 && board[regey][regex] <= 0)
	{
		return 1; // jos 1
	}
	if (oy + 2 < LUNGIME && ox - 1 >= 0 && regey == oy + 2 && regex == ox - 1 && board[regey][regex] <= 0)
	{
		return 1; //jos 2
	}
	if (oy + 1 < LUNGIME && ox - 2 >= 0 && regey == oy + 1 && regex == ox - 2 && board[regey][regex] <= 0)
	{
		return 1; // stanga 1
	}
	if (oy - 1 >= 0 && ox - 2 >= 0 && regey == oy - 1 && regex == ox - 2 && board[regey][regex] <= 0)
	{
		return 1;
	}
	return 0;
}

int RegeNSah(int ox, int oy, int regex, int regey)
{
	if (ox - 1 >= 0 && oy - 1 >= 0 && regey == oy - 1 && regex == ox - 1 && board[regey][regex] >= 0)
	{
		return 1;
	}
	if (oy - 1 >= 0 && regex == ox && regey == oy - 1 && board[regey][regex] >= 0)
	{
		return 1;
	}
	if (oy - 1 >= 0 && ox + 1 < LUNGIME && regex == ox + 1 && regey == oy - 1 && board[regey][regex] >= 0)
	{
		return 1;
	}
	if (ox + 1 < LUNGIME && regey == oy && regex == ox + 1 && board[regey][regex] >= 0)
	{
		return 1;
	}
	if (ox + 1 < LUNGIME && oy + 1 < LUNGIME && regey == oy + 1 && regex == ox + 1 && board[regey][regex] >= 0)
	{
		return 1;
	}
	if (oy + 1 < LUNGIME && regey == oy + 1 && regex == ox && board[regey][regex] >= 0)
	{
		return 1;
	}
	if (ox - 1 >= 0 && oy + 1 < LUNGIME && regex == ox - 1 && regey == oy + 1 && board[regey][regex] >= 0)
	{
		return 1;
	}
	if (ox - 1 >= 0 && regey == oy && regex == ox - 1 && board[regey][regex] >= 0)
	{
		return 1;
	}
	return 0;
}


int RegeNegruSahCheck(int posRegex, int posRegey)
{
	int ok = 0;
	for (int i = 0; i < LUNGIME; i++)
	{
		for (int j = 0; j < LUNGIME; j++)
		{
			if (board[i][j] < 0)
			{
				if (board[i][j] == PionALB)
				{
					ok = PionASah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == TurnALB)
				{
					ok = TurnASah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == CalALB)
				{
					ok = CalASah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == NebunALB)
				{
					ok = NebunASah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == ReginaALB)
				{
					ok = ReginaASah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == RegeALB)
				{
					ok = RegeASah(j, i, posRegex, posRegey);
				}
				if (ok == 1)
				{
					return 0;
				}
			}
		}
	}
	return 1;
}

int RegeN(int ox, int oy, int nx, int ny)
{
	if (ox - 1 >= 0 && oy - 1 >= 0 && ny == oy - 1 && nx == ox - 1 && board[ny][nx] <= 0)
	{
		int ok = RegeNegruSahCheck(ox - 1, oy - 1);
		if (ok == 1)
		{
			return 1;  // stanga sus
		}
	}
	if (oy - 1 >= 0 && nx == ox && ny == oy - 1 && board[ny][nx] <= 0)
	{
		int ok = RegeNegruSahCheck(ox, oy - 1);
		if (ok == 1)
		{
			return 1; // sus
		}
	}
	if (oy - 1 >= 0 && ox + 1 < LUNGIME && nx == ox + 1 && ny == oy - 1 && board[ny][nx] <= 0)
	{
		int ok = RegeNegruSahCheck(ox + 1, oy - 1);
		if (ok == 1)
		{
			return 1; // dreapta sus
		}
	}
	if (ox + 1 < LUNGIME && ny == oy && nx == ox + 1 && board[ny][nx] <= 0)
	{
		int ok = RegeNegruSahCheck(ox + 1, oy);
		if (ok == 1)
		{
			return 1; // dreapta
		}
	}
	if (ox + 1 < LUNGIME && oy + 1 < LUNGIME && ny == oy + 1 && nx == ox + 1 && board[ny][nx] <= 0)
	{
		int ok = RegeNegruSahCheck(ox + 1, oy + 1);
		if (ok == 1)
		{
			return 1; // dreapta jos
		}
	}
	if (oy + 1 < LUNGIME && ny == oy + 1 && nx == ox && board[ny][nx] <= 0)
	{
		int ok = RegeNegruSahCheck(ox, oy + 1);
		if (ok == 1)
		{
			return 1; // jos
		}
	}
	if (ox - 1 >= 0 && oy + 1 < LUNGIME && nx == ox - 1 && ny == oy + 1 && board[ny][nx] <= 0)
	{
		int ok = RegeNegruSahCheck(ox - 1, oy + 1);
		if (ok == 1)
		{
			return 1; // stanga jos
		}
	}
	if (ox - 1 >= 0 && ny == oy && nx == ox - 1 && board[ny][nx] <= 0)
	{
		int ok = RegeNegruSahCheck(ox - 1, oy);
		if (ok == 1)
		{
			return 1; // stanga
		}
	}
	// рокировка напрво
	if (turnNegruDreapta == 0 && regeNegru == 0 && board[0][5] == 0 && board[0][6] == 0 && ny == 0 && nx == 6)
	{
		int ok = RegeNegruSahCheck(4, 0);
		if (ok == 1)
		{
			ok = RegeNegruSahCheck(5, 0);
			if (ok == 1)
			{
				ok = RegeNegruSahCheck(6, 0);
				if (ok == 1)
				{
					regeNegru = 1;
					turnNegruDreapta = 1;
					board[0][7] = 0;
					board[0][5] = TurnNEGRU2;
					return 1;
				}
			}
		}
	}
	if (turnNegruStanga == 0 && regeNegru == 0 && board[0][3] == 0 && board[0][2] == 0 && board[0][1] == 0 && ny == 0 && nx == 2)
	{
		int ok = RegeNegruSahCheck(4, 0);
		if (ok == 1)
		{
			ok = RegeNegruSahCheck(3, 0);
			if (ok == 1)
			{
				ok = RegeNegruSahCheck(2, 0);
				if (ok == 1)
				{
					ok = RegeNegruSahCheck(1, 0);
					if (ok == 1)
					{
						regeNegru = 1;
						turnNegruStanga = 1;
						board[0][0] = 0;
						board[0][3] = TurnNEGRU1;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}


int RegeAlbSahCheck(int posRegex, int posRegey)
{
	int ok = 0;
	for (int i = 0; i < LUNGIME; i++)
	{
		for (int j = 0; j < LUNGIME; j++)
		{
			if (board[i][j] > 0)
			{
				if (board[i][j] == PionNEGRU1 || board[i][j] == PionNEGRU2 || board[i][j] == PionNEGRU3 || board[i][j] == PionNEGRU4 || board[i][j] == PionNEGRU5 || board[i][j] == PionNEGRU6 || board[i][j] == PionNEGRU7 || board[i][j] == PionNEGRU8)
				{
					ok = PionNSah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == TurnNEGRU1 || board[i][j] == TurnNEGRU2)
				{
					ok = TurnNSah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == CalNEGRU1)
				{
					ok = CalNSah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == CalNEGRU2)
				{
					ok = CalNSah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == NebunNEGRU1 || board[i][j] == NebunNEGRU2)
				{
					ok = NebunNSah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == ReginaNEGRU)
				{
					ok = ReginaNSah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == RegeNEGRU)
				{
					ok = RegeNSah(j, i, posRegex, posRegey);
				}
				if (ok == 1)
				{					
					return 0;
				}
			}
		}
	}
	return 1;
}

int RegeA(int ox, int oy, int nx, int ny)
{
	if (ox - 1 >= 0 && oy - 1 >= 0 && ny == oy - 1 && nx == ox - 1 && board[ny][nx] >= 0)
	{
		int ok = RegeAlbSahCheck(ox - 1, oy - 1);
		if (ok == 1)
		{
			return 1;  // stanga sus
		}
	}
	if (oy - 1 >= 0 && nx == ox && ny == oy - 1 && board[ny][nx] >= 0)
	{
		int ok = RegeAlbSahCheck(ox, oy - 1);
		if (ok == 1)
		{
			return 1; // sus
		}
	}
	if (oy - 1 >= 0 && ox + 1 < LUNGIME && nx == ox + 1 && ny == oy - 1 && board[ny][nx] >= 0)
	{
		int ok = RegeAlbSahCheck(ox + 1, oy - 1);
		if (ok == 1)
		{
			return 1; // dreapta sus
		}
	}
	if (ox + 1 < LUNGIME && ny == oy && nx == ox + 1 && board[ny][nx] >= 0)
	{
		int ok = RegeAlbSahCheck(ox + 1, oy);
		if (ok == 1)
		{
			return 1; // dreapta
		}
	}
	if (ox + 1 < LUNGIME && oy + 1 < LUNGIME && ny == oy + 1 && nx == ox + 1 && board[ny][nx] >= 0)
	{
		int ok = RegeAlbSahCheck(ox + 1, oy + 1);
		if (ok == 1)
		{
			return 1; // dreapta jos
		}
	}
	if (oy + 1 < LUNGIME && ny == oy + 1 && nx == ox && board[ny][nx] >= 0)
	{
		int ok = RegeAlbSahCheck(ox, oy + 1);
		if (ok == 1)
		{
			return 1; // jos
		}
	}
	if (ox - 1 >= 0 && oy + 1 < LUNGIME && nx == ox - 1 && ny == oy + 1 && board[ny][nx] >= 0)
	{
		int ok = RegeAlbSahCheck(ox - 1, oy + 1);
		if (ok == 1)
		{
			return 1; // stanga jos
		}
	}
	if (ox - 1 >= 0 && ny == oy && nx == ox - 1 && board[ny][nx] >= 0)
	{
		int ok = RegeAlbSahCheck(ox - 1, oy);
		if (ok == 1)
		{
			return 1; // stanga
		}
	}

	// рокировка направо
	if (regeAlb == 0 && turnAlbDreapta == 0 && board[7][5] == 0 && board[7][6] == 0 && ny == 7 && nx == 6)
	{
		int ok = 1;
		ok = RegeAlbSahCheck(4, 7);
		if (ok == 1)
		{
			ok = RegeAlbSahCheck(5, 7);
			if (ok == 1)
			{
				ok = RegeAlbSahCheck(6, 7);
				if (ok == 1)
				{
					board[7][7] = 0;
					board[7][5] = TurnALB;
					regeAlb = 1;
					turnAlbDreapta = 1;
					return 1;
				}
			}
		}
	}
	// рокировка налево
	if (regeAlb == 0 && turnAlbDreapta == 0 && board[7][3] == 0 && board[7][2] == 0 && board[7][1] == 0 && ny == 7 && nx == 2)
	{
		int ok = 1;
		ok = RegeAlbSahCheck(4, 7);
		if (ok == 1)
		{
			ok = RegeAlbSahCheck(3, 7);
			if (ok == 1)
			{
				ok = RegeAlbSahCheck(2, 7);
				if (ok == 1)
				{
					ok = RegeAlbSahCheck(1, 7);
					if (ok == 1)
					{
						board[7][0] = 0;
						board[7][3] = TurnALB;
						regeAlb = 1;
						turnAlbStanga = 1;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}


void pozRegeAlb()
{
	for (int i = 0; i < LUNGIME; i++)
	{
		for (int j = 0; j < LUNGIME; j++)
		{
			if (board[i][j] == RegeALB)
			{
				poz_mas[16].x = j;
				poz_mas[16].y = i;
				break;
			}
		}
	}
}

void pozRegeNegru()
{
	for (int i = 0; i < LUNGIME; i++)
	{
		for (int j = 0; j < LUNGIME; j++)
		{
			if (board[i][j] == RegeNEGRU)
			{
				poz_mas[17].y = i;
				poz_mas[17].x = j;
				break;
			}
		}
	}
}

int PionNegruSahCheck(int posPionx, int posPiony)//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
{
	int ok = 0;
	for (int i = 0; i < LUNGIME; i++)
	{
		for (int j = 0; j < LUNGIME; j++)
		{
			if (board[i][j] < 0)
			{
				if (board[i][j] == PionALB)
				{
					ok = PionASah(j, i, posPionx, posPiony);
				}
				if (board[i][j] == TurnALB)
				{
					ok = TurnASah(j, i, posPionx, posPiony);
				}
				if (board[i][j] == CalALB)
				{
					ok = CalASah(j, i, posPionx, posPiony);
				}
				if (board[i][j] == NebunALB)
				{
					ok = NebunASah(j, i, posPionx, posPiony);
				}
				if (board[i][j] == ReginaALB)
				{
					ok = ReginaASah(j, i, posPionx, posPiony);
				}
				if (board[i][j] == RegeALB)
				{
					ok = RegeASah(j, i, posPionx, posPiony);
				}
				if (ok == 1)
				{
					return 0; // 0 - шах есть
				}
			}
		}
	}
	return 1; // 1 - шаха нет
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void pozPionNegru()//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
{
	for (int i = 0; i < Size_Board; i++)
	{
		for (int j = 0; j < Size_Board; j++)
		{
			if (board[i][j] == PionNEGRU1)
			{
				poz_mas[0].y = i;
				poz_mas[0].x = j;				
			}			
			if (board[i][j] == PionNEGRU2)
			{
				poz_mas[1].y = i;
				poz_mas[1].x = j;
			}
			if (board[i][j] == PionNEGRU3)
			{
				poz_mas[2].y = i;
				poz_mas[2].x = j;
			}
			if (board[i][j] == PionNEGRU4)
			{
				poz_mas[3].y = i;
				poz_mas[3].x = j;
			}
			if (board[i][j] == PionNEGRU5)
			{
				poz_mas[4].y = i;
				poz_mas[4].x = j;				
			}
			if (board[i][j] == PionNEGRU6)
			{
				poz_mas[5].y = i;
				poz_mas[5].x = j;
			}
			if (board[i][j] == PionNEGRU7)
			{
				poz_mas[6].y = i;
				poz_mas[6].x = j;
			}
			if (board[i][j] == PionNEGRU8)
			{
				poz_mas[7].y = i;
				poz_mas[7].x = j;
			}	
			if (board[i][j] == CalNEGRU1)
			{
				poz_mas[8].y = i;
				poz_mas[8].x = j;
			}
			if (board[i][j] == CalNEGRU2)
			{
				poz_mas[9].y = i;
				poz_mas[9].x = j;
			}
			if (board[i][j] == TurnNEGRU1)
			{
				poz_mas[10].y = i;
				poz_mas[10].x = j;
			}
			if (board[i][j] == TurnNEGRU2)
			{
				poz_mas[11].y = i;
				poz_mas[11].x = j;
			}
			if (board[i][j] == NebunNEGRU1)
			{
				poz_mas[12].y = i;
				poz_mas[12].x = j;
			}
			if (board[i][j] == NebunNEGRU2)
			{
				poz_mas[13].y = i;
				poz_mas[13].x = j;
			}
			if (board[i][j] == ReginaNEGRU)
			{
				poz_mas[14].y = i;
				poz_mas[14].x = j;
			}			
			if (board[i][j] == RegeNEGRU)
			{
				poz_mas[15].y = i;
				poz_mas[15].x = j;
			}
			//-------
			if (board[i][j] == PionALB)
			{
				poz_mas[16].y = i;
				poz_mas[16].x = j;
				board[i][j] = -1;
			}
			if (board[i][j] == TurnALB)
			{
				poz_mas[17].y = i;
				poz_mas[17].x = j;
				board[i][j] = -2;
			}
			if (board[i][j] == CalALB)
			{
				poz_mas[18].y = i;
				poz_mas[18].x = j;
				board[i][j] = -3;
			}
			if (board[i][j] == NebunALB)
			{
				poz_mas[19].y = i;
				poz_mas[19].x = j;
				board[i][j] = -4;
			}
			if (board[i][j] == ReginaALB)
			{
				poz_mas[20].y = i;
				poz_mas[20].x = j;
				board[i][j] = -5;
			}
			if (board[i][j] == RegeALB)
			{
				poz_mas[21].y = i;
				poz_mas[21].x = j;
				board[i][j] = -6;
			}
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	RenderWindow window(VideoMode(600, 600), "Chess");
	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;

	t1.loadFromFile("images/board.png");
	t2.loadFromFile("images/PionNegru.png");
	t3.loadFromFile("images/PionAlb.png");
	t4.loadFromFile("images/TurnNegru.png");
	t5.loadFromFile("images/TurnAlb.png");
	t6.loadFromFile("images/CalAlb.png");
	t7.loadFromFile("images/CalNegru.png");
	t8.loadFromFile("images/NebunNegru.png");
	t9.loadFromFile("images/NebunAlb.png");
	t10.loadFromFile("images/ReginaAlb.png");
	t11.loadFromFile("images/ReginaNegru.png");
	t12.loadFromFile("images/RegeNegru.png");
	t13.loadFromFile("images/RegeAlb.png");
	t14.loadFromFile("images/TransformareAlb.png");
	t15.loadFromFile("images/TransformareNegru.png");

	Sprite tabla(t1);
	Sprite PionNegru(t2);
	Sprite PionAlb(t3);
	Sprite TurnNegru(t4);
	Sprite TurnAlb(t5);
	Sprite CalAlb(t6);
	Sprite CalNegru(t7);
	Sprite NebunNegru(t8);
	Sprite NebunAlb(t9);
	Sprite ReginaAlb(t10);
	Sprite ReginaNegru(t11);
	Sprite RegeNegru(t12);
	Sprite RegeAlb(t13);
	Sprite Mutare;
	Sprite TransformareALB(t14);
	Sprite TransformareNEGRU(t15);

	float dx = 0, dy = 0;
	int numarPiesaMutata = 0;

	step_mas[0].life = 1;
	step_mas[1].life = 1;
	step_mas[2].life = 1;
	step_mas[3].life = 1;
	step_mas[4].life = 1;
	step_mas[5].life = 1;
	step_mas[6].life = 1;
	step_mas[7].life = 1;
	step_mas[8].life = 1;
	step_mas[9].life = 1;
	step_mas[10].life = 1;
	step_mas[11].life = 1;
	step_mas[12].life = 1;
	step_mas[13].life = 1;
	step_mas[14].life = 1;
	step_mas[15].life = 1;	

	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);
		x = pos.x / size;
		y = pos.y / size;
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
			window.clear();
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					if (transformareAlb == 1)
					{
						if (pos.y >= poz_mas[19].y * size && pos.y <= (poz_mas[19].y + 1) * size && pos.x >= poz_mas[19].x * size && pos.x <= (poz_mas[19].x + 1) * size)
						{
							int xx = pos.x % 100, yy = pos.y % 100;
							if (xx < 50 && yy < 50 && xx > 0 && yy > 0)
							{
								board[poz_mas[19].y][poz_mas[19].x] = TurnALB;
								transformareAlb = 0;
							}
							if (xx > 50 && xx < 100 && yy < 50 && yy > 0)
							{
								board[poz_mas[19].y][poz_mas[19].x] = ReginaALB;
								transformareAlb = 0;
							}
							if (xx > 50 && xx < 100 && yy>50 && yy < 100)
							{
								board[poz_mas[19].y][poz_mas[19].x] = CalALB;
								transformareAlb = 0;
							}
							if (xx < 50 && xx>0 && yy > 50 && y < 100)
							{
								board[poz_mas[19].y][poz_mas[19].x] = NebunALB;
								transformareAlb = 0;
							}
							if (transformareAlb == 0)
							{
								pozRegeNegru();
								int h = RegeNegruSahCheck(poz_mas[17].x, poz_mas[17].y);
								if (h == 0)
								{
									sahNegru = 1;
								}
							}
						}
					}
					if (transformareNegru == 1)
					{
						if (pos.y >= poz_mas[20].y * size && pos.y <= (poz_mas[20].y + 1) * size && pos.x >= poz_mas[20].x * size && pos.x <= (poz_mas[20].x + 1) * size)
						{
							int xx = pos.x % 100, yy = pos.y % 100;
							if (xx < 50 && yy < 50 && xx > 0 && yy > 0)
							{
								board[poz_mas[20].y][poz_mas[20].x] = TurnNEGRU1;
								transformareNegru = 0;
							}
							if (xx < 50 && yy < 50 && xx > 0 && yy > 0)
							{
								board[poz_mas[20].y][poz_mas[20].x] = TurnNEGRU2;
								transformareNegru = 0;
							}
							if (xx > 50 && xx < 100 && yy < 50 && yy > 0)
							{
								board[poz_mas[20].y][poz_mas[20].x] = ReginaNEGRU;
								transformareNegru = 0;
							}							
							if (xx > 50 && xx < 100 && yy>50 && yy < 100)
							{
								board[poz_mas[20].y][poz_mas[20].x] = CalNEGRU1;
								transformareNegru = 0;
							}
							if (xx > 50 && xx < 100 && yy>50 && yy < 100)
							{
								board[poz_mas[20].y][poz_mas[20].x] = CalNEGRU2;
								transformareNegru = 0;
							}
							if (xx < 50 && xx>0 && yy > 50 && y < 100)
							{
								board[poz_mas[20].y][poz_mas[20].x] = NebunNEGRU1;
								transformareNegru = 0;
							}
							if (xx < 50 && xx>0 && yy > 50 && y < 100)
							{
								board[poz_mas[20].y][poz_mas[20].x] = NebunNEGRU2;
								transformareNegru = 0;
							}
							if (transformareNegru == 0)
							{
								pozRegeAlb();
								int h = RegeAlbSahCheck(poz_mas[16].x, poz_mas[16].y);
								if (h == 0)
								{
									sahAlb = 1;
								}
							}
						}
					}
					if (board[y][x] != 0)
					{
						dx = pos.x - x * size;
						dy = pos.y - y * size;

						switch (board[y][x])//---------------------------------------------------------------------------------------------------------------------------------------------
						{
						case (PionNEGRU1):
							numarPiesaMutata = PionNEGRU1;
							Mutare = PionNegru;
							board[y][x] = 0;
							break;
						case (PionNEGRU2):
							numarPiesaMutata = PionNEGRU2;
							Mutare = PionNegru;
							board[y][x] = 0;
							break;
						case (PionNEGRU3):
							numarPiesaMutata = PionNEGRU3;
							Mutare = PionNegru;
							board[y][x] = 0;
							break;
						case (PionNEGRU4):
							numarPiesaMutata = PionNEGRU4;
							Mutare = PionNegru;
							board[y][x] = 0;
							break;
						case (PionNEGRU5):
							numarPiesaMutata = PionNEGRU5;
							Mutare = PionNegru;
							board[y][x] = 0;
							break;
						case (PionNEGRU6):
							numarPiesaMutata = PionNEGRU6;
							Mutare = PionNegru;
							board[y][x] = 0;
							break;
						case (PionNEGRU7):
							numarPiesaMutata = PionNEGRU7;
							Mutare = PionNegru;
							board[y][x] = 0;
							break;
						case (PionNEGRU8):
							numarPiesaMutata = PionNEGRU8;
							Mutare = PionNegru;
							board[y][x] = 0;
							break;
						}
						//---------------------------------------------------------------------------------------------------------------------------------------------
						/*if ((board[y][x] == PionNEGRU1) && mutare == 1) /// пешка
						{
							numarPiesaMutata = PionNEGRU1; //---------------------------------------------------------------------------------------------------------------------------------------------
							Mutare = PionNegru;
							board[y][x] = 0;
						}*/

						if (board[y][x] == PionALB && mutare == 0)
						{
							numarPiesaMutata = PionALB;
							Mutare = PionAlb;
							board[y][x] = 0;
						}
						if (board[y][x] == TurnNEGRU1 && mutare == 1) ///
						{
							numarPiesaMutata = TurnNEGRU1;
							Mutare = TurnNegru;
							board[y][x] = 0;

						}
						if (board[y][x] == TurnNEGRU2 && mutare == 1) ///
						{
							numarPiesaMutata = TurnNEGRU2;
							Mutare = TurnNegru;
							board[y][x] = 0;

						}
						if (board[y][x] == TurnALB && mutare == 0)
						{
							numarPiesaMutata = TurnALB;
							Mutare = TurnAlb;
							board[y][x] = 0;

						}
						if (board[y][x] == CalALB && mutare == 0)
						{
							numarPiesaMutata = CalALB;
							Mutare = CalAlb;
							board[y][x] = 0;
						}

						switch (board[y][x])
						{
						case (CalNEGRU1):
							numarPiesaMutata = CalNEGRU1;
							Mutare = CalNegru;
							board[y][x] = 0;
							break;
						case (CalNEGRU2):
							numarPiesaMutata = CalNEGRU2;
							Mutare = CalNegru;
							board[y][x] = 0;
							break;
						}
						/*if (board[y][x] == CalNEGRU1 && mutare == 1) ///
						{
							numarPiesaMutata = CalNEGRU;
							Mutare = CalNegru;
							board[y][x] = 0;
						}*/
						if (board[y][x] == NebunNEGRU1 && mutare == 1) ///
						{
							numarPiesaMutata = NebunNEGRU1;
							Mutare = NebunNegru;
							board[y][x] = 0;
						}
						if (board[y][x] == NebunNEGRU2 && mutare == 1) ///
						{
							numarPiesaMutata = NebunNEGRU2;
							Mutare = NebunNegru;
							board[y][x] = 0;
						}
						if (board[y][x] == NebunALB && mutare == 0)
						{
							numarPiesaMutata = NebunALB;
							Mutare = NebunAlb;
							board[y][x] = 0;
						}
						if (board[y][x] == ReginaALB && mutare == 0)
						{
							numarPiesaMutata = ReginaALB;
							Mutare = ReginaAlb;
							board[y][x] = 0;
						}
						if (board[y][x] == ReginaNEGRU && mutare == 1) ///
						{
							numarPiesaMutata = ReginaNEGRU;
							Mutare = ReginaNegru;
							board[y][x] = 0;
						}					
						if (board[y][x] == RegeNEGRU && mutare == 1) ///
						{
							numarPiesaMutata = RegeNEGRU;
							Mutare = RegeNegru;
							board[y][x] = 0;
						}
						if (board[y][x] == RegeALB && mutare == 0)
						{
							numarPiesaMutata = RegeALB;
							Mutare = RegeAlb;
							board[y][x] = 0;
						}
						if (board[y][x] == 0)
						{
							move = 1;
							poz_mas[18].x = x;
							poz_mas[18].y = y;
						}
					}
				}
			}
			if (e.type == Event::MouseButtonReleased)
			{
				if (e.key.code == Mouse::Left)
				{
					int ok = 2;
					if (numarPiesaMutata == PionALB && move == 1)
					{
						ok = PionA(poz_mas[18].x, poz_mas[18].y, x, y);
					}
					if ((numarPiesaMutata == PionNEGRU1 || numarPiesaMutata == PionNEGRU2 || numarPiesaMutata == PionNEGRU3 || numarPiesaMutata == PionNEGRU4 || numarPiesaMutata == PionNEGRU5 || numarPiesaMutata == PionNEGRU6 || numarPiesaMutata == PionNEGRU7 || numarPiesaMutata == PionNEGRU8) && move == 1) /// пешка //---------------------------------------------------------------------------------------------------------------------------------------------
					{
						ok = PionN(poz_mas[18].x, poz_mas[18].y, x, y);
					}
					if (numarPiesaMutata == TurnALB && move == 1)
					{
						ok = TurnA(poz_mas[18].x, poz_mas[18].y, x, y);
						if (ok == 1 && turnAlbStanga == 0 && poz_mas[18].y == 7 && poz_mas[18].x == 0)
						{
							turnAlbStanga = 1;
						}
						if (ok == 1 && turnAlbDreapta == 0 && poz_mas[18].y == 7 && poz_mas[18].x == 7)
						{
							turnAlbDreapta = 1;
						}
					}
					if (numarPiesaMutata == TurnNEGRU1 || numarPiesaMutata == TurnNEGRU2 && move == 1) ///
					{
						ok = TurnN(poz_mas[18].x, poz_mas[18].y, x, y);
						if (ok == 1 && turnNegruDreapta == 0 && poz_mas[18].y == 0 && poz_mas[18].x == 7)
						{
							turnNegruDreapta = 1;
						}
						if (ok == 1 && turnNegruStanga == 0 && poz_mas[18].y == 0 && poz_mas[18].x == 0)
						{
							turnNegruStanga = 1;
						}
					}
					if (numarPiesaMutata == NebunALB && move == 1)
					{
						ok = NebunA(poz_mas[18].x, poz_mas[18].y, x, y);
					}
					if (numarPiesaMutata == NebunNEGRU1 || numarPiesaMutata == NebunNEGRU2 && move == 1) ///
					{
						ok = NebunN(poz_mas[18].x, poz_mas[18].y, x, y);
					}
					if (numarPiesaMutata == ReginaALB && move == 1)
					{
						ok = ReginaA(poz_mas[18].x, poz_mas[18].y, x, y);
					}
					if (numarPiesaMutata == ReginaNEGRU && move == 1) ///
					{
						ok = ReginaN(poz_mas[18].x, poz_mas[18].y, x, y);
					}
					if (numarPiesaMutata == CalALB && move == 1)
					{
						ok = CalA(poz_mas[18].x, poz_mas[18].y, x, y);
					}
					if ((numarPiesaMutata == CalNEGRU1 || numarPiesaMutata == CalNEGRU2) && move == 1) ///
					{
						ok = CalN(poz_mas[18].x, poz_mas[18].y, x, y);
					}
					if (numarPiesaMutata == RegeNEGRU && move == 1) ///
					{
						ok = RegeN(poz_mas[18].x, poz_mas[18].y, x, y);
						if (ok == 1 && regeNegru == 0)
						{
							regeNegru = 1;
						}
					}
					if (numarPiesaMutata == RegeALB && move == 1)
					{
						ok = RegeA(poz_mas[18].x, poz_mas[18].y, x, y);
						if (ok == 1 && regeAlb == 0)
						{
							regeAlb = 1;
						}
					}
					if (ok == 1)
					{
						int nr = board[y][x];
						board[y][x] = numarPiesaMutata;
						if (y == 0 && numarPiesaMutata == PionALB)
						{
							transformareAlb = 1;
							poz_mas[19].x = x;
							poz_mas[19].y = y;
							board[y][x] = 0;
						}
						if (y == 7 && (numarPiesaMutata == PionNEGRU1 || numarPiesaMutata == PionNEGRU2 || numarPiesaMutata == PionNEGRU3 || numarPiesaMutata == PionNEGRU4 || numarPiesaMutata == PionNEGRU5 || numarPiesaMutata == PionNEGRU6 || numarPiesaMutata == PionNEGRU7 || numarPiesaMutata == PionNEGRU8))
						{
							transformareNegru = 1;
							poz_mas[20].x = x;
							poz_mas[20].y = y;
							board[y][x] = 0;
						}
						if (mutare == 0) // белые пошли, а черные следуют
						{
							if (sahAlb == 1)
							{
								pozRegeAlb();
								int s = RegeAlbSahCheck(poz_mas[16].x, poz_mas[16].y);
								if (s == 0)
								{
									board[poz_mas[18].y][poz_mas[18].x] = numarPiesaMutata;
									board[y][x] = nr;
								}
								else
								{
									sahAlb = 0;
									pozRegeNegru();
									int sah = RegeNegruSahCheck(poz_mas[17].x, poz_mas[17].y);
									if (sah == 0)
									{
										sahNegru = 1;
									}
									mutare = 1;
								}
							}
							else
							{
								pozRegeAlb();
								int sa = RegeAlbSahCheck(poz_mas[16].x, poz_mas[16].y);
								if (sa == 0)
								{
									board[poz_mas[18].y][poz_mas[18].x] = numarPiesaMutata;
									board[y][x] = nr;
								}
								else
								{
									pozRegeNegru();
									int sah = RegeNegruSahCheck(poz_mas[17].x, poz_mas[17].y);
									if (sah == 0)
									{
										sahNegru = 1;
									}
									mutare = 1;
								}
							}
						}						
					}
					else if (ok == 0)
					{
						board[poz_mas[18].y][poz_mas[18].x] = numarPiesaMutata;
					}
					move = 0;
				}
			}

			if (mutare == 1) {
				if (e.type == Event::MouseButtonReleased)//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
				{
					if (e.key.code == Mouse::Right)
					{
						/*
						for (int i = 0; i < Size_Board; i++)
						{
							for (int j = 0; j < Size_Board; j++)
							{
								if (board[i][j] != 0)
								{
									if (board[i][j] == PionNEGRU1)
									{
										PionNegru.setPosition(j * size, i * size);
										window.draw(PionNegru);
									}
									if (board[i][j] == PionNEGRU2)
									{
										PionNegru.setPosition(j * size, i * size);
										window.draw(PionNegru);
									}
									if (board[i][j] == PionNEGRU3)
									{
										PionNegru.setPosition(j * size, i * size);
										window.draw(PionNegru);
									}
									if (board[i][j] == PionNEGRU4)
									{
										PionNegru.setPosition(j * size, i * size);
										window.draw(PionNegru);
									}
									if (board[i][j] == PionNEGRU5)
									{
										PionNegru.setPosition(j * size, i * size);
										window.draw(PionNegru);
									}
									if (board[i][j] == PionNEGRU6)
									{
										PionNegru.setPosition(j * size, i * size);
										window.draw(PionNegru);
									}
									if (board[i][j] == PionNEGRU7)
									{
										PionNegru.setPosition(j * size, i * size);
										window.draw(PionNegru);
									}
									if (board[i][j] == PionNEGRU8)
									{
										PionNegru.setPosition(j * size, i * size);
										window.draw(PionNegru);
									}
									if (board[i][j] == PionALB)
									{
										PionAlb.setPosition(j * size, i * size);
										window.draw(PionAlb);
									}
									if (board[i][j] == TurnNEGRU1)
									{
										TurnNegru.setPosition(j * size, i * size);
										window.draw(TurnNegru);
									}
									if (board[i][j] == TurnNEGRU2)
									{
										TurnNegru.setPosition(j * size, i * size);
										window.draw(TurnNegru);
									}
									if (board[i][j] == TurnALB)
									{
										TurnAlb.setPosition(j * size, i * size);
										window.draw(TurnAlb);
									}
									if (board[i][j] == CalALB)
									{
										CalAlb.setPosition(j * size, i * size);
										window.draw(CalAlb);
									}
									if (board[i][j] == CalNEGRU1)
									{
										CalNegru.setPosition(j * size, i * size);
										window.draw(CalNegru);
									}
									if (board[i][j] == CalNEGRU2)
									{
										CalNegru.setPosition(j * size, i * size);
										window.draw(CalNegru);
									}
									if (board[i][j] == NebunNEGRU1)
									{
										NebunNegru.setPosition(j * size, i * size);
										window.draw(NebunNegru);
									}
									if (board[i][j] == NebunNEGRU2)
									{
										NebunNegru.setPosition(j * size, i * size);
										window.draw(NebunNegru);
									}
									if (board[i][j] == NebunALB)
									{
										NebunAlb.setPosition(j * size, i * size);
										window.draw(NebunAlb);
									}
									if (board[i][j] == ReginaALB)
									{
										ReginaAlb.setPosition(j * size, i * size);
										window.draw(ReginaAlb);
									}
									if (board[i][j] == ReginaNEGRU)
									{
										ReginaNegru.setPosition(j * size, i * size);
										window.draw(ReginaNegru);
									}
									if (board[i][j] == RegeNEGRU)
									{
										RegeNegru.setPosition(j * size, i * size);
										window.draw(RegeNegru);
									}
									if (board[i][j] == RegeALB)
									{
										RegeAlb.setPosition(j * size, i * size);
										window.draw(RegeAlb);
									}
								}
							}
						}
						*/


						/*poz_mas[0] = pionNegru1
						poz_mas[1] = pionNegru2
						poz_mas[2] = pionNegru3
						poz_mas[3] = pionNegru4
						poz_mas[4] = pionNegru5
						poz_mas[5] = pionNegru6
						poz_mas[6] = pionNegru7
						poz_mas[7] = pionNegru8
						poz_mas[8] = calNegru1
						poz_mas[9] = calNegru2
						poz_mas[10] = turnNegru1
						poz_mas[11] = turnNegru2
						poz_mas[12] = nebunNegru1
						poz_mas[13] = nebunNegru2
						poz_mas[14] = reginaNegru
						poz_mas[15] = regeNegru	*/
						step_mas[0].name = PionNEGRU1;
						step_mas[1].name = PionNEGRU2;
						step_mas[2].name = PionNEGRU3;
						step_mas[3].name = PionNEGRU4;
						step_mas[4].name = PionNEGRU5;
						step_mas[5].name = PionNEGRU6;
						step_mas[6].name = PionNEGRU7;
						step_mas[7].name = PionNEGRU8;

						step_mas[8].name = CalNEGRU1;
						step_mas[9].name = CalNEGRU2;

						step_mas[10].name = TurnNEGRU1;
						step_mas[11].name = TurnNEGRU2;

						step_mas[12].name = NebunNEGRU1;
						step_mas[13].name = NebunNEGRU2;

						step_mas[14].name = ReginaNEGRU;						

						step_mas[15].name = RegeNEGRU;

						/*step_mas[0].life = 1;
						step_mas[1].life = 1;
						step_mas[2].life = 1;
						step_mas[3].life = 1;
						step_mas[4].life = 1;
						step_mas[5].life = 1;
						step_mas[6].life = 1;
						step_mas[7].life = 1;
						step_mas[8].life = 1;
						step_mas[9].life = 1;
						step_mas[10].life = 1;
						step_mas[11].life = 1;
						step_mas[12].life = 1;
						step_mas[13].life = 1;
						step_mas[14].life = 1;						
						step_mas[15].life = 1;*/

						int Step, NextStep, times = 0, p = 0, BestStep = 0, BestPoint = 0, plus = 0, z = 0, Longturn = 0, Longnebun = 0, RU = 0, LD = 0, LU = 0, RD = 0, CL = 0, Longregina = 0, ReginaRD = 0, ReginaRU = 0, ReginaLU = 0, ReginaLD = 0;

						while (CL < 16) { // Проверка жизни фигур бота

							if (board[step_mas[CL].oldy][step_mas[CL].oldx] < 0) {

								step_mas[CL].life = 0;
							}
							CL++;
						}	

						pozPionNegru();
						
						z = 0; // обнуление данных после хода черных
						while (z < 25) {
							step_mas[z].point = 0;
							step_mas[z].deistvie = 0;
							z++;
						}
						n = 0;
						// Пешки
						while (plus < 8) { // Проверка Пешек -----------------------------------------------------------------------------------------------------------

							if (step_mas[plus].life == 1) {

								if (poz_mas[plus].y == 1) // если позиция пешки начальная								
								{
									if (poz_mas[plus].y + 2 < Size_Board && board[poz_mas[plus].y + 1][poz_mas[plus].x] == 0 && board[poz_mas[plus].y + 2][poz_mas[plus].x] == 0) // ходить на 2 вперед
									{
										if (PionNegruSahCheck(poz_mas[plus].y + 2, poz_mas[plus].x) == 1) { step_mas[n].point += 1; }
										else { step_mas[n].point += 0; }
										step_mas[n].point += 3;
										step_mas[n].deistvie = 2;
									}
								}
								else if (poz_mas[plus].y + 1 < Size_Board && poz_mas[plus].y + 1 < Size_Board && board[poz_mas[plus].y + 1][poz_mas[plus].x] == 0) // в любых других случаях (обычный ход вперед на 1)
								{
									if (PionNegruSahCheck(poz_mas[plus].y + 1, poz_mas[plus].x) == 1) { step_mas[n].point += 1; }
									else { step_mas[n].point += 0; }
									step_mas[n].point += 2;
									step_mas[n].deistvie = 1;
								}
								if (poz_mas[plus].y + 1 < Size_Board && poz_mas[plus].x - 1 >= 0) {
									if (board[poz_mas[plus].y + 1][poz_mas[plus].x - 1] < 0) // бить левее 
									{
										step_mas[n].point = 10; // смотря кто там стоит кол-во баллов
										step_mas[n].deistvie = 3;
									}
								}
								if (poz_mas[plus].y + 1 < Size_Board && poz_mas[plus].x + 1 < Size_Board) {
									if (board[poz_mas[plus].y + 1][poz_mas[plus].x + 1] < 0) // бить правее
									{
										times = 15; /// смотря кто там стоит кол-во баллов
										if (step_mas[n].point < times) {
											step_mas[n].point = times;
											step_mas[n].deistvie = 4;
										}
									}
								}
							}
							n++;
							plus++;
						}
						plus = 8;	
						// Кони
						while (plus < 10) { // Проверка Коней ----------------------------------------------------------------------------------------------------------
							if (step_mas[plus].life == 1) {
								//CalNStap12(poz_mas[8].x, poz_mas[8].y); // детект ходов коня
								int oy = poz_mas[plus].y, ox = poz_mas[plus].x;
								times = 0;
								if (oy - 2 >= 0 && ox - 1 >= 0 && board[oy - 2][ox - 1] <= 0) // самый верхний левый (2 вверх, 1 налево)
								{
									times = 1;
									if (PionNegruSahCheck(poz_mas[plus].y - 2, poz_mas[plus].x - 1) == 1) { step_mas[n].point += 1; }
									else { step_mas[n].point -= 1; }
									if (board[oy - 2][ox - 1] < 0) { step_mas[n].point += 10; }
									if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 1; }
									//step_mas[n].deistvie = 1;
								}
								if (oy - 2 >= 0 && ox + 1 < Size_Board && board[oy - 2][ox + 1] <= 0) // самый верхний правый (2 вверх, 1 направо)
								{
									times = 1;
									if (PionNegruSahCheck(poz_mas[plus].y - 2, poz_mas[plus].x + 1) == 1) { times += 1; }
									else { times -= 1; }
									if (board[oy - 2][ox + 1] < 0) { times += 10; }
									if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 2; }
									//step_mas[n].deistvie = 2;
								}
								if (oy - 1 >= 0 && ox + 2 < Size_Board && board[oy - 1][ox + 2] <= 0) // вправа немного выше (1 вверх, 2 вправо)
								{
									times = 1;
									if (PionNegruSahCheck(poz_mas[plus].y - 1, poz_mas[plus].x + 2) == 1) { times += 1; }
									else { times -= 1; }
									if (board[oy - 1][ox + 2] < 0) { times += 10; }
									if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 3; }
									//step_mas[n].deistvie = 3;
								}
								if (oy + 1 < Size_Board && ox + 2 < Size_Board && board[oy + 1][ox + 2] <= 0) // вправа немного ниже (1 вниз, 2 вправо)
								{
									times = 1;
									if (PionNegruSahCheck(poz_mas[plus].y + 1, poz_mas[plus].x + 2) == 1) { times += 1; }
									else { times -= 1; }
									if (board[oy + 1][ox + 2] < 0) { times += 10; }
									if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 4; }
									//step_mas[n].deistvie = 4;
								}
								if (oy + 2 < Size_Board && ox + 1 < Size_Board && board[oy + 2][ox + 1] <= 0) // самый нижниий правый (2 вниз, 1 вправо)
								{
									times = 1;
									if (PionNegruSahCheck(poz_mas[plus].y + 2, poz_mas[plus].x + 1) == 1) { times += 1; }
									else { times -= 1; }
									if (board[oy + 2][ox + 1] < 0) { times += 10; }
									if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 5; }
									//step_mas[n].deistvie = 5;
								}
								if (oy + 2 < Size_Board && ox - 1 >= 0 && board[oy + 2][ox - 1] <= 0) // самый нижниий левый (2 вниз, 1 влево)
								{
									times = 1;
									if (PionNegruSahCheck(poz_mas[plus].y + 2, poz_mas[plus].x - 1) == 1) { times += 1; }
									else { times -= 1; }
									if (board[oy + 2][ox - 1] < 0) { times += 10; }
									if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 6; }
									//step_mas[n].deistvie = 6;
								}
								if (oy + 1 < Size_Board && ox - 2 >= 0 && board[oy + 1][ox - 2] <= 0) // влево немного ниже (1 вниз, 2 влево)
								{
									times = 1;
									if (PionNegruSahCheck(poz_mas[plus].y + 1, poz_mas[plus].x - 2) == 1) { times += 1; }
									else { times -= 1; }
									if (board[oy + 1][ox - 2] < 0) { times += 10; }
									if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 7; }
									//step_mas[n].deistvie = 7;
								}
								if (oy - 1 >= 0 && ox - 2 >= 0 && board[oy - 1][ox - 2] <= 0) // влево немного выше (1 вверх, 2 влево)
								{
									times = 1;
									if (PionNegruSahCheck(poz_mas[plus].y - 1, poz_mas[plus].x - 2) == 1) { times += 1; }
									else { times -= 1; }
									if (board[oy - 1][ox - 2] < 0) { times += 10; }
									if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 8; }
									//step_mas[n].deistvie = 8;
								}
							}
							n++;
							plus++;
						}
						plus = 10;
						// Ладьи
						while (plus < 12) {
							if (step_mas[plus].life == 1) {
								int oy = poz_mas[plus].y, ox = poz_mas[plus].x;
								times = 0;
								for (int i = ox - 1; i >= 0; i--) // движение влево
								{
									if (board[oy][i] == 0)
									{
										step_mas[n].point += 1; // +1 за обычный ход на 1
										step_mas[n].deistvie = 1;
										Longturn = i;
									}
									else if (board[oy][i] < 0) {

										step_mas[n].point += 10; // +10 за битье врага
										step_mas[n].deistvie = 1;
										Longturn = i;
										break;
									}
									else if (board[oy][i] != 0)
									{
										break;
									}
								}
								times = 0;
								for (int i = oy - 1; i >= 0; i--) // движение вверх
								{
									if (board[i][ox] == 0)
									{
										times += 1; // +1 за обычный ход на 1
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 2; Longturn = i; }
									}
									else if (board[i][ox] < 0) {

										times += 10; // +10 за битье врага
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 2; Longturn = i; }
										break;
									}
									else if (board[i][ox] != 0)
									{
										break;
									}
								}
								times = 0;
								for (int i = ox + 1; i <= 7; i++) // движение вправо
								{
									if (board[oy][i] == 0)
									{
										times += 1; // +1 за обычный ход на 1
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 3; Longturn = i; }
									}
									else if (board[oy][i] < 0) {

										times += 10; // +10 за битье врага
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 3; Longturn = i; }
										break;
									}
									else if (board[oy][i] != 0)
									{
										break;
									}
								}
								times = 0;
								for (int i = oy + 1; i <= 7; i++) // движение вниз
								{
									if (board[i][ox] == 0)
									{
										times += 1; // +1 за обычный ход на 1
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 4; Longturn = i; }
									}
									else if (board[i][ox] < 0) {

										times += 10; // +10 за битье врага
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 4; Longturn = i; }
										break;
									}
									else if (board[i][ox] != 0)
									{
										break;
									}
								}
							}
							n++;
							plus++;
						}
						plus = 12;
						// Слоны
						while (plus < 14) {
							if (step_mas[plus].life == 1) {
								times = 0;
								int j = poz_mas[plus].x - 1;

								for (int i = poz_mas[plus].y - 1; i >= 0; i--) // влево вверх (действие 1)
								{
									if (j >= 0) {

										if (board[i][j] < 0) {

											times += 1; // +10 за битье врага									
											if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 1; Longnebun = i; LU = j; }
											break;
										}
										if (board[i][j] == 0)
										{
											times += 1; // +1 за обычный ход на 1
											if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 1; Longnebun = i; LU = j; }
										}
										else if (board[i][j] != 0)
										{
											break;
										}
									}
									j--;
								}

								times = 0;
								j = poz_mas[plus].x + 1;

								for (int i = poz_mas[plus].y - 1; i >= 0; i--) // вправо вверх (действие 2)
								{
									if (j < 8) {

										if (board[i][j] < 0) {

											times += 1; // +10 за битье врага
											if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 2; Longnebun = i; RU = j; }
											break;
										}
										if (board[i][j] == 0)
										{
											times += 1; // +1 за обычный ход на 1
											if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 2; Longnebun = i; RU = j; }
										}
										else if (board[i][j] != 0)
										{
											break;
										}
									}
									j++;
								}

								times = 0;
								j = poz_mas[plus].x - 1;

								for (int i = poz_mas[plus].y + 1; i <= 7; i++) // влево вниз (действие 3)
								{
									if (j >= 0) {

										if (board[i][j] < 0) {

											times += 1; // +10 за битье врага									
											if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 3; Longnebun = i; LD = j; }
											break;
										}
										if (board[i][j] == 0)
										{
											times += 1; // +1 за обычный ход на 1									
											if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 3; Longnebun = i; LD = j; }
										}
										else if (board[i][j] != 0)
										{
											break;
										}
									}
									j--;
								}

								times = 0;
								j = poz_mas[plus].x + 1;

								for (int i = poz_mas[plus].y + 1; i <= 7; i++)  // вправо вниз (действие 4)
								{
									if (j < 8) {

										if (board[i][j] < 0) {

											times += 1; // +10 за битье врага
											if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 4; Longnebun = i; RD = j; }
											break;
										}
										if (board[i][j] == 0)
										{
											times += 1; // +1 за обычный ход на 1
											if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 4; Longnebun = i; RD = j; }
										}
										else if (board[i][j] != 0)
										{
											break;
										}
									}
									j++;
								}
							}
							n++;
							plus++;
						}
						plus = 14;
						// Ферзь
						while (plus < 15) {
							if (step_mas[plus].life == 1) {
								times = 0;
								for (int i = poz_mas[plus].x - 1; i >= 0; i--) // движение влево
								{
									if (board[poz_mas[plus].y][i] < 0)  // действие 1 bite
									{
										times = 20; // +20 за битье врага			
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 1; Longregina = i; }
										break;
									}
									if (board[poz_mas[plus].y][i] == 0) // движение влево
									{
										times += 1; // +1 за обычный ход на 1									
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 1; Longregina = i; }
									}
									else if (board[poz_mas[plus].y][i] != 0)
									{
										break;
									}
								}
								times = 0;
								for (int i = poz_mas[plus].y - 1; i >= 0; i--) // движение вверх
								{
									if (board[i][poz_mas[plus].x] < 0) // действие 2 bite
									{
										times = 20; // +20 за битье врага			
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 2; Longregina = i; }
										break;
									}
									if (board[i][poz_mas[plus].x] == 0) // движение вверх
									{
										times += 1; // +1 за обычный ход на 1									
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 2; Longregina = i; }
									}
									else if (board[i][poz_mas[plus].x] != 0)
									{
										break;
									}
								}
								times = 0;
								for (int i = poz_mas[plus].x + 1; i < 8; i++) // движение вправо
								{
									if (board[poz_mas[plus].y][i] < 0)  // действие 3 bite
									{
										times = 20; // +20 за битье врага			
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 3; Longregina = i; }
										break;
									}
									if (board[poz_mas[plus].y][i] == 0) // движение вправо
									{
										times += 1; // +1 за обычный ход на 1									
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 3; Longregina = i; }
									}
									else if (board[poz_mas[plus].y][i] != 0)
									{
										break;
									}
								}
								times = 0;
								for (int i = poz_mas[plus].y + 1; i < 8; i++) // движение вниз
								{
									if (board[i][poz_mas[plus].x] < 0)  // действие 4 bite
									{
										times = 20; // +20 за битье врага			
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 4; Longregina = i; }
										break;
									}
									if (board[i][poz_mas[plus].x] == 0)  // движение вниз
									{
										times += 1; // +1 за обычный ход на 1									
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 4; Longregina = i; }
									}
									else if (board[i][poz_mas[plus].x] != 0)
									{
										break;
									}
								}
								times = 0;
								int j = poz_mas[plus].x - 1;
								for (int i = poz_mas[plus].y - 1; i >= 0; i--) // движение влево вверх
								{
									if (j >= 0) {

										if (board[i][j] < 0) // действие 5 bite
										{
											times = 20; // +20 за битье врага			
											if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 5; Longregina = i; ReginaLU = j; }
											break;
										}
										if (board[i][j] == 0)  // движение влево вверх
										{
											times += 1; // +1 за обычный ход на 1									
											if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 5; Longregina = i; ReginaLU = j; }
										}
										else if (board[i][j] != 0)
										{
											break;
										}
									}
									j--;
								}
								times = 0;
								j = poz_mas[plus].x + 1;
								for (int i = poz_mas[plus].y - 1; i >= 0; i--) // движение вправо вверх
								{
									if (j < 8) {

										if (board[i][j] < 0)  // действие 6 bite
										{
											times = 20; // +20 за битье врага			
											if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 6; Longregina = i; ReginaRU = j; }
											break;
										}
										if (board[i][j] == 0)  // движение вправо вверх
										{
											times += 1; // +1 за обычный ход на 1									
											if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 6; Longregina = i; ReginaRU = j; }
										}
										else if (board[i][j] != 0)
										{
											break;
										}
									}
									j++;
								}
								times = 0;
								j = poz_mas[plus].x - 1;
								for (int i = poz_mas[plus].y + 1; i < 8; i++) // движение влево вниз
								{
									if (j >= 0) {

										if (board[i][j] < 0) // действие 7 bite
										{
											times = 20; // +20 за битье врага			
											if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 7; Longregina = i; ReginaLD = j; }
											break;
										}
										if (board[i][j] == 0) // движение влево вниз
										{
											times += 1; // +1 за обычный ход на 1									
											if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 7; Longregina = i; ReginaLD = j; }
										}
										else if (board[i][j] != 0)
										{
											break;
										}
									}
									j--;
								}
								times = 0;
								j = poz_mas[plus].x + 1;
								for (int i = poz_mas[plus].y + 1; i < 8; i++)  // движение вправо вниз
								{
									if (j < 8) {

										if (board[i][j] < 0) // действие 8 bite
										{
											times = 20; // +20 за битье врага			
											if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 8; Longregina = i; ReginaRD = j; }
											break;
										}
										if (board[i][j] == 0) // движение вправо вниз
										{
											times += 1; // +1 за обычный ход на 1									
											if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 8; Longregina = i; ReginaRD = j; }
										}
										else if (board[i][j] != 0)
										{
											break;
										}
									}
									j++;
								}
							}
							n++;
							plus++;
						}						
						plus = 15;
						// Король
						while (plus < 16) {

							if (step_mas[plus].life == 1) {

								times = 0;
								if (poz_mas[plus].x - 1 >= 0 && poz_mas[plus].y - 1 >= 0 && board[poz_mas[plus].y - 1][poz_mas[plus].x - 1] <= 0) // влево вверх (действие 1)
								{
									if (board[poz_mas[plus].y - 1][poz_mas[plus].x - 1] < 0) {

										times += 10; // +10 за битье врага									
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 1; }
									}
									if (board[poz_mas[plus].y - 1][poz_mas[plus].x - 1] == 0) {

										times += 1; // +1 за обычный ход на 1
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 1; }
									}
								}
								times = 0;
								if (poz_mas[plus].y - 1 >= 0 && board[poz_mas[plus].y - 1][poz_mas[plus].x] <= 0) // вверх (действие 2)
								{
									if (board[poz_mas[plus].y - 1][poz_mas[plus].x] < 0) {

										times += 10; // +10 за битье врага									
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 2; }
									}
									if (board[poz_mas[plus].y - 1][poz_mas[plus].x] == 0) {

										times += 1; // +1 за обычный ход на 1
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 2; }
									}
								}
								times = 0;
								if (poz_mas[plus].y - 1 >= 0 && poz_mas[plus].x + 1 < Size_Board && board[poz_mas[plus].y - 1][poz_mas[plus].x + 1] <= 0) // вправо вверх (действие 3)
								{
									if (board[poz_mas[plus].y - 1][poz_mas[plus].x + 1] < 0) {

										times += 10; // +10 за битье врага									
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 3; }
									}
									if (board[poz_mas[plus].y - 1][poz_mas[plus].x + 1] == 0) {

										times += 1; // +1 за обычный ход на 1
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 3; }
									}
								}
								times = 0;
								if (poz_mas[plus].x + 1 < Size_Board && board[poz_mas[plus].y][poz_mas[plus].x + 1] <= 0) // вправо (действие 4)
								{
									if (board[poz_mas[plus].y][poz_mas[plus].x + 1] < 0) {

										times += 10; // +10 за битье врага									
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 4; }
									}
									if (board[poz_mas[plus].y][poz_mas[plus].x + 1] == 0) {

										times += 1; // +1 за обычный ход на 1
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 4; }
									}
								}
								times = 0;
								if (poz_mas[plus].x + 1 < Size_Board && poz_mas[plus].y + 1 < Size_Board && board[poz_mas[plus].y + 1][poz_mas[plus].x + 1] <= 0) // вправо вниз (действие 5)
								{
									if (board[poz_mas[plus].y + 1][poz_mas[plus].x + 1] < 0) {

										times += 10; // +10 за битье врага									
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 5; }
									}
									if (board[poz_mas[plus].y + 1][poz_mas[plus].x + 1] == 0) {

										times += 1; // +1 за обычный ход на 1
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 5; }
									}
								}
								times = 0;
								if (poz_mas[plus].y + 1 < Size_Board && board[poz_mas[plus].y + 1][poz_mas[plus].x] <= 0) // вниз (действие 6)
								{
									if (board[poz_mas[plus].y + 1][poz_mas[plus].x] < 0) {

										times += 10; // +10 за битье врага									
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 6; }
									}
									if (board[poz_mas[plus].y + 1][poz_mas[plus].x] == 0) {

										times += 1; // +1 за обычный ход на 1
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 6; }
									}
								}
								times = 0;
								if (poz_mas[plus].x - 1 >= 0 && poz_mas[plus].y + 1 < Size_Board && board[poz_mas[plus].y + 1][poz_mas[plus].x - 1] <= 0) // влево вниз (действие 7)
								{
									if (board[poz_mas[plus].y + 1][poz_mas[plus].x - 1] < 0) {

										times += 10; // +10 за битье врага									
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 7; }
									}
									if (board[poz_mas[plus].y + 1][poz_mas[plus].x - 1] == 0) {

										times += 1; // +1 за обычный ход на 1
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 7; }
									}
								}
								times = 0;
								if (poz_mas[plus].x - 1 >= 0 && board[poz_mas[plus].y][poz_mas[plus].x - 1] <= 0) // влево (действие 8)
								{
									if (board[poz_mas[plus].y][poz_mas[plus].x - 1] < 0) {

										times += 10; // +10 за битье врага									
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 8; }
									}
									if (board[poz_mas[plus].y][poz_mas[plus].x - 1] == 0) {

										times += 1; // +1 за обычный ход на 1
										if (times > step_mas[n].point) { step_mas[n].point = times; step_mas[n].deistvie = 8; }
									}
								}
							}
							n++;
							plus++;
						}

						// лучший результат = ход
						n = 0, p = 0;
						BestPoint = 0;
						while (p < 20) {
							if (BestPoint < step_mas[n].point) { BestPoint = step_mas[n].point; BestStep = n; p++; n++; }
							else { p++;	n++; }
						}

						if (step_mas[BestStep].name == PionNEGRU1 || step_mas[BestStep].name == PionNEGRU2 || step_mas[BestStep].name == PionNEGRU3 || step_mas[BestStep].name == PionNEGRU4 || step_mas[BestStep].name == PionNEGRU5 || step_mas[BestStep].name == PionNEGRU6 || step_mas[BestStep].name == PionNEGRU7 || step_mas[BestStep].name == PionNEGRU8) {

							if (step_mas[BestStep].deistvie == 1) { // ход вперед на 1 

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = PionNegru;

								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[BestStep].y + 1][poz_mas[BestStep].x] = step_mas[BestStep].name;
							}
							else if (step_mas[BestStep].deistvie == 3) { // бить влево

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = PionNegru;

								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[BestStep].y + 1][poz_mas[BestStep].x - 1] = step_mas[BestStep].name;
							}
							else if (step_mas[BestStep].deistvie == 4) { // бить вправо

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = PionNegru;

								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[BestStep].y + 1][poz_mas[BestStep].x + 1] = step_mas[BestStep].name;

							}
							else if (step_mas[BestStep].deistvie == 2) { // ход вперед на 2

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = PionNegru;

								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[BestStep].y + 2][poz_mas[BestStep].x] = step_mas[BestStep].name;
							}

						}
						
						if (step_mas[BestStep].name == CalNEGRU1 || step_mas[BestStep].name == CalNEGRU2) { // действия коня ------------------------------------------------------------------------

							if (step_mas[BestStep].deistvie == 1) { // самый верхний левый (2 вверх, 1 налево)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = CalNegru;

								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[BestStep].y - 2][poz_mas[BestStep].x - 1] = step_mas[BestStep].name;
							}
							else if (step_mas[BestStep].deistvie == 2) { // самый верхний правый (2 вверх, 1 направо)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = CalNegru;

								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[BestStep].y - 2][poz_mas[BestStep].x + 1] = step_mas[BestStep].name;
							}
							else if (step_mas[BestStep].deistvie == 3) { // вправа немного выше (1 вверх, 2 вправо)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = CalNegru;

								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[BestStep].y - 1][poz_mas[BestStep].x + 2] = step_mas[BestStep].name;
							}
							else if (step_mas[BestStep].deistvie == 4) { // вправа немного ниже (1 вниз, 2 вправо)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = CalNegru;

								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[BestStep].y + 1][poz_mas[BestStep].x + 2] = step_mas[BestStep].name;
							}
							else if (step_mas[BestStep].deistvie == 5) { // самый нижниий правый (2 вниз, 1 вправо)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = CalNegru;

								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[BestStep].y + 2][poz_mas[BestStep].x + 1] = step_mas[BestStep].name;
							}
							else if (step_mas[BestStep].deistvie == 6) { // самый нижниий левый (2 вниз, 1 влево)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = CalNegru;

								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[BestStep].y + 2][poz_mas[BestStep].x - 1] = step_mas[BestStep].name;
							}
							else if (step_mas[BestStep].deistvie == 7) { // влево немного ниже (1 вниз, 2 влево)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = CalNegru;

								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[BestStep].y + 1][poz_mas[BestStep].x - 2] = step_mas[BestStep].name;
							}
							else if (step_mas[BestStep].deistvie == 8) { // влево немного выше (1 вверх, 2 влево)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = CalNegru;

								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[BestStep].y - 1][poz_mas[BestStep].x - 2] = step_mas[BestStep].name;
							}
						}

						if (step_mas[BestStep].name == TurnNEGRU1 || step_mas[BestStep].name == TurnNEGRU2) {

							if (step_mas[BestStep].deistvie == 1) {

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = TurnNegru;

								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[BestStep].y][Longturn] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 2) {

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = TurnNegru;

								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[Longturn][poz_mas[BestStep].x] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 3) {

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = TurnNegru;

								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[BestStep].y][Longturn] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 4) {

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = TurnNegru;

								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[Longturn][poz_mas[BestStep].x] = step_mas[BestStep].name;
							}
						}

						if (step_mas[BestStep].name == NebunNEGRU1 || step_mas[BestStep].name == NebunNEGRU2) {

							if (step_mas[BestStep].deistvie == 1) {  // влево вверх (действие 1)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = NebunNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[Longnebun][LU] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 2) {  // вправо вверх (действие 2)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = NebunNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[Longnebun][RU] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 3) { // влево вниз (действие 3)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = NebunNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[Longnebun][LD] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 4) { // вправо вниз (действие 4)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = NebunNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[Longnebun][RD] = step_mas[BestStep].name;
							}
						}

						if (step_mas[BestStep].name == ReginaNEGRU) {

							if (step_mas[BestStep].deistvie == 1) { // движение влево

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = ReginaNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[BestStep].y][Longregina] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 2) { // движение вверх

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = ReginaNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[Longregina][poz_mas[BestStep].x] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 3) { // движение вправо

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = ReginaNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[BestStep].y][Longregina] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 4) { // движение вниз

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = ReginaNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[Longregina][poz_mas[BestStep].x] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 5) { // движение влево вверх

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = ReginaNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[Longregina][ReginaLU] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 6) { // движение вправо вверх

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = ReginaNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[Longregina][ReginaRU] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 7) { // движение влево вниз

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = ReginaNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[Longregina][ReginaLD] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 8) { // движение вправо вниз

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = ReginaNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[Longregina][ReginaRD] = step_mas[BestStep].name;
							}
						}

						if (step_mas[BestStep].name == RegeNEGRU) {

							if (step_mas[BestStep].deistvie == 1) { // влево вверх (действие 1)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = RegeNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[15].y - 1][poz_mas[15].x - 1] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 2) { // вверх (действие 2)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = RegeNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[15].y - 1][poz_mas[15].x] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 3) { // вправо вверх (действие 3)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = RegeNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[15].y - 1][poz_mas[15].x + 1] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 4) { // вправо (действие 4)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = RegeNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[15].y][poz_mas[15].x + 1] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 5) { // вправо вниз (действие 5)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = RegeNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[15].y + 1][poz_mas[15].x + 1] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 6) { // вниз (действие 6)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = RegeNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[15].y + 1][poz_mas[15].x] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 7) { // влево вниз (действие 7)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = RegeNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[15].y + 1][poz_mas[15].x - 1] = step_mas[BestStep].name;
							}
							if (step_mas[BestStep].deistvie == 8) { // влево (действие 8)

								numarPiesaMutata = step_mas[BestStep].name;
								Mutare = RegeNegru;
								board[poz_mas[BestStep].y][poz_mas[BestStep].x] = 0;
								board[poz_mas[15].y][poz_mas[15].x - 1] = step_mas[BestStep].name;
							}
						}

						mutare = 0; // передача хода белым

						// координаты всех фигур для видимости их же боту
						for (int i = 0; i < Size_Board; i++)
						{
							for (int j = 0; j < Size_Board; j++)
							{
								if (board[i][j] == PionNEGRU1)
								{
									step_mas[0].oldy = i;
									step_mas[0].oldx = j;
								}
								if (board[i][j] == PionNEGRU2)
								{
									step_mas[1].oldy = i;
									step_mas[1].oldx = j;
								}
								if (board[i][j] == PionNEGRU3)
								{
									step_mas[2].oldy = i;
									step_mas[2].oldx = j;
								}
								if (board[i][j] == PionNEGRU4)
								{
									step_mas[3].oldy = i;
									step_mas[3].oldx = j;
								}
								if (board[i][j] == PionNEGRU5)
								{
									step_mas[4].oldy = i;
									step_mas[4].oldx = j;
								}
								if (board[i][j] == PionNEGRU6)
								{
									step_mas[5].oldy = i;
									step_mas[5].oldx = j;
								}
								if (board[i][j] == PionNEGRU7)
								{
									step_mas[6].oldy = i;
									step_mas[6].oldx = j;
								}
								if (board[i][j] == PionNEGRU8)
								{
									step_mas[7].oldy = i;
									step_mas[7].oldx = j;
								}
								if (board[i][j] == CalNEGRU1)
								{
									step_mas[8].oldy = i;
									step_mas[8].oldx = j;
								}
								if (board[i][j] == CalNEGRU2)
								{
									step_mas[9].oldy = i;
									step_mas[9].oldx = j;
								}
								if (board[i][j] == TurnNEGRU1)
								{
									step_mas[10].oldy = i;
									step_mas[10].oldx = j;
								}
								if (board[i][j] == TurnNEGRU2)
								{
									step_mas[11].oldy = i;
									step_mas[11].oldx = j;
								}
								if (board[i][j] == NebunNEGRU1)
								{
									step_mas[12].oldy = i;
									step_mas[12].oldx = j;
								}
								if (board[i][j] == NebunNEGRU2)
								{
									step_mas[13].oldy = i;
									step_mas[13].oldx = j;
								}
								if (board[i][j] == ReginaNEGRU)
								{
									step_mas[14].oldy = i;
									step_mas[14].oldx = j;
								}								
								if (board[i][j] == RegeNEGRU)
								{
									step_mas[15].oldy = i;
									step_mas[15].oldx = j;
								}
							}
						}
						
						std::cout << "poz_mas[BestStep].y = " << poz_mas[BestStep].y << std::endl;
						std::cout << "poz_mas[BestStep].x = " << poz_mas[BestStep].x << std::endl;
						pozPionNegru();
						std::cout << std::endl;
						std::cout << "poz_mas[BestStep].y = " << poz_mas[BestStep].y << std::endl;
						std::cout << "poz_mas[BestStep].x = " << poz_mas[BestStep].x << std::endl;
						std::cout << std::endl;	
						std::cout << "-------" << std::endl;
						std::cout << std::endl;
					}
				}
			}
		}
		// Отображать
		window.clear();
		window.draw(tabla);
		if (transformareAlb == 1)
		{
			TransformareALB.setPosition(poz_mas[19].x * size, poz_mas[19].y * size);
			window.draw(TransformareALB);
		}
		if (transformareNegru == 1)
		{
			TransformareNEGRU.setPosition(poz_mas[20].x * size, poz_mas[20].y * size);
			window.draw(TransformareNEGRU);
		}
		if (move == 1)
		{
			Mutare.setPosition(pos.x - dx, pos.y - dy);
			window.draw(Mutare);
		}
		for (int i = 0; i < Size_Board; i++)
		{
			for (int j = 0; j < Size_Board; j++)
			{
				if (board[i][j] != 0)
				{
					if (board[i][j] == PionNEGRU1)
					{
						PionNegru.setPosition(j* size, i* size);
						window.draw(PionNegru);
					}
					if (board[i][j] == PionNEGRU2)
					{
						PionNegru.setPosition(j* size, i* size);
						window.draw(PionNegru);
					}
					if (board[i][j] == PionNEGRU3)
					{
						PionNegru.setPosition(j* size, i* size);
						window.draw(PionNegru);
					}
					if (board[i][j] == PionNEGRU4)
					{
						PionNegru.setPosition(j* size, i* size);
						window.draw(PionNegru);
					}
					if (board[i][j] == PionNEGRU5)
					{
						PionNegru.setPosition(j * size, i * size);
						window.draw(PionNegru);
					}
					if (board[i][j] == PionNEGRU6)
					{
						PionNegru.setPosition(j * size, i * size);
						window.draw(PionNegru);
					}
					if (board[i][j] == PionNEGRU7)
					{
						PionNegru.setPosition(j * size, i * size);
						window.draw(PionNegru);
					}
					if (board[i][j] == PionNEGRU8)
					{
						PionNegru.setPosition(j * size, i * size);
						window.draw(PionNegru);
					}
					if (board[i][j] == PionALB)
					{
						PionAlb.setPosition(j * size, i * size);
						window.draw(PionAlb);
					}
					if (board[i][j] == TurnNEGRU1)
					{
						TurnNegru.setPosition(j * size, i * size);
						window.draw(TurnNegru);
					}
					if (board[i][j] == TurnNEGRU2)
					{
						TurnNegru.setPosition(j * size, i * size);
						window.draw(TurnNegru);
					}
					if (board[i][j] == TurnALB)
					{
						TurnAlb.setPosition(j * size, i * size);
						window.draw(TurnAlb);
					}
					if (board[i][j] == CalALB)
					{
						CalAlb.setPosition(j * size, i * size);
						window.draw(CalAlb);
					}
					if (board[i][j] == CalNEGRU1)
					{
						CalNegru.setPosition(j * size, i * size);
						window.draw(CalNegru);
					}
					if (board[i][j] == CalNEGRU2)
					{
						CalNegru.setPosition(j * size, i * size);
						window.draw(CalNegru);
					}
					if (board[i][j] == NebunNEGRU1)
					{
						NebunNegru.setPosition(j * size, i * size);
						window.draw(NebunNegru);
					}
					if (board[i][j] == NebunNEGRU2)
					{
						NebunNegru.setPosition(j * size, i * size);
						window.draw(NebunNegru);
					}
					if (board[i][j] == NebunALB)
					{
						NebunAlb.setPosition(j * size, i * size);
						window.draw(NebunAlb);
					}
					if (board[i][j] == ReginaALB)
					{
						ReginaAlb.setPosition(j * size, i * size);
						window.draw(ReginaAlb);
					}
					if (board[i][j] == ReginaNEGRU)
					{
						ReginaNegru.setPosition(j * size, i * size);
						window.draw(ReginaNegru);
					}					
					if (board[i][j] == RegeNEGRU)
					{
						RegeNegru.setPosition(j * size, i * size);
						window.draw(RegeNegru);
					}
					if (board[i][j] == RegeALB)
					{
						RegeAlb.setPosition(j * size, i * size);
						window.draw(RegeAlb);
					}
				}
			}
		}
		window.display();
	}
	return 0;
}
