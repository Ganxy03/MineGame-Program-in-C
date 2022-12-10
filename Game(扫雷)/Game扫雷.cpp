#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <graphics.h>

#define ROW 15
#define COL 15
#define NUM 15
#define SIZE 30

int count = 0;
int   map[ROW + 2][COL + 2];
IMAGE img[12];

void GameInit()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			map[i][j] = 0;
		}
	}
	int n = 0;
	while (n < NUM)
	{
		srand((unsigned int)time(NULL));
		int r = rand() % ROW + 1;
		int c = rand() % COL + 1;
		if (map[r][c] == 0)
		{
			map[r][c] = -1;
			n++;
		}
	}
	for (int i = 1; i <= ROW; i++)
	{
		for (int j = 1; j <= COL; j++)
		{
			if (map[i][j] != -1)
			{
				for (int m = i - 1; m <= i + 1; m++)
				{
					for (int n = j - 1; n <= j + 1; n++)
					{
						if (map[m][n] == -1)
						{
							map[i][j]++;
						}
					}
				}
			}
		}
	}
	for (int i = 1; i <=ROW; i++)
	{
		for (int j = 1; j <=COL; j++)
		{
			map[i][j] += 20;
		}
	}
}

	/*****************************************
		ÔªËØ		Í¼Æ¬					
		0-8			Êý×Ö		+20		20-28
		-1			img[9](À×)	+20		19
		19-28		img[10]
	******************************************/

void GameDraw()
{
	for (int i = 1; i <= ROW; i++)
	{
		for (int j = 1; j <= COL; j++)
		{
			printf("%2d ", map[i][j]);
			if (map[i][j] == -1)
			{
				putimage((i - 1) * SIZE, (j - 1) * SIZE, &img[9]);
			}
			else if (map[i][j] >= 0 && map[i][j] <= 8)
			{
				putimage((i - 1) * SIZE, (j - 1) * SIZE, &img[map[i][j]]);
			}
			else if (map[i][j] >= 19 && map[i][j]<=28)
			{
				putimage((i - 1) * SIZE, (j - 1) * SIZE, &img[10]);
			}
			else if (map[i][j] > 30)
			{
				putimage((i - 1) * SIZE, (j - 1) * SIZE, &img[11]);
			}
		}
		printf("\n");
	}
}

void OpenZero(int r,int c)
{
	map[r][c] -= 20;
	count++;
	for (int m = r - 1; m <= r + 1; m++)
	{
		for (int n = c - 1; n <= c + 1; n++)
		{
			if (m >= 1 && m <= ROW && n >= 1 && n <= COL)
			{
				if (map[m][n] >= 19 && map[m][n] <= 28)
				{
					if (map[m][n] != 20)
					{
						map[m][n] -= 20;
						count++;
					}
					else
					{
						OpenZero(m, n);
					}
				}
			}
		}
	}
}

int PlayGame()
{
	MOUSEMSG msg = { 0 };
	int r, c;
	
	while (1)
	{
		
		msg = GetMouseMsg();
		switch(msg.uMsg)
		{
			
			case WM_LBUTTONDOWN:
				r = msg.x / SIZE + 1;
				c = msg.y / SIZE + 1;
				if (map[r][c] >= 19 && map[r][c] <= 28)
				{
					if (map[r][c] == 20)
					{
						OpenZero(r,c);
					}
					else
					{
						map[r][c] -= 20;
						count++;
					}
				}
				return map[r][c];
				break;
			case WM_RBUTTONDOWN:
				r = msg.x / SIZE + 1;
				c = msg.y / SIZE + 1;
				if (map[r][c] >= 19 && map[r][c] <= 28)
				{
					map[r][c] += 50;
				}
				else if (map[r][c] > 30)
				{
					map[r][c] -= 50;
				}
				return map[r][c];
				break;
		}
	}
}

int main()
{
	HWND hwnd=initgraph(ROW * SIZE, COL * SIZE, SHOWCONSOLE);
	loadimage(&img[0], L"0.jpg", SIZE, SIZE);//0
	loadimage(&img[1], L"1.jpg", SIZE, SIZE);//1
	loadimage(&img[2], L"2.jpg", SIZE, SIZE);//2
	loadimage(&img[3], L"3.jpg", SIZE, SIZE);//3
	loadimage(&img[4], L"4.jpg", SIZE, SIZE);//4
	loadimage(&img[5], L"5.jpg", SIZE, SIZE);//5
	loadimage(&img[6], L"6.jpg", SIZE, SIZE);//6
	loadimage(&img[7], L"7.jpg", SIZE, SIZE);//7
	loadimage(&img[8], L"8.jpg", SIZE, SIZE);//8
	loadimage(&img[9], L"9.jpg", SIZE, SIZE);//À×
	loadimage(&img[10], L"10.jpg", SIZE, SIZE);//¿Õ°×
	loadimage(&img[11], L"11.jpg", SIZE, SIZE);//±ê¼Ç

	GameInit();
	system("pause");
	while (1)
	{
		GameDraw();
		if (PlayGame()==-1)
		{
			GameDraw();
			MessageBox(hwnd, L"you r a low B!!", L"",MB_OK);
			break;
		}
		if (ROW * COL - NUM == count)
		{
			MessageBox(hwnd, L"you win!!", L"", MB_OK);
			break;
		}
	}
	return 0;
}
