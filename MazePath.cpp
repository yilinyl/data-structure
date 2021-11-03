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
	int x;   //������
	int y;   //������
	int ord; //���
	int di;  //�жϷ���
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
	//di=1,2,3,4ʱ���ֱ�λ����������(y+1)������(x+1)������(y-1)������(x-1)
	switch (di)
	{
	case 1:++y; break; //����
	case 2:++x; break; //����
	case 3:--y; break; //����
	case 4:--x; break; //����
	}
}

bool Position::Pass(int a[][N])
{
	//�ж�(x,y)�Ƿ�Ϊͨ���飨ֵΪ0��
	if (a[x][y] == 0||a[x][y] == 2||a[x][y] == 3)
		return true;
	else
		return false;
}

bool Position::operator==(Position &p)
{
	//����==
	if (x == p.x && y == p.y)
		return true;
	return false;
}
bool Position::operator!=(Position &p)
{
	//����!=
	if (x != p.x || y != p.y)
		return true;
	return false;
}

Position& Position::operator=(Position &p)
{
	//���ظ�ֵ�����=
	x = p.x;
	y = p.y;
	di = p.di;
	ord = p.ord;
	return *this;
}

void InitMaze(MazeType Map[][N], Position &start, Position &end)
{
	//�Թ��ĳ�ʼ����������㡢�յ㣩
	for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
	{
		if (Map[i][j] == 2)
		{
			start.SetPos(i, j); //�������
			start.SetDi(1);
			continue;
		}
		if (Map[i][j] == 3)
		{
			end.SetPos(i, j); //�����յ�
			continue;
		}
	}
}

Status MazePath_Stack(MazeType Map[][N])
{
	//��ջʵ���Թ�����

	std::stack<Position> Path; //��ջ�洢ͨ��Ԫ��
	Position start, end, CurPos, PastPos; int Di;

	//�Թ��ĳ�ʼ����������㡢�յ㣩
	InitMaze(Map, start, end);
	Path.push(start);
	CurPos = start;
	CurPos.NextPosition();
		do
		{
			if (CurPos.Pass(Map))
			{
				//��ǰλ�ÿ�ͨ
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
				CurPos.SuccessPrint(Map);  //�����㼣
				CurPos.SetDi(1);  //��ǰλ������һ��
				CurPos.NextPosition();
			}

			else
			{
				PastPos = Path.top();  //ջ��λ��
				if (!Path.empty() && PastPos.GetDirection() < 4)  //ջ������ջ��λ�û�����������δ̽��
				{
					Di = PastPos.GetDirection();
					PastPos.SetDi(++Di);
					CurPos = PastPos;  //��ǰλ���˻�ջ��λ��
					CurPos.NextPosition();  //��ǰλ���ƶ���ջ��λ������δ̽������
					CurPos.SetDi(1);
					Path.pop();
					Path.push(PastPos);
				}
				while (!Path.empty() && PastPos.GetDirection() == 4)  //ջ���ն�ջ��λ�����ܾ���̽��
				{
					PastPos = Path.top();
					PastPos.FailPrint(Map); //ʧ�ܱ��
					Path.pop();
					PastPos = Path.top();
				}
			}
		} while (!Path.empty()); //ջ����
		return FALSE;
}

Status MazePath_Queue(MazeType Map[][N])
{
	//�ö���ʵ���Թ�����
	std::queue<Position> Path;
	MazeType data[N][N] = {0};
	Position start, end, CurPos, Front, Pos;
	int x, y, step = 1; bool flag = false;
	
	InitMaze(Map, start, end);   //�Թ��ĳ�ʼ��
	start.SetDi(1);
	start.SetOrd(1);
	Path.push(start);  
	CurPos = start;
	while (!Path.empty())   //���в�Ϊ��
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
				CurPos.FootPrint(Map);  //�����㼣
				CurPos.SetOrd(++step);
				Path.push(CurPos);    //��ͨλ�����
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
		data[x][y] = Front.GetOrd();  //������Ԫ�ص���Ŵ�����Ӧλ��
		Path.pop();
	}
	if (flag)
	{
		//�������·��
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
	//��ӡ�Թ�
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			switch (Map[i][j])
			{
			case 0:cout << "  "; break;
			case 1:cout << "##"; break;
			case 2:cout << " A"; break;    //���
			case 3:cout << " B"; break;    //�յ�
			case MARK:cout << " `"; break; //����·��
			case FAIL:cout << "XX"; break; //ʧ�ܱ��
			case MARK_OK:cout << " v"; break;
			}
		}
		cout << endl;
	}

}