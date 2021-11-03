#include <iostream>
#include <stack>
#include <queue>
using namespace std;

#define TRUE 1
#define FALSE 0
#define N 15
#define MARK 4
#define FAIL 5
#define MARK_OK 6

typedef int Status;
typedef int MazeType;

class Position;
void InitMaze(MazeType Map[][N], Position &start, Position &end);
Status MazePath_Stack(MazeType Map[][N]);
Status MazePath_Queue(MazeType Map[][N]);
void PrintMaze(MazeType Map[][N]);
int main()
{
	
	int map[15][15] = { 
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1 },
	{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } 
	};
	
	cout << "------- Path Seeking -------" << endl;
	PrintMaze(map);
	MazePath_Stack(map);
	cout << endl;
	cout << "------Result_Using Stack------" << endl;
	PrintMaze(map);
	cout << endl;
	MazePath_Queue(map);
	cout << "------Result_Using Queue------" << endl;
	PrintMaze(map);
	return 0;
}

class Position
{
private:
	int x;   //横坐标
	int y;   //纵坐标
	int ord; //序号
	int di;  //判断方向
public:
	void NextPosition();
	bool Pass(int a[][N]);
	Status FootPrint(int a[][N])
	{
		a[x][y] = MARK;
		return TRUE;
	}
	Status SuccessPrint(int a[][N])
	{
		a[x][y] = MARK_OK;
		return TRUE;
	}
	Status FailPrint(int a[][N])
	{
		a[x][y] = FAIL;
		return TRUE;
	}
	int GetX(){ return x; }
	int GetY(){ return y; }
	int GetOrd(){ return ord; }
	int GetDirection(){ return di; }
	void SetX(int a){ x = a; }
	void SetY(int b){ y = b; }
	void SetDi(int d){ di = d; }
	void SetOrd(int n){ ord = n; }
	void SetPos(int a, int b)
	{
		x = a; y = b;
	}
	bool operator==(Position &p);
	bool operator!=(Position &p);
	Position& operator=(Position &p);
};

void Position::NextPosition()
{
	//di=1,2,3,4时，分别将位置坐标右移(y+1)，下移(x+1)，左移(y-1)，上移(x-1)
	switch (di)
	{
	case 1:++y; break; //右移
	case 2:++x; break; //下移
	case 3:--y; break; //左移
	case 4:--x; break; //上移
	}
}

bool Position::Pass(int a[][N])
{
	//判断(x,y)是否为通道块（值为0）
	if (a[x][y] == 0||a[x][y] == 2||a[x][y] == 3)
		return true;
	else
		return false;
}

bool Position::operator==(Position &p)
{
	//重载==
	if (x == p.x && y == p.y)
		return true;
	return false;
}
bool Position::operator!=(Position &p)
{
	//重载!=
	if (x != p.x || y != p.y)
		return true;
	return false;
}

Position& Position::operator=(Position &p)
{
	//重载赋值运算符=
	x = p.x;
	y = p.y;
	di = p.di;
	ord = p.ord;
	return *this;
}

void InitMaze(MazeType Map[][N], Position &start, Position &end)
{
	//迷宫的初始化（设置起点、终点）
	for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
	{
		if (Map[i][j] == 2)
		{
			start.SetPos(i, j); //设置起点
			start.SetDi(1);
			continue;
		}
		if (Map[i][j] == 3)
		{
			end.SetPos(i, j); //设置终点
			continue;
		}
	}
}

Status MazePath_Stack(MazeType Map[][N])
{
	//用栈实现迷宫搜索

	std::stack<Position> Path; //用栈存储通道元素
	Position start, end, CurPos, PastPos; int Di;

	//迷宫的初始化（设置起点、终点）
	InitMaze(Map, start, end);
	Path.push(start);
	CurPos = start;
	CurPos.NextPosition();
		do
		{
			if (CurPos.Pass(Map))
			{
				//当前位置可通
				if (CurPos == start && Path.size() > 1)
				{
					while (!Path.empty())
					{
						PastPos = Path.top();
						PastPos.FailPrint(Map);
						Path.pop();
					}
				}
				Path.push(CurPos);
				if (CurPos == end)
					return TRUE;
				CurPos.SuccessPrint(Map);  //留下足迹
				CurPos.SetDi(1);  //当前位置右移一步
				CurPos.NextPosition();
			}

			else
			{
				PastPos = Path.top();  //栈顶位置
				if (!Path.empty() && PastPos.GetDirection() < 4)  //栈不空且栈顶位置还有其他方向未探索
				{
					Di = PastPos.GetDirection();
					PastPos.SetDi(++Di);
					CurPos = PastPos;  //当前位置退回栈顶位置
					CurPos.NextPosition();  //当前位置移动至栈顶位置其他未探索方向
					CurPos.SetDi(1);
					Path.pop();
					Path.push(PastPos);
				}
				while (!Path.empty() && PastPos.GetDirection() == 4)  //栈不空而栈顶位置四周均已探索
				{
					PastPos = Path.top();
					PastPos.FailPrint(Map); //失败标记
					Path.pop();
					PastPos = Path.top();
				}
			}
		} while (!Path.empty()); //栈不空
		return FALSE;
}

Status MazePath_Queue(MazeType Map[][N])
{
	//用队列实现迷宫搜索
	std::queue<Position> Path;
	MazeType data[N][N] = {0};
	Position start, end, CurPos, Front, Pos;
	int x, y, step = 1; bool flag = false;
	
	InitMaze(Map, start, end);   //迷宫的初始化
	start.SetDi(1);
	start.SetOrd(1);
	Path.push(start);  
	CurPos = start;
	while (!Path.empty())   //队列不为空
	{
		Pos = Path.front();
		for (int i = 1; i <= 4; i++)
		{
			CurPos = Pos;
			step = Pos.GetOrd();
			CurPos.SetDi(i);
			CurPos.NextPosition();
			if (CurPos.Pass(Map) && CurPos != start)
			{
				CurPos.FootPrint(Map);  //留下足迹
				CurPos.SetOrd(++step);
				Path.push(CurPos);    //可通位置入队
				if (CurPos == end)
				{
					
					flag = true;
					break;
				}
			}
		}
		Front = Path.front();
		x = Front.GetX();
		y = Front.GetY();
		data[x][y] = Front.GetOrd();  //将队首元素的序号存入相应位置
		Path.pop();
	}
	if (flag)
	{
		//倒序查找路径
		x = end.GetX();
		y = end.GetY();
		CurPos = end;
		while (step>0)
		{
			if (data[x - 1][y] == step - 1)
			{
				CurPos.SetX(x - 1);
			}
			else if (data[x + 1][y] == step - 1)
			{
				CurPos.SetX(x + 1);
			}
			else if (data[x][y - 1] == step - 1)
			{
				CurPos.SetY(y-1);
			}
			else if (data[x][y + 1] == step - 1)
			{
				CurPos.SetY(y + 1);
			}
			x = CurPos.GetX();
			y = CurPos.GetY();
			if (x == 0 || y == 0)
				break;
			Map[x][y] = MARK_OK;
			step--;
		}
		Map[1][1] = 2;
		Map[13][13] = 3;
		return TRUE;
	}
	return FALSE;

}

void PrintMaze(MazeType Map[][N])
{
	//打印迷宫
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			switch (Map[i][j])
			{
			case 0:cout << "  "; break;
			case 1:cout << "##"; break;
			case 2:cout << " A"; break;    //起点
			case 3:cout << " B"; break;    //终点
			case MARK:cout << " `"; break; //生成路径
			case FAIL:cout << "XX"; break; //失败标记
			case MARK_OK:cout << " v"; break;
			}
		}
		cout << endl;
	}

}