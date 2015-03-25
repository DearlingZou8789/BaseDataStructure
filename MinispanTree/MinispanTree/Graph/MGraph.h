//#ifndef MinispanTree_GraphAdjList_h
//#define MinispanTree_GraphAdjList_h
/*图表的邻接矩阵*/
#include "GraphType.h"

typedef struct {
    VertexType vexs[MAXVEX];	/*顶点表*/
	EdgeType arc[MAXVEX][MAXVEX];	/*邻接矩阵，可这看作表*/
	int numVertexes,numEdges;	/*图中当前的顶点树和边数*/
}MGraph;

void CreateMGraph(MGraph *G){
    int i,j,k,w;
    printf("输入顶点数和边数:\n");
    scanf("%d,%d",&G->numVertexes,&G->numEdges);/*输入顶点数和边数*/
    for( i = 0;i <G->numVertexes;i++){  //读入顶点信息，建立顶点表
        scanf("%c",&G->vexs[i]);
    }
    for(i = 0;i <G->numVertexes;i++)
        for(j = 0;j <G->numVertexes;j++)
            G->arc[i][j]=INFINITY;  /*邻接矩阵初始化*/
    printf("请按照边格式输入，(Vi，Vj)上的下标i，下标j和权w:\n");
    for(k = 0;k <G->numEdges;k++){  /*读入numEdges条边，建立邻接矩阵*/
        printf("共有%d条边，输入第%d条边:",G->numEdges,k+1);
        scanf("%d,%d,%d",&i,&j,&w); /*输入边(Vi,Vj)上的权w*/
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j];/*邻接矩阵，对称*/
    }
    printf("图以邻接矩阵的数据结构存储在计算机中\n");
}


//#endif