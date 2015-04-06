#ifndef MinispanTree_MGraph_h
#define MinispanTree_MGraph_h
/*图表的邻接矩阵*/

#include <stdio.h>
#include <stdlib.h>
#include "GraphType.h"
#include "../Queue/Queue.h"


typedef struct {
    VertexType vexs[MAXVEX];	/*顶点表*/
	EdgeType arc[MAXVEX][MAXVEX];	/*邻接矩阵，可这看作表*/
	int numVertexes,numEdges;	/*图中当前的顶点树和边数*/
}MGraph;

typedef struct{
    int begin;
    int end;
    int weight;
}Edge;  //边集结点dge结构的定义，需要将邻接矩阵转为成边集数组

/*用在最短路径中存储最短路径下标和权值的数组*/
typedef int Pathmatirx[MAXVEX];    // 用于存储最短路径下标的数组

typedef int ShortPathTable[MAXVEX]; //用于存储到各点最短路径的权值和
/***********************************/

/*用在最短路径中存储最短路径下表和权值的数组，用于弗洛伊德算法中*/
typedef int PathmatrixFloyd[MAXVEX][MAXVEX];   //用于存储最短路径下标的数组

typedef int ShortPathTableFloyd[MAXVEX][MAXVEX];//用于存储到各点最短路径的权值和
/*****************************************************/

extern void MGraphCreate(MGraph *G);   //创建图的邻接矩阵数据结构

/*邻接矩阵的深度优先递归算法*/
extern void MGraphDFS(MGraph *G,int i);

//邻接矩阵的深度遍历操作
extern void MGraphDFSTraverse(MGraph *G);

//邻接矩阵的广度遍历算法
extern void MGraphBFSTraverse(MGraph *G);

//（Prim）普里姆算法：生成最小生成树
extern void MGraphMiniSpanTree_Prim(MGraph *G);

//邻接矩阵转边集数组
extern void MGraphToEdge(MGraph *G, Edge *E[MAXEDGE]);

//Kruskal算法生成最小生成树
extern void MGraphMiniSpanTree_Kruskal(MGraph *G);

/*Dijkstra算法求最短路径，求有向图G的Vo顶点到其余顶点V最短路径P[V]及带权长度D[v]
 *P[v]的值为前驱顶点下标，D[v]表示V0到V的最短路径长度和
 */
extern void MGraphShortestPath_Dijkstra(MGraph *G, int v0,
                            Pathmatirx *P, ShortPathTable *D);

/*Floyd算法，求网图G中个顶点v到其余顶点w最短路径P[v][w]及带权长度D[v][w]*/
extern void MGraphShortestPath_Floyd(MGraph *G, PathmatrixFloyd *P,
                              ShortPathTableFloyd *D);

//利用P和D数组求得每个顶点到其他顶点的路径
extern void MGraphAllShortest(MGraph *G);


#endif