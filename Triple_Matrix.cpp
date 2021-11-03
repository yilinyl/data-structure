#include <iostream>
using namespace std;

#define MAXSIZE 12500   //非零元个数最大值
#define OK 1
#define ERROR 0
#define M 3
#define N 4

typedef int ElemType;
typedef int Status;
typedef struct
{
	//定义三元组
	int i, j;    //行下标、列下标
	ElemType e;
}Triple;

typedef struct
{
	//定义三元组表(存放稀疏矩阵)
	Triple data[MAXSIZE + 1];  //data[0]未使用
	int mu, nu, tu;            //矩阵的行数、列数、非零元个数
}TSMatrix;

Status CreateTriple(TSMatrix &A, ElemType a[][N]);
void Print(TSMatrix A);
Status AddMatrix(TSMatrix &A, TSMatrix B);

int main()
{
	int a[M][N] = {
		{1,0,0,0},
		{0,2,0,0},
		{0,0,3,0}
	};
	int b[M][N] = {
		{-1,1,0,0},
		{0,1,0,0},
		{0,0,-3,0}
	};
	TSMatrix A , B;
	CreateTriple(A, a);
	CreateTriple(B, b);
	cout << "////三元组表A////" << endl;
	Print(A);
	cout << "////三元组表B////" << endl;
	Print(B);
	AddMatrix(A, B);
	cout << "A+B= " << endl;
	Print(A);
	return 0;
}

Status CreateTriple(TSMatrix &A, ElemType a[][N])
{
	//创建三元组表
	int k = 1;
	A.mu = M; A.nu = N; A.tu = 0;
	A.data[0] = { 0, 0, 0 };
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (a[i][j] != 0)
			{
				A.data[k].i = i+1;
				A.data[k].j = j+1;
				A.data[k].e = a[i][j];
				k++;
				A.tu++;
			}
		}
	}
	return OK;
}

void Print(TSMatrix A)
{
	//打印三元组表
	for (int k = 1; k <= A.tu; k++)
	{
		cout << '[' << k << "] " << A.data[k].i << ' ' << A.data[k].j << ' '<< A.data[k].e << endl;
	}
}

Status AddMatrix(TSMatrix &A, TSMatrix B)
{
	//矩阵相加A=A+B
	//前提：A、B列数对应相等
	if (A.mu != B.mu || A.nu != B.nu)
		return ERROR;

	int k, ka , kb;
	for (kb = 1; kb <= B.tu ; kb++)
	{	
		for (ka = 1; ka <= A.tu; ka++)
		{
			if (A.data[ka].i == B.data[kb].i && A.data[ka].j == B.data[kb].j)
			{
				//若A中相应位置为非零元
				A.data[ka].e += B.data[kb].e;
				if (A.data[ka].e == 0)
				{
					//删除求和后的零元
					for (k = ka; k <= A.tu; k++)
					{
						A.data[k] = A.data[k + 1];
					}
					A.tu--;
				}
				if (kb == B.tu) return OK;
				break;
			}
			
		}
		

		if (ka > A.tu)
		{
			//若A中相应位置为零元，将B中该元素插入A中
			for (k = 0; k <= A.tu; k++)
			{
				//查找插入位置
				if (A.data[k].i == B.data[kb].i)  //插入位置在A中某非零行
				{
					if (B.data[kb].j >= A.data[k].j && B.data[kb].j <= A.data[k + 1].j)
						break;
				}
				else if (B.data[kb].i > A.data[k].i && B.data[kb].i <= A.data[k + 1].i)  //插入位置在A中某零行
					break;
			}

			A.tu++;
			for (int n = A.tu; n > k+1; n--)  //将B.data[kb]插入A.data[k]之后
				A.data[n] = A.data[n - 1];
			A.data[k + 1] = B.data[kb];
		}
		
	}
	return OK;
}