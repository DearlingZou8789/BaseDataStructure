//
//  GraphAdjList.c
//  MinispanTree
//
//  Created by qianfeng on 15/3/29.
//  Copyright (c) 2015年 qianfeng. All rights reserved.
//

#include "GraphAdjList.h"

void CreateGraphAdjList(GraphAdjList *G){   /*创建邻接表*/
    int i,j,k,w;
    char c;
    EdgeNode *e;
    printf("输入顶点数和边数:\n");
    scanf("%d,%d",&G->numVertexes,&G->numEdges);/*输入顶点数和边数*/
    for(i=0;i<G->numVertexes;i++)   //循环顶点,初始化邻接表
    {
        printf("输入第%d个顶点数：",i+1);
        while((c=getchar())=='\n'&&c==EOF)  //当按下enter键，清除输入的字符
            fflush(stdin);
        scanf(" %c",&G->adjList[i].data);
        G->adjList[i].firstedge=NULL;   //顶点的边表为空表
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
        e->next = G->adjList[i].firstedge;  //将e指针指向当前顶点指向的结点
        G->adjList[i].firstedge = e;        //将当前顶点的指针指向e

        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->weight = w;
        e->adjvex = i;
        e->next = G->adjList[j].firstedge;
        G->adjList[j].firstedge = e;
    }
}
//时间复杂度(n)

//邻接表的深度优先递归算法
void DFSGraphAdjList(GraphAdjList *GL,int i){
    EdgeNode *p;
    visited[i]=TRUE;
    printf("%c",GL->adjList[i].data);   //打印i顶点的数据
    p = GL->adjList[i].firstedge;
    while(p){
        if(!visited[p->adjvex])
            DFSGraphAdjList(GL,p->adjvex);          //对未访问的邻接顶点递归调用
        p = p->next;
    }
}

//邻接表的深度遍历操作
void DFSTraverse(GraphAdjList *GL){
    int i;
    for(i = 0;i < GL->numVertexes;i++)
        visited[i]=FALSE;           //初始化visited数组，将其设置为未访问
    for(i = 0;i < GL->numVertexes;i++)
        if(!visited[i])             //对未访问的顶点i进行DFS访问,对于连通图,只会执行一次
            DFSGraphAdjList(GL,i);
}
//对于点多边少的稀疏图来说，邻接表结构似的算法在时间效率上大大提高
//找邻接点所需的时间取决于顶点和边数，时间复杂度（n＋e）

