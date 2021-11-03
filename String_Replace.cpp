#include <iostream>
using namespace std;

#define OK 1
#define END 0

#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN + 1];
typedef int Status;

void get_next(SString T, int next[]);
int index_KMP(SString S, SString T, int pos);
void Replace(SString &S, SString T, SString V);
void SetStrLen(SString &S);

int main()
{
	SString s1 = "ATGATAGGAAGATAGGATATA", s2 = "TATA", s3 = "ATAT";
	SetStrLen(s1);
	SetStrLen(s2);
	SetStrLen(s3);
	cout << "/////��������ģʽ��1�Ĳ�����ģʽ��2���/////" << endl;
	cout <<"������"<< s1 << endl;
	cout << "ģʽ��1��" << s2 << endl;
	cout << "ģʽ��2��" << s3 << endl;
	Replace(s1, s2, s3);
	cout << s1 << endl;
	return 0;
}

void get_next(SString T, int next[])
{
	//��ģʽ��T��next����
	int i = 1, j = 0;
	next[1] = 0;
	while (i < T[0])
	{
		if (j == 0 || T[i] == T[j])
		{
			i++; j++;
			next[i] = j;
		}
		else
			j = next[j];
	}
}

int index_KMP(SString S, SString T, int pos)
{
	//��ģʽ��T������S����pos��ʼ��λ��
	int i = pos, j = 1;
	int next[MAXSTRLEN] = { 0 };
	get_next(T, next);
	while (i <= S[0] && j <= T[0])
	{
		if (j == 0 || S[i] == T[j])
		{
			i++; j++;
		}
		else
			j = next[j];
	}
	if (j > T[0]) return i - T[0];  //ƥ��ɹ�������������ģʽ����ʼ��ǰһλ
	return 0;
}

void Replace(SString &S, SString T, SString V)
{
	//���ַ���V�滻����S�г��ֵ�������T��ȵĲ��ص��Ӵ�
	//��V��T�������
	int start = 1, end, index;

	while (start + T[0] - 1 <= S[0])  	  
	//�ж�����ʣ�ಿ���Ƿ����ٽ���һ��ģʽƥ��
	//��ʣ�ಿ�ֳ���С��ģʽ������ֹѭ��  
	{
		index = index_KMP(S, T, start);
		if (index == 0)
			break;        //ƥ��ʧ�ܣ�ѭ����ֹ
		start = index + 1;
		end = index + T[0];
		for (int i = start; i <= end; i++)
			S[i] = V[i - index];   //��V���ַ��滻S����Ӧ�ַ�
		start = end;
	}
}

void SetStrLen(SString &S)
{
	unsigned char *ptr = S;
	int count = 0;
	while (*ptr++)
		count++;
	for (int i = count ; i > 0;i--)
		S[i] = S[i - 1];
	S[0] = count
		;
}