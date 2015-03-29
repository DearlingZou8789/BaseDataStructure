#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include "../structtype.h"

#ifndef QUEUEMAXSIZE
#define QUEUEMAXSIZE 100
#endif

typedef int QElemType;	//QElemType类型根据实际情况而定，这里假设为int

//循环队列的顺序存储结构
typedef struct{
	QElemType data[QUEUEMAXSIZE];
	int rear;	//尾指针，若队列不空，指向队列元素的下一个位置
	int front;	//头指针
}SqQueue;

//循环队列函数申明
//初始化循环队列为空队列
Status InitSqQueue(SqQueue *Q);

//返回队列Q的元素长度，也就是队列的当前长度
int SqQueueLength(SqQueue Q);

//循环队列的入队操作
//若队列未满，则插入元素e为Q新的队尾元素
Status EnSqQueue(SqQueue Q,QElemType e);

//循环队列出对操作
//若队列为空，则删除Q中队头元素，用e返回值
Status DeSqQueue(SqQueue *Q,QElemType e);


//队列的链式结构
typedef struct QNode{   //链结点结构
    QElemType data;
    struct QNode *next;
}QNode,*QueuePtr;       //QNode结点，QueuePtr结点指针

typedef struct{         //队列的链表结构
    QueuePtr front,rear;    //队头，队尾指针
}LinkQueue;

//链队列的初始化，使用前
Status initEnLinkQueue(LinkQueue *Q);


//链队列的入队操作
//输入元素e为Q的新的队尾元素
Status EnLinkQueue(LinkQueue *Q,QElemType e);

//出队操作，链队列
Status DeLinkQueue(LinkQueue *Q,QElemType *e);


#endif