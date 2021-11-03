#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0

typedef char TElemType;
typedef int Status;

//-----二叉链表存储表示-----//
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode *lchild, *rchild;  //左右子女指针
}BiTNode, *BiTree;
///////////////////////////////

Status CreateBiTree(BiTree &T)
{
	//按前序顺序建立二叉链表
	char ch[50];
	cin >> ch;
	int i = 0;
	while (ch[i])
	{
		if (ch[i] == '@')
			T = NULL;
		else
		{
			T = new BiTNode;
			if (!T) return ERROR;
			T->data = ch[i];
			CreateBiTree(T->lchild);
			CreateBiTree(T->rchild);
		}
		i++;
	}
	
	return OK;
}

Status PrintElement(TElemType e)
{
	cout << e <<' ';
	return OK;
}

Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
	//前序遍历二叉树，同时输出结点所在层次
	static int rank = 0;
	if (T)
	{
		if (Visit(T->data))
		{
			cout << '<'<<++rank<<'>'<<'\t';
			if (PreOrderTraverse(T->lchild, Visit)) 
			if (PreOrderTraverse(T->rchild, Visit))
			{
				rank--;
				return OK;
			}
			rank--;
			return ERROR;
		}			
	}
	else return OK;
}

int CountLeaf(BiTree T)
{
	//递归实现----统计二叉树中度为0的结点数
	static int count = 0;
	if (T)
	{
		CountLeaf(T->lchild);
		CountLeaf(T->rchild);
		if (T->lchild == NULL && T->rchild == NULL)
			return ++count;
	}
	return count;
}

int main()
{
	BiTree T;
	cout << "按前序依次输入二叉树结点：" << endl;
	CreateBiTree(T);
	cout << "二叉树结点<层次>如下：" << endl;
	PreOrderTraverse(T, PrintElement);
	cout << endl;
	int c= CountLeaf(T);
	cout << "度为0的结点个数为：" << c << endl;
	return 0;
}