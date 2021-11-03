#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;
typedef struct DuLNode
{
	ElemType data;
	struct DuLNode *prior;
	struct DuLNode *next;
	int freq;
}DuLNode, *DuLinkList;

void CreateList(DuLinkList &L, int n);
void PrintList(DuLinkList L);
Status Locate(DuLinkList &L, ElemType x);

int main()
{
	DuLinkList La;
	CreateList(La, 5);
	cout << "原始链表：";
	PrintList(La);
	cout << "查询 5：";
	Locate(La, 5);
	PrintList(La);
	cout << "查询 1：";
	Locate(La, 1);
	PrintList(La);
	cout << "查询 3：";
	Locate(La, 3);
	PrintList(La);
	cout << "查询 1：";
	Locate(La, 1);
	PrintList(La);
	return 0;
}

void CreateList(DuLinkList &L,int n)
{
	DuLinkList p, q;
	ElemType info;
	L = new DuLNode;
	L->next = NULL;
	L->prior = NULL;
	L->freq = 0;
	q = L;
	for (int i = n; i > 0; --i)
	{
		cin >> info;
		p = new DuLNode;
		p->next = NULL;
		p->data = info;
		p->freq = 0;
		q->next = p;
		p->prior = q;
		q = p;
	}

}
void PrintList(DuLinkList L)
{
	//顺序打印链表
	DuLinkList p;
	p = L->next;
	while (p)
	{
		cout << p->data << '(' << p->freq << ") ";
		p = p->next;
	}
	cout << endl;
}

Status Locate(DuLinkList &L, ElemType x)
{
	//查找元素值为x的结点
	DuLinkList p, q;
	p = L->next;
	while (p)
	{
		if (p->data == x)
		{
			++ p->freq;
			break;
		}
		p = p->next;
	}
	if (p)
	{
		q = p->prior;
		while (q->prior && p->freq > q->freq)
		{
			q->next = p->next;
			p->prior = q->prior;
			q->prior->next = p;
			p->next->prior = q;
			q->prior = p;
			p->next = q;
			q = p->prior;
		}
		return OK;
	}

	return ERROR;
}