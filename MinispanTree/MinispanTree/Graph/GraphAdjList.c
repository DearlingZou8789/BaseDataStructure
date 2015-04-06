//
//  GraphAdjList.c
//  MinispanTree
//
//  Created by qianfeng on 15/3/29.
//  Copyright (c) 2015年 qianfeng. All rights reserved.
//

#include "GraphAdjList.h"

void GraphAdjListCreate(GraphAdjList *GL)
{   /*创建邻接表*/
    int i, j, k, w;
    char c;
    EdgeNode *e;
    printf("输入顶点数和边数:\n");
    scanf("%d,%d", &GL->numVertexes, &GL->numEdges);/*输入顶点数和边数*/
    for (i=0; i<GL->numVertexes; i++)   //循环顶点,初始化邻接表
    {
        printf("输入第%d个顶点数：", i+1);
        while ((c=getchar())=='\n'&&c==EOF)  //当按下enter键，清除输入的字符
            fflush(stdin);
        scanf(" %c", &GL->adjList[i].data);
        GL->adjList[i].firstedge = NULL;   //顶点的边表为空表
    }
    printf("输入边(Vi，Vj)上的下标i，下标j和权w:\n");
    for (k=0; k<GL->numEdges; k++)
    {  /*读入numEdges条边，建立邻接矩阵*/
        printf("共有%d条边，输入第%d条边:", GL->numEdges, k+1);
        scanf("%d,%d,%d", &i, &j, &w); /*输入边(Vi,Vj)上的权w*/
        e = (EdgeNode *)malloc(sizeof(EdgeNode));   /*新建一个结点*/
        /*向内存申请空间。*/
        /*生成边表结点*/
        e->weight = w;                      /*给边表结点赋权值*/
        e->adjvex = j;                      /*邻接边序号为j*/
        e->next = GL->adjList[i].firstedge;  //将e指针指向当前顶点指向的结点
        GL->adjList[i].firstedge = e;        //将当前顶点的指针指向e

        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->weight = w;
        e->adjvex = i;
        e->next = GL->adjList[j].firstedge;
        GL->adjList[j].firstedge = e;
    }
}
//时间复杂度(n)

//邻接表的深度优先递归算法
void GraphAdjListDFS(GraphAdjList *GL, int i)
{
    EdgeNode *p;
    visited[i] = TRUE;
    printf("%c", GL->adjList[i].data);   //打印i顶点的数据
    p = GL->adjList[i].firstedge;
    while (p)
    {
        if (!visited[p->adjvex])
        {
            DFSGraphAdjList(GL,p->adjvex);          //对未访问的邻接顶点递归调用
        }
        p = p->next;
    }
}

//邻接表的深度遍历操作
void GraphAdjListDFSTraverse(GraphAdjList *GL)
{
    int i;
    for (i=0; i<GL->numVertexes; i++)
        visited[i] = FALSE;           //初始化visited数组，将其设置为未访问
    for (i=0; i<GL->numVertexes; i++)
    {
        if (!visited[i])             //对未访问的顶点i进行DFS访问,对于连通图,只会执行一次
        {
            GraphAdjListDFS(GL,i);
        }
    }
}
//对于点多边少的稀疏图来说，邻接表结构似的算法在时间效率上大大提高
//找邻接点所需的时间取决于顶点和边数，时间复杂度（n＋e）

//邻接表的广度遍历算法
void GraphAdjListBFSTraverse(GraphAdjList *GL)
{
    int i;
    EdgeNode *p;
    SqQueue Q;
    for (i=0; i<GL->numVertexes; i++)
    {
        visited[i] = FALSE;
    }
    SqQueueInit(&Q);
    for (i=0; i<GL->numVertexes; i++)
    {
        if (!visited[i])
        {
            visited[i] = TRUE;
            printf("%c ", GL->adjList[i].data); //打印顶点，也可以其他操作
            SqQueueEn(&Q, i);
            while (!SqQueueEmpty(&Q))
            {
                SqQueueDe(&Q, i);
                p = GL->adjList[i].firstedge;   //找到当前顶点边表链表头指针
                while (p)
                {
                    if (!visited[p->adjvex])
                    {
                        visited[p->adjvex] = TRUE;
                        printf("%c ", GL->adjList[p->adjvex].data);
                        SqQueueEn(&Q, p->adjvex);   //将此顶点入队列；
                    }
                    p = p->next;                //指针指向下一个邻接点
                }
            }
        }
    }
}
/*深度优先遍历更适合目标比较明确，已找到目标位主要目的情况，而广度优先更适合在不断扩大遍历范围时找到相对最优解的情况
 */
