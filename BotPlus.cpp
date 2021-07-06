#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstring>

#define LUNGIME 8
#define PionNEGRU1 11
#define PionNEGRU2 12
#define PionNEGRU3 13
#define PionNEGRU4 14
#define PionNEGRU5 15
#define PionNEGRU6 16
#define PionNEGRU7 17
#define PionNEGRU8 18

#define PionALB -1
#define TurnNEGRU 2
#define TurnALB -2
#define CalALB -3
#define CalNEGRU 3
#define NebunNEGRU 4
#define NebunALB -4
#define ReginaALB -5
#define ReginaNEGRU 5
#define RegeNEGRU 6
#define RegeALB -6
#define size_struct 15
#define step_struct 15

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
	std::string name;
	int deistvie; // 0 - ходить, 1 - бить
}step_mas[step_struct];

/*poz_mas[0] = oldPoz
poz_mas[1] = regeleAlb
poz_mas[2] = regeleNegru
poz_mas[3] = pionNegru1
poz_mas[4] = pionNegru2
poz_mas[5] = pionNegru3
poz_mas[6] = pionNegru4
poz_mas[7] = pionNegru5
poz_mas[8] = pionNegru6
poz_mas[9] = pionNegru7
poz_mas[10] = pionNegru8
poz_mas[11] = transformA
poz_mas[12] = transformN*/


int  size = 100, move = 0, x, y;
int board[8][8] =
{ 2, 3, 4, 5, 6, 4, 3, 2,
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
	if (poz_mas[0].y == 6)
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
	if (poz_mas[0].y == 1)
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
					board[0][5] = TurnNEGRU;
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
						board[0][3] = TurnNEGRU;
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
				if (board[i][j] == TurnNEGRU)
				{
					ok = TurnNSah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == CalNEGRU)
				{
					ok = CalNSah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == NebunNEGRU)
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
				poz_mas[1].x = j;
				poz_mas[1].y = i;
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
				poz_mas[2].y = i;
				poz_mas[2].x = j;
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
					return 0;
				}
			}
		}
	}
	return 1;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void pozPionNegru()//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
{
	for (int i = 0; i < LUNGIME; i++)
	{
		for (int j = 0; j < LUNGIME; j++)
		{
			if (board[i][j] == PionNEGRU1)//---------------------------------------------------------------------------------------------------------------------------------------------
			{
				poz_mas[3].y = i;
				poz_mas[3].x = j;
				/// break;
			}
			///---------------------------------------------------------------------------------------------------------------------------------------------------------------------
			if (board[i][j] == PionNEGRU2)
			{
				poz_mas[4].y = i;
				poz_mas[4].x = j;
			}
			if (board[i][j] == PionNEGRU3)
			{
				poz_mas[5].y = i;
				poz_mas[5].x = j;
			}
			if (board[i][j] == PionNEGRU4)
			{
				poz_mas[6].y = i;
				poz_mas[6].x = j;
			}
			if (board[i][j] == PionNEGRU5)
			{
				poz_mas[7].y = i;
				poz_mas[7].x = j;
			}
			if (board[i][j] == PionNEGRU6)
			{
				poz_mas[8].y = i;
				poz_mas[8].x = j;
			}
			if (board[i][j] == PionNEGRU7)
			{
				poz_mas[9].y = i;
				poz_mas[9].x = j;
			}
			if (board[i][j] == PionNEGRU8)
			{
				poz_mas[10].y = i;
				poz_mas[10].x = j;
			}
			///---------------------------------------------------------------------------------------------------------------------------------------------------------------------
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	RenderWindow window(VideoMode(800, 800), "Chess");
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
						if (pos.y >= poz_mas[11].y * size && pos.y <= (poz_mas[11].y + 1) * size && pos.x >= poz_mas[11].x * size && pos.x <= (poz_mas[11].x + 1) * size)
						{
							int xx = pos.x % 100, yy = pos.y % 100;							
							if (xx < 50 && yy < 50 && xx > 0 && yy > 0)
							{
								board[poz_mas[11].y][poz_mas[11].x] = TurnALB;
								transformareAlb = 0;
							}
							if (xx > 50 && xx < 100 && yy < 50 && yy > 0)
							{
								board[poz_mas[11].y][poz_mas[11].x] = ReginaALB;
								transformareAlb = 0;
							}
							if (xx > 50 && xx < 100 && yy>50 && yy < 100)
							{
								board[poz_mas[11].y][poz_mas[11].x] = CalALB;
								transformareAlb = 0;
							}
							if (xx < 50 && xx>0 && yy > 50 && y < 100)
							{
								board[poz_mas[11].y][poz_mas[11].x] = NebunALB;
								transformareAlb = 0;
							}
							if (transformareAlb == 0)
							{
								pozRegeNegru();
								int h = RegeNegruSahCheck(poz_mas[2].x, poz_mas[2].y);
								if (h == 0)
								{
									sahNegru = 1;
								}
							}
						}
					}
					if (transformareNegru == 1)
					{
						if (pos.y >= poz_mas[12].y * size && pos.y <= (poz_mas[12].y + 1) * size && pos.x >= poz_mas[12].x * size && pos.x <= (poz_mas[12].x + 1) * size)
						{
							int xx = pos.x % 100, yy = pos.y % 100;							
							if (xx < 50 && yy < 50 && xx > 0 && yy > 0)
							{
								board[poz_mas[12].y][poz_mas[12].x] = TurnNEGRU;
								transformareNegru = 0;
							}
							if (xx > 50 && xx < 100 && yy < 50 && yy > 0)
							{
								board[poz_mas[12].y][poz_mas[12].x] = ReginaNEGRU;
								transformareNegru = 0;
							}
							if (xx > 50 && xx < 100 && yy>50 && yy < 100)
							{
								board[poz_mas[12].y][poz_mas[12].x] = CalNEGRU;
								transformareNegru = 0;
							}
							if (xx < 50 && xx>0 && yy > 50 && y < 100)
							{
								board[poz_mas[12].y][poz_mas[12].x] = NebunNEGRU;
								transformareNegru = 0;
							}
							if (transformareNegru == 0)
							{
								pozRegeAlb();
								int h = RegeAlbSahCheck(poz_mas[1].x, poz_mas[1].y);
								if (h == 0)
								{
									sahAlb = 1;
								}
							}
						}
					}
					if (board[y][x] != 0)
					{
						dx = pos.x - x * 100;
						dy = pos.y - y * 100;

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
						if (board[y][x] == TurnNEGRU && mutare == 1) ///
						{
							numarPiesaMutata = TurnNEGRU;
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
						if (board[y][x] == CalNEGRU && mutare == 1) ///
						{
							numarPiesaMutata = CalNEGRU;
							Mutare = CalNegru;
							board[y][x] = 0;
						}
						if (board[y][x] == NebunNEGRU && mutare == 1) ///
						{
							numarPiesaMutata = NebunNEGRU;
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
							poz_mas[0].x = x;
							poz_mas[0].y = y;
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
						ok = PionA(poz_mas[0].x, poz_mas[0].y, x, y);
					}
					if ((numarPiesaMutata == PionNEGRU1 || numarPiesaMutata == PionNEGRU2 || numarPiesaMutata == PionNEGRU3 || numarPiesaMutata == PionNEGRU4 || numarPiesaMutata == PionNEGRU5 || numarPiesaMutata == PionNEGRU6 || numarPiesaMutata == PionNEGRU7 || numarPiesaMutata == PionNEGRU8) && move == 1) /// пешка //---------------------------------------------------------------------------------------------------------------------------------------------
					{
						ok = PionN(poz_mas[0].x, poz_mas[0].y, x, y);
					}
					if (numarPiesaMutata == TurnALB && move == 1)
					{
						ok = TurnA(poz_mas[0].x, poz_mas[0].y, x, y);
						if (ok == 1 && turnAlbStanga == 0 && poz_mas[0].y == 7 && poz_mas[0].x == 0)
						{
							turnAlbStanga = 1;							
						}
						if (ok == 1 && turnAlbDreapta == 0 && poz_mas[0].y == 7 && poz_mas[0].x == 7)
						{
							turnAlbDreapta = 1;							
						}
					}
					if (numarPiesaMutata == TurnNEGRU && move == 1) ///
					{
						ok = TurnN(poz_mas[0].x, poz_mas[0].y, x, y);
						if (ok == 1 && turnNegruDreapta == 0 && poz_mas[0].y == 0 && poz_mas[0].x == 7)
						{
							turnNegruDreapta = 1;							
						}
						if (ok == 1 && turnNegruStanga == 0 && poz_mas[0].y == 0 && poz_mas[0].x == 0)
						{
							turnNegruStanga = 1;							
						}
					}
					if (numarPiesaMutata == NebunALB && move == 1)
					{
						ok = NebunA(poz_mas[0].x, poz_mas[0].y, x, y);
					}
					if (numarPiesaMutata == NebunNEGRU && move == 1) ///
					{
						ok = NebunN(poz_mas[0].x, poz_mas[0].y, x, y);
					}
					if (numarPiesaMutata == ReginaALB && move == 1)
					{
						ok = ReginaA(poz_mas[0].x, poz_mas[0].y, x, y);
					}
					if (numarPiesaMutata == ReginaNEGRU && move == 1) ///
					{
						ok = ReginaN(poz_mas[0].x, poz_mas[0].y, x, y);
					}
					if (numarPiesaMutata == CalALB && move == 1)
					{
						ok = CalA(poz_mas[0].x, poz_mas[0].y, x, y);
					}
					if (numarPiesaMutata == CalNEGRU && move == 1) ///
					{
						ok = CalN(poz_mas[0].x, poz_mas[0].y, x, y);
					}
					if (numarPiesaMutata == RegeNEGRU && move == 1) ///
					{
						ok = RegeN(poz_mas[0].x, poz_mas[0].y, x, y);
						if (ok == 1 && regeNegru == 0)
						{
							regeNegru = 1;							
						}
					}
					if (numarPiesaMutata == RegeALB && move == 1)
					{
						ok = RegeA(poz_mas[0].x, poz_mas[0].y, x, y);
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
							poz_mas[11].x = x;
							poz_mas[11].y = y;
							board[y][x] = 0;
						}
						if (y == 7 && (numarPiesaMutata == PionNEGRU1 || numarPiesaMutata == PionNEGRU2 || numarPiesaMutata == PionNEGRU3 || numarPiesaMutata == PionNEGRU4 || numarPiesaMutata == PionNEGRU5 || numarPiesaMutata == PionNEGRU6 || numarPiesaMutata == PionNEGRU7 || numarPiesaMutata == PionNEGRU8))
						{
							transformareNegru = 1;
							poz_mas[12].x = x;
							poz_mas[12].y = y;
							board[y][x] = 0;
						}
						if (mutare == 0) // белые пошли, а черные следуют
						{
							if (sahAlb == 1)
							{
								pozRegeAlb();
								int s = RegeAlbSahCheck(poz_mas[1].x, poz_mas[1].y);
								if (s == 0)
								{
									board[poz_mas[0].y][poz_mas[0].x] = numarPiesaMutata;
									board[y][x] = nr;
								}
								else
								{
									sahAlb = 0;
									pozRegeNegru();
									int sah = RegeNegruSahCheck(poz_mas[2].x, poz_mas[2].y);
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
								int sa = RegeAlbSahCheck(poz_mas[1].x, poz_mas[1].y);
								if (sa == 0)
								{
									board[poz_mas[0].y][poz_mas[0].x] = numarPiesaMutata;
									board[y][x] = nr;
								}
								else
								{
									pozRegeNegru();
									int sah = RegeNegruSahCheck(poz_mas[2].x, poz_mas[2].y);
									if (sah == 0)
									{
										sahNegru = 1;
									}
									mutare = 1;
								}
							}
						}

						/*else // черные пошли, а белые пошли следом ------------------------------------------------------------------------------------------------------------------------------------
						{
							
								//PionN(oldPoz.x, oldPoz.y, x, y);
								//PionN(180, 180, 280, 180);
								//mutare = 0;
							
							if (board[y][x] == PionNEGRU && mutare == 1) /// пешка
							{
								numarPiesaMutata = PionNEGRU;
								Mutare = PionNegru;
								board[y][x] = 0;
							}

							if (numarPiesaMutata == PionNEGRU && move == 1) /// пешка
							{
								ok = PionN(oldPoz.x, oldPoz.y, x, y);
							}

							///
							if (sahNegru == 1)
							{
								pozRegeNegru();
								int s = RegeNegruSahCheck(regeleNegru.x, regeleNegru.y);
								if (s == 0)
								{
									board[oldPoz.y][oldPoz.x] = numarPiesaMutata;
									board[y][x] = nr;
								}
								else
								{
									sahNegru = 0;
									pozRegeAlb();
									int sah = RegeAlbSahCheck(regeleAlb.x, regeleAlb.y);
									if (sah == 0)
									{
										sahAlb = 1;
									}
									mutare = 0;
								}
							}
							else
							{
								pozRegeNegru();
								int sa = RegeNegruSahCheck(regeleNegru.x, regeleNegru.y);
								if (sa == 0)
								{
									board[oldPoz.y][oldPoz.x] = numarPiesaMutata;
									board[y][x] = nr;
								}
								else
								{
									pozRegeAlb();
									int sah = RegeAlbSahCheck(regeleAlb.x, regeleAlb.y);
									if (sah == 0)
									{
										sahAlb = 1;
									}
									mutare = 0;
								}
							}

							//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
						}*/
					}
					else if (ok == 0)
					{
						board[poz_mas[0].y][poz_mas[0].x] = numarPiesaMutata;
					}
					move = 0;
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Space))//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
			{	
				int Step, NextStep, Points, n = 0, times = 0, p = 0, BestStep = 0;

				//poz_mas[3] = pionNegru1
				if (board[poz_mas[3].y + 1][poz_mas[3].x] == 0) { // boar x y (можно ли походить вперед)

					step_mas[n].point = 1;
					step_mas[n].deistvie = 0;///
				}
				if (board[poz_mas[3].y + 1 < LUNGIME][poz_mas[3].x - 1 >= 0] < 0) { // есть ли кто слева

					step_mas[n].point = 10; // смотря кто там стоит кол-во баллов
					step_mas[n].deistvie = 1;///
				}
				if (board[poz_mas[3].y + 1 < LUNGIME][poz_mas[3].x + 1 < LUNGIME] < 0) { // есть ли кто справа

					times = 10; /// смотря кто там стоит кол-во баллов
					if (step_mas[n].point < times) {
						step_mas[n].point = times;
						step_mas[n].deistvie = 2;///
					}					
				}					
				step_mas[n].name = "PionNEGRU1";
				
				// лучший результат = ход
				n = 0;
				while (p < 14) { // это в самом конце после анализа всех фигур

					if (step_mas[n].point > step_mas[n + 1].point) BestStep = n;
					p++;
					n++;
				}

				if (step_mas[BestStep].name == "PionNEGRU1" || step_mas[BestStep].name == "PionNEGRU2" || step_mas[BestStep].name == "PionNEGRU3" || step_mas[BestStep].name == "PionNEGRU4" || step_mas[BestStep].name == "PionNEGRU5" || step_mas[BestStep].name == "PionNEGRU6" || step_mas[BestStep].name == "PionNEGRU7" || step_mas[BestStep].name == "PionNEGRU8") {

					switch (step_mas[BestStep].deistvie)
					{
					case (0):
						board[poz_mas[3].y][poz_mas[3].x] = 0;						
						//board[poz_mas[3].y +1][poz_mas[3].x] = 11;
						board[poz_mas[3].y + 1][poz_mas[3].x] = PionNEGRU1;
						break;

					case (1):
						board[poz_mas[3].y][poz_mas[3].x] = 0;
						board[poz_mas[3].y + 1][poz_mas[3].x - 1] = PionNEGRU1;
						break;

					case (2):
						board[poz_mas[3].y][poz_mas[3].x] = 0;
						board[poz_mas[3].y + 1][poz_mas[3].x + 1] = PionNEGRU1;
						break;					
					}
				}

				mutare = 0; // передача хода белым

				/*poz_mas[3].y = i;
				poz_mas[3].x = j;*/

				/*numarPiesaMutata = PionNEGRU1;
				Mutare = PionNegru;
				board[y][x] = 0;
				break;*/
								
				/*struct Step {
					int point;
					std::string str;
					int deistvie; // (У пешки: 0 - ход вперед, 1 - бить левее, 2 - бить правее)
				}step_mas[step_struct];*/


				/*Vector2i pos = Mouse::getPosition(window);
				x = pos.x / size;
				y = pos.y / size;

				int nr = board[y][x];

				pozPionNegru();
				int sah = PionNegruSahCheck(pionNegru.x, pionNegru.y);
				if (sah == 0)
				{
					board[oldPoz.y][oldPoz.x] = numarPiesaMutata;
					board[y][x] = nr;
				}
				else
				{
					sahAlb = 0;
					pozRegeNegru();
					int sah = RegeNegruSahCheck(regeleNegru.x, regeleNegru.y);
					if (sah == 0)
					{
						sahNegru = 1;
					}
					mutare = 1;
				}*/

				/*numarPiesaMutata = PionNEGRU1;
				board[3][4] = PionNEGRU1;
				Mutare = PionNegru;
				board[1][2] = 0;
				mutare = 0;*/

				
			}//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

		}
		// Отображать
		window.clear();
		window.draw(tabla);
		if (transformareAlb == 1)
		{
			TransformareALB.setPosition(poz_mas[11].x * size, poz_mas[11].y * size);
			window.draw(TransformareALB);
		}
		if (transformareNegru == 1)
		{
			TransformareNEGRU.setPosition(poz_mas[12].x * size, poz_mas[12].y * size);
			window.draw(TransformareNEGRU);
		}
		if (move == 1)
		{
			Mutare.setPosition(pos.x - dx, pos.y - dy);
			window.draw(Mutare);
		}
		for (int i = 0; i < LUNGIME; i++)
		{
			for (int j = 0; j < LUNGIME; j++)
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
					if (board[i][j] == TurnNEGRU)
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
					if (board[i][j] == CalNEGRU)
					{
						CalNegru.setPosition(j * size, i * size);
						window.draw(CalNegru);
					}
					if (board[i][j] == NebunNEGRU)
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
