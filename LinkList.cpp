#include <iostream>
using namespace std;

#define TRUE 1
#define False 0
#define OK 1
#define ERROR 0
#define N 10

typedef int Status;
typedef int ElemType;

//-------������洢�ṹ����-------

typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

void CreateList_L(LinkList &L);
void CreateRandList_L(LinkList &L,int n);
void InsertNode(LinkList &L, ElemType e);
//void CreateListTail(LinkList &L, ElemType a[]);
void PrintList_L(LinkList L);
void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc);
void MergeList1(LinkList &La, LinkList &Lb, LinkList &Lc);

int main()
{
	LinkList a, b, c;
	a = new LNode;
	a->next = NULL;
	b = new LNode;
	b->next = NULL;
	for (int i = 1; i <= 6; ++i)
		InsertNode(a, i);
	for (int j = 2; j <= 8; j += 2)
		InsertNode(b, j);
	MergeList1(a, b, c);
	PrintList_L(a);
	PrintList_L(b);
	PrintList_L(c);
	return 0;
}

//β���뷨����������Ԫ�������û����룩
void CreateList_L(LinkList &L)
{
	LinkList p, q;
	ElemType info;
	L = new LNode;
	L->next = NULL;
	q = L;
	q->next = NULL;
	while (cin >> info)   //��������������룬��Ctrl+z��ֹ
	{
		p = new LNode;
		p->next = NULL;
		p->data = info;
		q->next = p;
		q = p;
		q->next = NULL;
	}
}


//β���뷨���ɵ�����Ԫ���������������
void CreateRandList_L(LinkList &L, int n)
{
	LinkList p, q;
	L = new LNode;
	L->next = NULL;
	q = L;
	for (int i = n; i > 0; i--)
	{
		p = new LNode;
		p->data = rand() % 10;
		q->next = p;
		q = p;
		q->next = NULL;
	}

}

void InsertNode(LinkList &L, ElemType e)
{
	LinkList p;
	p = new LNode;
	p->next = NULL;
	p->data = e;
	p->next = L->next;
	L->next = p;
}

//void CreateListTail(LinkList &L, ElemType a[])
//{
//	LinkList p, q;
//	ElemType *s = a;
//	L = new LNode;
//	L->next = NULL;
//	q = L;
//	while (*s)
//	{
//		p = new LNode;
//		p->next = NULL;
//		p->data = *s;
//
//	}
//}

//��ӡ������˳��
void PrintList_L(LinkList L)
{
	LinkList p;
	p = L->next;
	while (p)
	{
		cout << p->data << ' ';
		p = p->next;
	}
	cout << endl;
}

//�ϲ��ǵݼ�������������ͬԪ�ر�����
void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc)
{
	LinkList pa, pb, pc;
	pa = La->next;
	pb = Lb->next;
	pc = Lc = La;
	while (pa && pb)
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;
	delete pb;
}

void MergeList1(LinkList &La, LinkList &Lb, LinkList &Lc)
{
	LinkList pa, pb, pc;
	pa = La->next;
	pb = Lb->next;
	pc = Lc = La;
	while (pa && pb)
	{
		if (pa->data < pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else if (pa->data > pb->data)
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
		else
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;
	delete pb;
}