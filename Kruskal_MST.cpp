#include <iostream>
using namespace std;

#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
#define MAX_EDGE_NUM 50
#define OK 1
#define ERROR 0
#define OVERFLOW -1

typedef int Status;
typedef int VRType;      //顶点关系：无向图0或1，有向图为权值
typedef int InfoType;    //数据类型
typedef int VertexType;  //顶点名称
typedef enum{DG, DN, UDG, UDN}GraphKind;   //{有向图，有向网，无向图，无向网}

///////////图的邻接矩阵存储结构///////////
typedef struct ArcCell
{
	VRType adj;
	InfoType *info;  //该弧上其他信息
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{
	VertexType vex[MAX_VERTEX_NUM];  //顶点向量
	AdjMatrix arcs;        //邻接矩阵
	int vexnum, arcnum;    //顶点数，弧数
	GraphKind kind;        //图的类型
}MGraph;



Status LocateVex(MGraph G, VertexType v)
{
	//在图中查找顶点v的位置
	for (int i = 0; i < G.vexnum; i++)
	if (G.vex[i] == v) return i;
	return OVERFLOW;
}

Status CreateUDN(MGraph &G)
{
	//创建无向网
	int IncInfo, i, j, k;
	VertexType v1, v2; InfoType w;
	G.kind = UDN;
	cout << "输入无向网的顶点数、弧数、有无其他信息（0为没有其他信息）" << endl;
	cin >> G.vexnum >> G.arcnum >> IncInfo;  //输入顶点数、弧数，IncInfo为0则无其他信息
	cout << "输入顶点：" << endl;
	for (i = 0; i < G.vexnum; i++)
		cin >> G.vex[i];
	for (i = 0; i < G.vexnum; i++)
		for (j = 0; j < G.vexnum; j++)
			G.arcs[i][j].adj = INFINITY;   //邻接矩阵初始化
	cout << "依次输入各边的起点、终点、权值：" << endl;
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
	int parent[MAX_VERTEX_NUM],rank[MAX_VERTEX_NUM];   //判断各顶点是否有相同的根（是否连通）
	
	//Kruskal算法求解最小生成树
	Edge edge[MAX_EDGE_NUM];
//	VertexType firstV = G.vex[0];  //起始点firstV
	int i, j, k, m, temp, countE = 0, countV = 0;
	for (i = 0; i < G.vexnum; i++) { parent[i] = -1; rank[i] = 0; };   //parent, rank数组初始化
	for (k = 0; k < G.arcnum; k++) edge[k].w = INFINITY;  //edge数组初始化
	k = 0;
	for (i = 0; i < G.vexnum; i++)   //遍历图中所有边，存入edge数组
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
				edge[k].w = G.arcs[i][j].adj;  //将边（vi,vj）赋给edge[k]
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
		cout << '(' << edge[k].start << ',' << edge[k].end << ')' << ' ' << edge[k].w << endl;  //输出最小生成树
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