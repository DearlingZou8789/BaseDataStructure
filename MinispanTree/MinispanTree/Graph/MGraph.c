//
//  MGraph.c
//  MinispanTree
//
//  Created by qianfeng on 15/3/29.
//  Copyright (c) 2015年 qianfeng. All rights reserved.
//

#include "MGraph.h"

void MGraphCreate(MGraph *G)
{   //创建图的邻接矩阵数据结构
    int i,j,k,w;
    char c;
    printf("输入顶点数和边数:\n");
    scanf("%d,%d", &G->numVertexes, &G->numEdges);/*输入顶点数和边数*/
    for (i=0; i<G->numVertexes; i++)
    {  //读入顶点信息，建立顶点表
        printf("请输入第%d个顶点:", i+1);
        while ((c=getchar())=='\n' && c == EOF);
        fflush(stdin);
        scanf(&G->vexs[i]);
        //        fflush(stdin);
    }
    for (i=0; i<G->numVertexes; i++)
        for (j=0; j<G->numVertexes; j++)
            G->arc[i][j] = INFINITY;  /*邻接矩阵初始化*/
    printf("请按照边格式输入，(Vi，Vj)上的下标i，下标j和权w:\n");
    for (k=0; k<G->numEdges; k++)
    {  /*读入numEdges条边，建立邻接矩阵*/
        printf("共有%d条边，输入第%d条边:", G->numEdges, k+1);
        scanf("%d,%d,%d", &i, &j, &w); /*输入边(Vi,Vj)上的权w*/
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j];/*邻接矩阵，对称*/
    }
    printf("图以邻接矩阵的数据结构存储在计算机中\n");
}
//时间复杂度（n*n)

/*邻接矩阵的深度优先递归算法*/
void MGraphDFS(MGraph *G, int i)
{
    int j;
    visited[i] = TRUE;
    printf("%c", G->vexs[i]);     //打印顶点，也可以其他操作
    for (j=0; j<G->numVertexes; j++)
    {
        //if(G->arc[i][j] == 1 && !visited[j])   //感觉不对，arc[i][j]存储的为权值，权值应为非0且非INIFITY
        if (G->arc[i][j]!=0 && G->arc[i][j]!=INFINITY
           && !visited[j])
            MGraphDFS(G, j);            //对为访问的邻接顶点递归调用
    }
}

//邻接矩阵的深度遍历操作
void MGraphDFSTraverse(MGraph *G){
    int i;
    for (i=0; i<G->numVertexes; i++)
        visited[i] = FALSE;
    for (i=0; i<G->numVertexes; i++)
        if (!visited[i])
            MGraphDFS(G, i);
}
//对于n个顶点e条边的图来说，邻接矩阵由于是二维数组，要查找每个顶点的邻接点需要访问矩阵中的所有元素，因此都需要（n＊n）的时间。

//邻接矩阵的广度遍历算法
void MGraphBFSTraverse(MGraph *G)
{
    int i, j;
    SqQueue Q;
    for (i=0; i<G->numVertexes; i++)
    {
        visited[i] = FALSE;
    }
    SqQueueInit(&Q);    //初始化循环队列表
    for (i=0; i<G->numVertexes; i++)    //对每一个顶点做循环
    {
        if (!visited[i])                //若是未访问过就处理
        {
            visited[i] = TRUE;          //设置当前定点访问过
            printf("%c ", G->vexs[i]);  //打印定点，也可以其他操作
            SqQueueEn(&Q, i);            //将此顶点入队列
            while (!SqQueueEmpty(&Q))   //若当前队列不为空
            {
                SqQueueDe(&Q, i);       //将队中元素出队列，赋值给i
                for (j=0; j<G->numVertexes; j++)
                {
                    //判断其他顶点若与当前定点存在边且未访问过
                    if (G->arc[i][j]==1 && !visited[j])
                    {
                        visited[j] = TRUE;  //将找到的此顶点标记为已访问
                        printf("%c ", G->vexs[j]);  //打印顶点
                        SqQueueEn(&Q, j);   //将找到的此顶点入队列
                    }
                }

            }
        }
    }
}

/*构造连通网的最小代价生成树称为最小生成树*/

//（Prim）普里姆算法：生成最小生成树
void MGraphMiniSpanTree_Prim(MGraph *G)
{
    int min, i, j, k;
    int adjvex[MAXVEX];         //保存相关顶点下标
    int lowcost[MAXVEX];        //保存相关顶点间边的权值
    lowcost[0] = 0;             //初始化第一个权值为0，即V0加入生成树
                   //lowcost的值为0，在这里就是此下表的顶点已经加入生成树
    adjvex[0] = 0;              //初始化第一个顶点下标为0
    for (i=0; i<G->numVertexes; i++)
    {
        lowcost[i] = G->arc[0][i];  //将V0顶点与之有边的权值存入数组
        adjvex[i] = 0;              //初始化都为V0的下标
    }
    for (i=0; i<G->numVertexes; i++)
    {
        min = INFINITY;     //初始化最小权值为无穷大
        j = 1;
        k = 0;
        while (j<G->numVertexes)    //循环全部顶点
        {
            if (lowcost[j]!=0 && lowcost[j]<min)    /*如果权值不为0且权值        
                                                     小于min*/
            {
                min = lowcost[j];   //则让当前权值成为最小值
                k = j;              //将当前最小值的下标存入K
            }
            j++;
        }
        printf("(%d, %d)", adjvex[k], k);//打印当前顶点边中权值最小边
        lowcost[k] = 0; //将当前顶点的权值设置为0，表示此顶点已经完成任务
        for (j=1; j<G->numVertexes; j++)    //循环所有顶点
        {
            if (lowcost[j]!=0 && G->arc[k][j]<lowcost[j])
            {/*若下标为k顶点各边权值小于此前这些顶点未被加入加入生成树权值*/
                lowcost[j] = G->arc[k][j];  //将较小权值存入lowcost
                adjvex[j] = k;          //将下表为k的顶点存入adjvex
            }
        }
    }
}

//邻接矩阵转边集数组,并将边集数组按照权值从小到大排序
void MGraphToEdge(MGraph *G, Edge *E[MAXEDGE])
{
    int i, j;
    int cnt = 0;
    int min;    //min为E[MAXEDGE]数组中最小权值的下标
    Edge *temp = NULL;
    for (i=0; i<G->numVertexes; i++)
    {
        for (j=0; j<G->numVertexes; j++)
        {
            if (!G->arc[i][j] && G->arc[i][j]!=INFINITY)
            {
                E[cnt] = (Edge *)calloc(1, sizeof(Edge));
                E[cnt]->begin = i;
                E[cnt]->end = j;
                E[cnt]->weight = G->arc[i][j];
                cnt++;
            }
        }
    }
    for (i=0; i<cnt-1; i++)
    {
        min = i;
        for (j=i; j<cnt; j++)
        {
            if (E[min]->weight > E[j]->weight)
            {
                min = j;
            }
        }
        if (min!=i)
        {
            temp = E[min];
            E[min] = E[i];
            E[i] = temp;
        }
    }
}

//Kruakal算法中得查找连线顶点的尾部下标
static int Find(int *parent, int f)
{
    while (parent[f]>0)
    {
        f = parent[f];
    }
    return f;
}

//Kruskal算法生成最小生成树
void MGraphMiniSpanTree_Kruskal(MGraph *G)
{
    int i, n, m;
    int parent[MAXVEX]; //定义艺术组用来判断边与边是否形成环路
    Edge *E[MAXEDGE];   //定义一位数组存储指向边集结点的指针
    MGraphToEdge(G, E); //调用函数将MGraph转换成Edge边集数组
    for (i=0; i<G->numVertexes; i++)
    {
        parent[i] = 0;      //初始化数组值为0
    }
    for (i=0; i<G->numEdges; i++) //循环每一条边
    {
        n = Find(parent, E[i]->begin);
        m = Find(parent, E[i]->end);
        if (n!=m)  //假如n和m不等，说明此边没有与现有生成树形成环路
        {
            parent[n] = m;/*将此边的结尾顶点放入下标为起点的parent中
                           表示此顶点已经在生成树集合中*/
            printf("(%d, %d) %d ", E[i]->begin, E[i]->end, E[i]->weight     );
        }
    }
}

/*
*克鲁斯卡尔算法主要是针对边来展开，边数少时效率会非常高，所以对于稀疏图有很大的优势
*而普里姆算法对于稠密图，即边数非常多的情况会更好一些
*/


/*
对于网图来说，最短路径，是值两定点之间经过的边上权值之和最少的路径，并且我们称路径上得第一个顶点是远点，最后一个顶点是终点
*/

/*Dijkstra算法求最短路径，求有向图G的Vo顶点到其余顶点V最短路径P[V]及带权长度D[v]
 *P[v]的值为前驱顶点下标，D[v]表示V0到V的最短路径长度和
 */
void MGraphShortestPath_Dijkstra(MGraph *G, int v0, Pathmatirx *P,
                                 ShortPathTable *D)
{
    int v, w, k, min;
    int final[MAXVEX];  //final[w] = 1表示求得顶点v0到vw的最短路径
    for (v=0; v<G->numVertexes; v++)
    {
        final[v] = 0;   //全部顶点初始化为未知最短路径
        (*D)[v] = G->arc[v0][v];    //将与V0点有连线的顶点加上权值
        (*P)[v] = 0;    //初始化路径数组P为0
    }
    (*D)[v0] = 0;       //v0到v0路径为0
    final[v0] = 1;      //v0到v0不需要求路径
    /*开始主循环，每次求得v0到某个v顶点的最短路径*/
    for (v=1; v<G->numVertexes; v++)
    {
        min = INFINITY;             //当前所知离v0顶点的最近距离
        for (w=0; w<G->numVertexes; w++)    //寻找离v0最近的顶点
        {
            if (!final[w] && (*D)[w]<min)
            {
                k = w;
                min = (*D)[w];  //w顶点离v0顶点更近
            }
        }
        final[k] = 1;   //将目前找到的最近的顶点置为1
        for (w=0; w<G->numVertexes; w++) //修正当前最短路径及距离
        {   /*如果经过v顶点的路径比现在这条路径的长度短的话*/
            if (!final[w] && (min+G->arc[k][w]<(*D)[w]))
            {   /*说明找到了更短的路径，修改D[w]和P[w]*/
                (*D)[w] = min + G->arc[k][w];   //修改当前路径长度
                (*P)[w] = k;
            }
        }
    }
}

/*Floyd算法的核心就是：D0[v][w] = min{D-1[v][w], D-1[v][0]+D-1[0][w]}*/
/*Floyd算法，求网图G中个顶点v到其余顶点w最短路径P[v][w]及带权长度D[v][w]
保存的两个数组P[MAXVEX][MAXVEX]和D[MAXVEX][MAXVEX]是结果，然后查询某个结点到某个结点的路径就利用这两个书数组就可以了*/
void MGraphShortestPath_Floyd(MGraph *G, PathmatrixFloyd *P,
                              ShortPathTableFloyd *D)
{
    int v, w, k;
    for (v=0; v<G->numVertexes; v++)
    {
        for (w=0; w<G->numVertexes; w++)
        {
            (*D)[v][w] = G->arc[v][w];  //D[v][w]值纪委对应点间的权值
            (*P)[v][w] = w;             //初始化P
        }
    }
    for (k=0; k<G->numVertexes; k++)
    {
        for (v=0; v<G->numVertexes; v++)
        {
            for (w=0; w<G->numVertexes; w++)
            {
                if ( (*D)[v][w] > (*D)[v][k]+(*D)[k][w] )
                {
                    /*如果经过下标为k顶点路径比原两点间路径更短
                      将当前两点间权值设为更小的一个*/
                    (*D)[v][w] = (*D)[v][k]+(*D)[k][w];
                    (*P)[v][w] = (*P)[v][k];
                    /*路径设置经过下标为k的顶点*/
                }
            }
        }
    }
}

/*Floyd算法，代码简洁到就是一个二重循环初始化加一个三重循环权值修正，就完成了所有顶点到所有顶点的最短路径计算。时间复杂度（n*n*n）
 如果你面临需要求所有顶点值所有顶点的最短路径问题是，弗洛伊德（Floyd）算法应该是不错的选择
 */

//利用P和D数组求得每个顶点到其他顶点的路径
void MGraphAllShortest(MGraph *G)
{
    int v, w, k;
    ShortPathTableFloyd D;
    PathmatrixFloyd P;
    MGraphShortestPath_Floyd(G, &P, &D);
    for (v=0; v<G->numVertexes; v++)
    {
        for (w=v+1; w<G->numVertexes; w++)
        {
            printf("v%d - v%d weight: %d ", v, w, D[v][w]);
            k = P[v][w];    //获得第一个路径顶点下标
            printf(" path: %d", v); //打印源点
            while (k!=w)
            {
                printf(" -> %d", k);    //打印路径顶点
                k = P[k][w];            //获取下一个路径顶点下标
            }
            printf(" -> %d\n", w);      //打印终点
        }
        printf("\n");
    }
}
