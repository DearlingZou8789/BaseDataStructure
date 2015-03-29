//
//  GraphAdjList.h
//  MinispanTree
//
//  Created by qianfeng on 15/3/24.
//  Copyright (c) 2015年 qianfeng. All rights reserved.
//

#ifndef MinispanTree_GraphAdjList_h
#define MinispanTree_GraphAdjList_h

#include <stdio.h>
#include "GraphType.h"
#include <string.h>

/*邻接表,定义了邻接表的类型*/

typedef struct EdgeNode          /*边表结点*/
{
    int adjvex;                 /*邻接点域，存储该顶点对应的下标*/
    EdgeType weight;            /*用于存储权值，对于非网图可以不需要*/
    struct EdgeNode *next;      /*链域，指向下一个邻接点*/
}EdgeNode;

typedef struct VertexNode        /*顶点表结点*/
{
    VertexType data;            /*顶点域，存储顶点信息，顶点表的数据*/
    struct EdgeNode *firstedge;  /*边表头指针*/
}VertexNode,AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;
    int numVertexes,numEdges;   /*图中当前顶点数和边数*/
}GraphAdjList;                  //图de邻接表

void CreateGraphAdjList(GraphAdjList *G);   /*创建邻接表*/

//邻接表的深度优先递归算法
void DFSGraphAdjList(GraphAdjList *GL,int i);

//邻接表的深度遍历操作
void DFSTraverse(GraphAdjList *GL);



#endif
