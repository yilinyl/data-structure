#include <iostream>
using namespace std;
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

//--------ϡ�����ʮ������洢-------
typedef struct OLNode
{
	int i, j;  //�С����±�
	ElemType e;
	struct OLNode *right, *down;
}OLNode, *OLink;
typedef struct
{
	OLink *rhead, *chead;   //�С��б�ͷָ��
	int mu, nu, tu;         //ϡ����������������������Ԫ����
}CrossList;
//////////////////////////////////////

//////////ʮ������Ĵ���////////////
Status CreateList(CrossList &A)
{
	cout << "����ϡ����������������������Ԫ����" << endl;
	cin >> A.mu >> A.nu >> A.tu;   //����ϡ����������������������Ԫ����
	
	int x, y, num, i, j, e;
	OLink q;
	A.rhead = new OLink[100];
	A.chead = new OLink[100];
	for (x = 0; x <= A.mu; x++)
		A.rhead[x] = NULL;
	for (y = 0; y <= A.nu; y++)
		A.chead[y] = NULL;

	cout << "�������Ԫ���С����±꼰Ԫ��ֵ:" << endl;
	for (num = 0; num < A.tu; num++)
	{
		cin >> i >> j >> e;
		OLink p = new OLNode;
		p->right = NULL;
		p->down = NULL;
		if (!p) return ERROR;
		p->i = i; p->j = j; p->e = e;
		//�в���
		if (A.rhead[i] == NULL || A.rhead[i]->j > j)  //���������Ԫ
		{
			p->right = A.rhead[i];
			A.rhead[i] = p;
		}
		else
		{   //���������±���Ҳ���λ�ã���p����q֮��
			for (q = A.rhead[i]; (q->right) && q->right->j < j; q = q->right);
			p->right = q->right;
			q->right = p;
		}
		//�в���
		if (A.chead[j] == NULL || A.chead[j]->i > i)  //���������Ԫ
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

///////����ӷ�///////
Status AddMatrix(CrossList &A, CrossList B)
{
	//ʵ�־�����ӣ�A=A+B
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
				//��A�в�������B�и�Ԫ����ͬλ�õķ���Ԫʱ
				p = pb;
				pb = pb->right;
				A.tu++;
				if (pre == NULL)   //��������
				{
					p->right = A.rhead[p->i];
					A.rhead[p->i] = p;
				}
				else              //����ǰ��Ԫ��֮��
				{
					p->right = pa;
					pre->right = p;
				}
				pre = p;

				if (A.chead[p->j] == NULL || A.chead[p->j]->i > p->i)  //��������
				{
					p->down = A.chead[p->j];
					A.chead[p->j] = p;
				}
				else   //����ǰ��Ԫ��֮��
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
				//A�д�����B�и�Ԫ��ͬ��λ�õķ���Ԫ
				p = pb;
				pb = pb->right;
				pa->e += p->e;
				if (pa->e == 0)
				{
					//����Ӻ�ֵΪ0��ɾ��A��Ԫ��
					if (pre == NULL)  //ɾ������ͷ���
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

///////��ӡ////////
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

/////////////////����///////////////////
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