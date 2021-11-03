#include <iostream>
#include <queue>
using namespace std;

#define TRUE 1
#define FALSE 0
#define N 15

typedef int Status;
typedef int MazeType;

typedef struct 
{
	int x;     //横坐标
	int y;     //纵坐标
	int di;    //方向
	int step;  //步数（序号）
}Position;

void InitMaze(MazeType Map[][N], Position &start, Position &end)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Map[i][j] == 2)
			{
				start.x = i;
				start.y = j;

			}
		}
	}
}