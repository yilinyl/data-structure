#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define MARK '@'

typedef char TElemType;
typedef int Status;

//---------�������������洢----------//
typedef enum PointerTag{Link,Thread};   //Link=0,ָ�룻Thread=1������
typedef struct BiThrNode
{
	TElemType data;
	struct BiThrNode *lchild, *rchild;
	PointerTag LTag, RTag;             //���ұ�־
}BiThrNode, *BiThrTree;
//////////////////////////////////////
Status PreOrderCreate(BiThrTree &T)
{
	//ǰ������������
	char ch[50];
	cin >> ch;
	int i = 0;
	while (ch[i])
	{
		if (ch[i] == MARK)
			T = NULL;
		else
		{
			T = new BiThrNode;
			if (!T) return ERROR;
			T->data = ch[i];
			T->LTag = Link;
			T->RTag = Link;
			PreOrderCreate(T->lchild);
			PreOrderCreate(T->rchild);
		}
		i++;
	}
	return OK;
}
void PreThreading(BiThrTree p)
{
	//ǰ��������
	static BiThrNode *pre = NULL;
	if (p)
	{
		if (p->lchild == NULL)
		{
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!pre && !p->rchild)   //�����ڵ�û��������
		{
			p->RTag = Thread;
			p->rchild = p->lchild;
		}
		if (pre && pre->rchild == NULL)
		{
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;
		if (p->LTag == Link)
			PreThreading(p->lchild);  //������������
		if (p->RTag == Link)
			PreThreading(p->rchild);  //������������
	}
}

Status Print(TElemType e)
{
	cout << e << ' ';
	return OK;
}


BiThrTree PreNext(BiThrTree p)
{
	//����ǰ����p�ĺ�̽��
	if (p->RTag == Link && p->LTag == Link)
		return p->lchild;
	return p->rchild;
}

Status PreTraverse(BiThrTree T, Status(*Visit) (TElemType e))
{
	//ǰ���������������
	//ͨ�����Һ�̽�㺯��PreNextʵ��
	BiThrNode *p = T;
	while (p)
	{
		Visit(p->data);
		p = PreNext(p);  
	}
	return OK;
}



int main()
{
	BiThrTree T;
	cout << "����ǰ�򴴽�������������" << endl;
	PreOrderCreate(T);
	PreThreading(T);             //������ǰ��������
	cout << "ǰ��������˳�����£�" << endl;
	PreTraverse(T, Print);       //����������ǰ��������
	return 0;
}