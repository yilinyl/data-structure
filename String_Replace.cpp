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
	cout << "/////将主串中模式串1的部分用模式串2替代/////" << endl;
	cout <<"主串："<< s1 << endl;
	cout << "模式串1：" << s2 << endl;
	cout << "模式串2：" << s3 << endl;
	Replace(s1, s2, s3);
	cout << s1 << endl;
	return 0;
}

void get_next(SString T, int next[])
{
	//求模式串T的next数组
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
	//求模式串T在主串S中自pos开始的位置
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
	if (j > T[0]) return i - T[0];  //匹配成功，返回主串中模式串起始的前一位
	return 0;
}

void Replace(SString &S, SString T, SString V)
{
	//用字符串V替换主串S中出现的所有与T相等的不重叠子串
	//设V与T长度相等
	int start = 1, end, index;

	while (start + T[0] - 1 <= S[0])  	  
	//判断主串剩余部分是否能再进行一次模式匹配
	//若剩余部分长度小于模式串，终止循环  
	{
		index = index_KMP(S, T, start);
		if (index == 0)
			break;        //匹配失败，循环终止
		start = index + 1;
		end = index + T[0];
		for (int i = start; i <= end; i++)
			S[i] = V[i - index];   //用V中字符替换S中相应字符
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