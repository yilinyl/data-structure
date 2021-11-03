#include <iostream>
using namespace std;

#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
#define MAX_EDGE_NUM 50
#define OK 1
#define ERROR 0
#define OVERFLOW -1

typedef int Status;
typedef int VRType;      //�����ϵ������ͼ0��1������ͼΪȨֵ
typedef int InfoType;    //��������
typedef int VertexType;  //��������
typedef enum{DG, DN, UDG, UDN}GraphKind;   //{����ͼ��������������ͼ��������}

///////////ͼ���ڽӾ���洢�ṹ///////////
typedef struct ArcCell
{
	VRType adj;
	InfoType *info;  //�û���������Ϣ
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{
	VertexType vex[MAX_VERTEX_NUM];  //��������
	AdjMatrix arcs;        //�ڽӾ���
	int vexnum, arcnum;    //������������
	GraphKind kind;        //ͼ������
}MGraph;



Status LocateVex(MGraph G, VertexType v)
{
	//��ͼ�в��Ҷ���v��λ��
	for (int i = 0; i < G.vexnum; i++)
	if (G.vex[i] == v) return i;
	return OVERFLOW;
}

Status CreateUDN(MGraph &G)
{
	//����������
	int IncInfo, i, j, k;
	VertexType v1, v2; InfoType w;
	G.kind = UDN;
	cout << "�����������Ķ�����������������������Ϣ��0Ϊû��������Ϣ��" << endl;
	cin >> G.vexnum >> G.arcnum >> IncInfo;  //���붥������������IncInfoΪ0����������Ϣ
	cout << "���붥�㣺" << endl;
	for (i = 0; i < G.vexnum; i++)
		cin >> G.vex[i];
	for (i = 0; i < G.vexnum; i++)
		for (j = 0; j < G.vexnum; j++)
			G.arcs[i][j].adj = INFINITY;   //�ڽӾ����ʼ��
	cout << "����������ߵ���㡢�յ㡢Ȩֵ��" << endl;
	for (k = 0; k < G.arcnum; k++)
	{
		cin >> v1 >> v2 >> w;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		if (i == OVERFLOW || j == OVERFLOW) return ERROR;
		G.arcs[j][i].adj = G.arcs[i][j].adj = w;
		if (IncInfo)
			cin >> *(G.arcs[i][j].info);
	}
	return OK;
}

Status Kruskal_MST(MGraph G)
{
	typedef struct
	{
		VertexType start, end;
		VRType w;
	}Edge;
	int parent[MAX_VERTEX_NUM],rank[MAX_VERTEX_NUM];   //�жϸ������Ƿ�����ͬ�ĸ����Ƿ���ͨ��
	
	//Kruskal�㷨�����С������
	Edge edge[MAX_EDGE_NUM];
//	VertexType firstV = G.vex[0];  //��ʼ��firstV
	int i, j, k, m, temp, countE = 0, countV = 0;
	for (i = 0; i < G.vexnum; i++) { parent[i] = -1; rank[i] = 0; };   //parent, rank�����ʼ��
	for (k = 0; k < G.arcnum; k++) edge[k].w = INFINITY;  //edge�����ʼ��
	k = 0;
	for (i = 0; i < G.vexnum; i++)   //����ͼ�����бߣ�����edge����
	{
		for (j = i; j < G.vexnum; j++)
		{
			if (G.arcs[i][j].adj != INFINITY)
			{
				k = 0;
				while (G.arcs[i][j].adj>edge[k].w) k++;
				countE++;
				for (m = countE; m>k; m--)
					edge[m] = edge[m - 1];
				edge[k].w = G.arcs[i][j].adj;  //���ߣ�vi,vj������edge[k]
				edge[k].start = G.vex[i];
				edge[k].end = G.vex[j];
			}			
		}
	}

	for (k = 0; countV < G.vexnum && k < G.arcnum; k++)
	{
		i = edge[k].start;
		j = edge[k].end;
		if (parent[i]>-1 && parent[j] > -1 && parent[i] == parent[j]) continue;
		if (parent[i] == parent[j])
		{
			parent[i] = parent[j] = i<j ? i : j;
			if (i>j) ++rank[i];
			else ++rank[j];
		}
		else
		{
			while (rank[i])
			{
				temp = i;
				i = parent[i];
				parent[temp] = parent[i];
				rank[temp] = rank[i] + 1;
			}
			while (rank[j])
			{
				temp = j;
				j = parent[j];
				parent[temp] = parent[j];
				rank[temp] = rank[j] + 1;
			}
		}
		cout << '(' << edge[k].start << ',' << edge[k].end << ')' << ' ' << edge[k].w << endl;  //�����С������
		countV++;
	}
	return OK;
}

int main()
{
	MGraph G;
	CreateUDN(G);
	Kruskal_MST(G);
	return 0;
}