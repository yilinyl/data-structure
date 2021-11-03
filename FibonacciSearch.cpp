#include <iostream>
using namespace std;

#define MAXSIZE 20
typedef int ElemType;
typedef int KeyType;

//静态查找表顺序结构定义//
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
	//斐波那契查找
	int f[10], k = 0, low = 0, high = T.length - 1, mid;
	Fibonacci(f);
	while (T.length + 1 != f[k]) k++;  //查找与查找表长度对应的斐波那契数
	k--;
	while (low <= high)
	{
		mid = low + f[k] - 1;
		if (key == T.elem[mid]) return mid;  //查找成功
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
	return -1;   //查找失败
}

int main()
{
	SSTable T;
	KeyType key;
	int i, j;
	cout << "输入有序表元素个数：" << endl;
	cin >> T.length;
	cout << "依次输入有序表（升序）的元素：" << endl;
	for (i = 0; i < T.length; i++)
		cin >> T.elem[i];
	cout << "查找元素：" << endl;
	cin >> key;
	j = FibonacciSearch(T, key);
	if (j == -1) cout << "查找失败" << endl;
	else cout << key<<"为表中第"<<j<<"号元素"<< endl;
	return 0;
}