//#ifndef MinispanTree_GraphAdjList_h
//#define MinispanTree_GraphAdjList_h
/*图表的邻接矩阵*/
#include "GraphType.h"

typedef struct {
    VertexType vexs[MAXVEX];	/*顶点表*/
	EdgeType arc[MAXVEX][MAXVEX];	/*邻接矩阵，可这看作表*/
	int numVertexes,numEdges;	/*图中当前的顶点树和边数*/
}MGraph;

void CreateMGraph(MGraph *G){   //创建图的邻接矩阵数据结构
    int i,j,k,w;
    char c;
    printf("输入顶点数和边数:\n");
    scanf("%d,%d",&G->numVertexes,&G->numEdges);/*输入顶点数和边数*/
    for( i = 0;i <G->numVertexes;i++){  //读入顶点信息，建立顶点表
        printf("请输入第%d个顶点:",i+1);
        while((c = getchar()) == '\n' && c == EOF);
        fflush(stdin);
        scanf(&G->vexs[i]);
//        fflush(stdin);
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
//时间复杂度（n*n)

/*邻接矩阵的深度优先递归算法*/
void DFS(MGraph *G,int i){
    int j;
    visited[i] = TRUE;
    printf("%c",G->vexs[i]);     //打印顶点，也可以其他操作
    for(j = 0;j < G->numVertexes; j++){
        //if(G->arc[i][j] == 1 && !visited[j])   //感觉不对，arc[i][j]存储的为权值，权值应为非0且非INIFITY
        if(G->arc[i][j]!=0 && G->arc[i][j]!=INFINITY && !visited[j])
           DFS(G,j);            //对为访问的邻接顶点递归调用
    }
}

//邻接矩阵的深度遍历操作
void DFSTraverse(MGraph *G){
    int i;
    for(i = 0;i < G->numVertexes; i++)
        visited[i] = FALSE;
    for(i = 0;i < g->numVertexes; i++)
        if(!visited[i])
            DFS(G,i)
}
//对于n个顶点e条边的图来说，邻接矩阵由于是二维数组，要查找每个顶点的邻接点需要访问矩阵中的所有元素，因此都需要（n＊n）的时间。

//邻接矩阵的广度遍历算法

void BFSTraverse(MGraph *G){
    
}