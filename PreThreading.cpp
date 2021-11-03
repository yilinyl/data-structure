#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define MARK '@'

typedef char TElemType;
typedef int Status;

//---------二叉树的线索存储----------//
typedef enum PointerTag{Link,Thread};   //Link=0,指针；Thread=1，线索
typedef struct BiThrNode
{
	TElemType data;
	struct BiThrNode *lchild, *rchild;
	PointerTag LTag, RTag;             //左右标志
}BiThrNode, *BiThrTree;
//////////////////////////////////////
Status PreOrderCreate(BiThrTree &T)
{
	//前序建立二叉链表
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
	//前序线索化
	static BiThrNode *pre = NULL;
	if (p)
	{
		if (p->lchild == NULL)
		{
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!pre && !p->rchild)   //若根节点没有右子树
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
			PreThreading(p->lchild);  //左子树线索化
		if (p->RTag == Link)
			PreThreading(p->rchild);  //右子树线索化
	}
}

Status Print(TElemType e)
{
	cout << e << ' ';
	return OK;
}


BiThrTree PreNext(BiThrTree p)
{
	//查找前序下p的后继结点
	if (p->RTag == Link && p->LTag == Link)
		return p->lchild;
	return p->rchild;
}

Status PreTraverse(BiThrTree T, Status(*Visit) (TElemType e))
{
	//前序遍历线索二叉树
	//通过查找后继结点函数PreNext实现
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
	cout << "按照前序创建线索二叉树：" << endl;
	PreOrderCreate(T);
	PreThreading(T);             //二叉树前序线索化
	cout << "前序遍历结点顺序如下：" << endl;
	PreTraverse(T, Print);       //线索二叉树前序遍历结果
	return 0;
}