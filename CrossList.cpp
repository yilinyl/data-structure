#include <iostream>
using namespace std;
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

//--------稀疏矩阵十字链表存储-------
typedef struct OLNode
{
	int i, j;  //行、列下标
	ElemType e;
	struct OLNode *right, *down;
}OLNode, *OLink;
typedef struct
{
	OLink *rhead, *chead;   //行、列表头指针
	int mu, nu, tu;         //稀疏矩阵的行数、列数、非零元个数
}CrossList;
//////////////////////////////////////

//////////十字链表的创建////////////
Status CreateList(CrossList &A)
{
	cout << "输入稀疏矩阵的行数、列数、非零元个数" << endl;
	cin >> A.mu >> A.nu >> A.tu;   //输入稀疏矩阵的行数、列数、非零元个数
	
	int x, y, num, i, j, e;
	OLink q;
	A.rhead = new OLink[100];
	A.chead = new OLink[100];
	for (x = 0; x <= A.mu; x++)
		A.rhead[x] = NULL;
	for (y = 0; y <= A.nu; y++)
		A.chead[y] = NULL;

	cout << "输入非零元的行、列下标及元素值:" << endl;
	for (num = 0; num < A.tu; num++)
	{
		cin >> i >> j >> e;
		OLink p = new OLNode;
		p->right = NULL;
		p->down = NULL;
		if (!p) return ERROR;
		p->i = i; p->j = j; p->e = e;
		//行插入
		if (A.rhead[i] == NULL || A.rhead[i]->j > j)  //插入非零首元
		{
			p->right = A.rhead[i];
			A.rhead[i] = p;
		}
		else
		{   //根据行列下标查找插入位置，将p插入q之后
			for (q = A.rhead[i]; (q->right) && q->right->j < j; q = q->right);
			p->right = q->right;
			q->right = p;
		}
		//列插入
		if (A.chead[j] == NULL || A.chead[j]->i > i)  //插入非零首元
		{
			p->down = A.chead[j];
			A.chead[j] = p;
		}
		else
		{
			for (q = A.chead[j]; (q->down) && q->down->i < i; q = q->down);
			p->down = q->down;
			q->down = p;
		}
	}
	return OK;

}

///////矩阵加法///////
Status AddMatrix(CrossList &A, CrossList B)
{
	//实现矩阵相加：A=A+B
	if (A.mu != B.mu || A.nu != B.nu)
		return ERROR;

	OLink pa = A.rhead[1], pb = B.rhead[1], pre=NULL, p = pb;
	OLink *col = new OLink[100];
	int i = 1, j;
	for (j = 0; j <= A.nu; j++)
		col[j] = A.chead[j];
	while (i <= B.mu)
	{
		while (pb)
		{
			i = pb->i;
			if (pa == NULL || pa->j > pb->j)
			{
				//当A中不存在与B中该元素相同位置的非零元时
				p = pb;
				pb = pb->right;
				A.tu++;
				if (pre == NULL)   //插入行首
				{
					p->right = A.rhead[p->i];
					A.rhead[p->i] = p;
				}
				else              //插入前序元素之后
				{
					p->right = pa;
					pre->right = p;
				}
				pre = p;

				if (A.chead[p->j] == NULL || A.chead[p->j]->i > p->i)  //插入列首
				{
					p->down = A.chead[p->j];
					A.chead[p->j] = p;
				}
				else   //插在前序元素之后
				{
					p->down = col[p->j]->down;
					col[p->j]->down = p;
				}
				col[p->j] = p;
				if (pb == NULL) break;
			}

			if (pa && pa->j < pb->j)
			{
				pre = pa;
				pa = pa->right;
			}

			if (pa && pa->j == pb->j)
			{
				//A中存在与B中该元素同样位置的非零元
				p = pb;
				pb = pb->right;
				pa->e += p->e;
				if (pa->e == 0)
				{
					//若相加后值为0，删除A中元素
					if (pre == NULL)  //删除该行头结点
						A.rhead[p->i] = pa->right;
					else
						pre->right = pa->right;
					p = pa;
					pa = pa->right;
					if (A.chead[p->j] == p)
						A.chead[p->j] = col[p->j] = p->down;
					else
						col[p->j]->down = p->down;
					delete p;
					A.tu--;
				}
			}
		}

		i++;
		pa = A.rhead[i];
		pb = B.rhead[i];
		pre = NULL;
	}
		
	return OK;
}

///////打印////////
void PrintList(CrossList A)
{
	OLink p;
	for (int i = 1; i <= A.mu; i++)
	{
		p = A.rhead[i];
		while (p)
		{
			cout << p->i << ' ' << p->j << ' ' << p->e << endl;
			p = p->right;
		}
	}
}

/////////////////调试///////////////////
int main()
{
	CrossList A, B;
	CreateList(A);
	CreateList(B);
	AddMatrix(A, B);
	cout << "//////////Print///////////" << endl;
	PrintList(A);
	return 0;
}