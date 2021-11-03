#include <iostream>
using namespace std;

#define MAXSIZE 20
typedef int ElemType;
typedef int KeyType;

//��̬���ұ�˳��ṹ����//
typedef struct
{
	ElemType elem[MAXSIZE];
	int length;
}SSTable;


void Fibonacci(int f[])
{
	f[0] = 1; f[1] = 1;
	for (int i = 2; i < 10; i++)
	{
		f[i] = f[i - 1] + f[i - 2];
	}
}

int FibonacciSearch(SSTable T, KeyType key)
{
	//쳲���������
	int f[10], k = 0, low = 0, high = T.length - 1, mid;
	Fibonacci(f);
	while (T.length + 1 != f[k]) k++;  //��������ұ��ȶ�Ӧ��쳲�������
	k--;
	while (low <= high)
	{
		mid = low + f[k] - 1;
		if (key == T.elem[mid]) return mid;  //���ҳɹ�
		else if (key < T.elem[mid])
		{
			high = mid - 1;
			k--;
		}
		else
		{
			low = mid + 1;
			k -= 2;
		}
	}
	return -1;   //����ʧ��
}

int main()
{
	SSTable T;
	KeyType key;
	int i, j;
	cout << "���������Ԫ�ظ�����" << endl;
	cin >> T.length;
	cout << "����������������򣩵�Ԫ�أ�" << endl;
	for (i = 0; i < T.length; i++)
		cin >> T.elem[i];
	cout << "����Ԫ�أ�" << endl;
	cin >> key;
	j = FibonacciSearch(T, key);
	if (j == -1) cout << "����ʧ��" << endl;
	else cout << key<<"Ϊ���е�"<<j<<"��Ԫ��"<< endl;
	return 0;
}