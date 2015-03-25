//
//  GraphAdjList.h
//  MinispanTree
//
//  Created by qianfeng on 15/3/24.
//  Copyright (c) 2015年 qianfeng. All rights reserved.
//
#include "GraphType.h"
//#ifndef MinispanTree_GraphAdjList_h
//#define MinispanTree_GraphAdjList_h

/*邻接表,定义了邻接表的类型*/

typedef char VertexType;        /*顶点类型应由用户定义*/
typedef int EdgeType;           /*边上的权值类型应由用户定义*/

typedef struct EdgeNode          /*边表结点*/
{
    int adjvex;                 /*邻接点域，存储该顶点对应的下标*/
    EdgeType weight;            /*用于存储权值，对于非网图可以不需要*/
    struct EdgeNode *next;      /*链域，指向下一个邻接点*/
}EdgeNode;

typedef struct VertexNode        /*顶点表结点*/
{
    VertexType data;            /*顶点域，存储顶点信息，顶点表的数据*/
    struct EdgeNode *firstdege;  /*边表头指针*/
}VertexNode,AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;
    int numVertexes,numEdges;   /*图中当前顶点数和边数*/
}GraphAdjList;

void CreateGraphAdjList(GraphAdjList *G){   /*创建邻接表*/
    int i,j,k,w;
    EdgeNode *e;
    printf("输入顶点数和边数:\n");
    scanf("%d,%d",&G->numVertexes,&G->numEdges);/*输入顶点数和边数*/
    for( i = 0;i <G->numVertexes;i++){  //读入顶点信息，建立顶点表
        //在自己电脑程序中有改变，下课后更改
        scanf(&G->adjList[i].data);
        G->adjList[i].firstdege=NULL;  /*邻接表初始化*/
    }
    printf("输入边(Vi，Vj)上的下标i，下标j和权w:\n");
    for(k = 0;k <G->numEdges;k++){  /*读入numEdges条边，建立邻接矩阵*/
        printf("共有%d条边，输入第%d条边:",G->numEdges,k+1);
        scanf("%d,%d,%d",&i,&j,&w); /*输入边(Vi,Vj)上的权w*/
        e = (EdgeNode *)malloc(sizeof(EdgeNode));   /*新建一个结点*/
                                            /*向内存申请空间。*/
                                            /*生成边表结点*/
        e->weight = w;                      /*给边表结点赋权值*/
        e->adjvex = j;                      /*邻接边序号为j*/
        e->next = G->adjList[i].firstdege;  //将e指针指向当前顶点指向的结点
        G->adjList[i].firstdege = e;        //将当前顶点的指针指向e

        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->weight = w;
        e->adjvex = i;
        e->next = G->adjList[j].firstdege;
        G->adjList[j].firstdege = e;
    }
}

//#endif
