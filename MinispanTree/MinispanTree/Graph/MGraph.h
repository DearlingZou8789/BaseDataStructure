#ifndef MinispanTree_GraphAdjList_h
#define MinispanTree_GraphAdjList_h
/*图表的邻接矩阵*/

#include <stdio.h>
#include "GraphType.h"


typedef struct {
    VertexType vexs[MAXVEX];	/*顶点表*/
	EdgeType arc[MAXVEX][MAXVEX];	/*邻接矩阵，可这看作表*/
	int numVertexes,numEdges;	/*图中当前的顶点树和边数*/
}MGraph;

void CreateMGraph(MGraph *G);   //创建图的邻接矩阵数据结构

/*邻接矩阵的深度优先递归算法*/
void DFSMGraph(MGraph *G,int i);

//邻接矩阵的深度遍历操作
void DFSMGraphTraverse(MGraph *G);


#endif