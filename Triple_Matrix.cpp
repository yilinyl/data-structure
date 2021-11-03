#include <iostream>
using namespace std;

#define MAXSIZE 12500   //����Ԫ�������ֵ
#define OK 1
#define ERROR 0
#define M 3
#define N 4

typedef int ElemType;
typedef int Status;
typedef struct
{
	//������Ԫ��
	int i, j;    //���±ꡢ���±�
	ElemType e;
}Triple;

typedef struct
{
	//������Ԫ���(���ϡ�����)
	Triple data[MAXSIZE + 1];  //data[0]δʹ��
	int mu, nu, tu;            //���������������������Ԫ����
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
	cout << "////��Ԫ���A////" << endl;
	Print(A);
	cout << "////��Ԫ���B////" << endl;
	Print(B);
	AddMatrix(A, B);
	cout << "A+B= " << endl;
	Print(A);
	return 0;
}

Status CreateTriple(TSMatrix &A, ElemType a[][N])
{
	//������Ԫ���
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
	//��ӡ��Ԫ���
	for (int k = 1; k <= A.tu; k++)
	{
		cout << '[' << k << "] " << A.data[k].i << ' ' << A.data[k].j << ' '<< A.data[k].e << endl;
	}
}

Status AddMatrix(TSMatrix &A, TSMatrix B)
{
	//�������A=A+B
	//ǰ�᣺A��B������Ӧ���
	if (A.mu != B.mu || A.nu != B.nu)
		return ERROR;

	int k, ka , kb;
	for (kb = 1; kb <= B.tu ; kb++)
	{	
		for (ka = 1; ka <= A.tu; ka++)
		{
			if (A.data[ka].i == B.data[kb].i && A.data[ka].j == B.data[kb].j)
			{
				//��A����Ӧλ��Ϊ����Ԫ
				A.data[ka].e += B.data[kb].e;
				if (A.data[ka].e == 0)
				{
					//ɾ����ͺ����Ԫ
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
			//��A����Ӧλ��Ϊ��Ԫ����B�и�Ԫ�ز���A��
			for (k = 0; k <= A.tu; k++)
			{
				//���Ҳ���λ��
				if (A.data[k].i == B.data[kb].i)  //����λ����A��ĳ������
				{
					if (B.data[kb].j >= A.data[k].j && B.data[kb].j <= A.data[k + 1].j)
						break;
				}
				else if (B.data[kb].i > A.data[k].i && B.data[kb].i <= A.data[k + 1].i)  //����λ����A��ĳ����
					break;
			}

			A.tu++;
			for (int n = A.tu; n > k+1; n--)  //��B.data[kb]����A.data[k]֮��
				A.data[n] = A.data[n - 1];
			A.data[k + 1] = B.data[kb];
		}
		
	}
	return OK;
}