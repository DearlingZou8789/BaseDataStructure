//
//  main.c
//  MinispanTree
//
//  Created by qianfeng on 15/3/24.
//  Copyright (c) 2015年 qianfeng. All rights reserved.
//

#include "main.h"
#include "Graph/GraphAdjList.h"
#include "Graph/MGraph.h"

int main(int argc,const char *argv[]){
    int choice;     //存储选择格式进行存储
    printf("请选择存储格式进行存储，1表示邻接矩阵，2表示邻接表：");
    scanf("%1d",&choice);
    switch(choice){
        case 1:
            MGraph *G=malloc(sizeof(MGraph));
//            G = malloc(sizeof(MGraph));
            CreateMGraph(G);
            break;
        case 2:
            GraphAdjList *GM=malloc(sizeof(GraphAdjList));
//            GM = malloc(sizeof(GraphAdjList));
            CreateGraphAdjList(GM);
            break;
        default:
            return 0;
    }
    return 0;
}