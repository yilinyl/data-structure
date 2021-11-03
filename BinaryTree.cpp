#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0

typedef char TElemType;
typedef int Status;

//-----��������洢��ʾ-----//
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode *lchild, *rchild;  //������Ůָ��
}BiTNode, *BiTree;
///////////////////////////////

Status CreateBiTree(BiTree &T)
{
	//��ǰ��˳������������
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
	//ǰ�������������ͬʱ���������ڲ��
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
	//�ݹ�ʵ��----ͳ�ƶ������ж�Ϊ0�Ľ����
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
	cout << "��ǰ�����������������㣺" << endl;
	CreateBiTree(T);
	cout << "���������<���>���£�" << endl;
	PreOrderTraverse(T, PrintElement);
	cout << endl;
	int c= CountLeaf(T);
	cout << "��Ϊ0�Ľ�����Ϊ��" << c << endl;
	return 0;
}