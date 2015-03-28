//
//  GraphType.h
//  MinispanTree
//
//  Created by qianfeng on 15/3/25.
//  Copyright (c) 2015年 qianfeng. All rights reserved.
//

//保存图结构的基本数据类型及最大数组数

#define MAXVEX 100		/*定义最大顶点树为100*/
#define INFINITY 65536		/*用65535来代表∞*/

typedef char VertexType;	/*顶点类型应由用户定义*/
typedef int EdgeType;		/*边上的权值类型应由用户定义*/
typedef int Boolean;        //Boolean是布尔类型，其值是TRUE活FALSE；
Boolean visited[MAXVEX];    //访问标志的数组
