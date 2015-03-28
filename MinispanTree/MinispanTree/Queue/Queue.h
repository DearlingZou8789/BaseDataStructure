#include <stdio.h>
#include "../structtype.h"

#define MAXSIZE 100
typedef int QElemType;	//QElemType类型根据实际情况而定，这里假设为int

//循环队列的顺序存储结构
typedef struct{
	QElemType data[MAXSIZE];
	int rear;	//尾指针，若队列不空，指向队列元素的下一个位置
	int front;	//头指针
}SqQueue;

//初始化循环队列为空队列
Status InitSqQueue(SqQueue *Q){
	Q->front=0;
	Q->rear=0;
	return OK;
}

//返回队列Q的元素长度，也就是队列的当前长度
int SqQueueLength(SqQueue Q){
    return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}

//循环队列的入队操作
//若队列未满，则插入元素e为Q新的队尾元素
Status EnSqQueue(SqQueue Q,QElemType e){
    if((Q.rear+1)%MAXSIZE==Q.front)    //队列满的标志
        return ERROR;
    Q.data[Q.rear]=e            //将该元素e插入到队尾
    Q.rear=(Q.rear+1)%MAXSIZE;  //rear指针向后移动一个位置，若到最后则转到数组头部
    return Ok;
}


//循环队列出对操作
//若队列为空，则删除Q中队头元素，用e返回值
Status DeSqQueue(SqQueue *Q,QElemType *e){
    if(Q->front==Q->rear)       //队列空的判断
        return ERROR;
    *e=Q->data[Q->front];       //将队头的元素返回给e
    Q->front=(Q->front+1)%MAXSIZE;  //将对头指针向后移动一个位置
                                //若到最后则转到数组头部
    return OK;
}

//队列的链式结构
typedef struct QNode{   //链结点结构
    QElemType data;
    struct QNode *next;
}QNode,*QueuePtr;       //QNode结点，QueuePtr结点指针

typedef struct{         //队列的链表结构
    QueuePtr front,rear;    //队头，队尾指针
}LinkQueue;


//链队列的入队操作
//输入元素e为Q的新的队尾元素
Status EnLinkQueue(LinkQueue *Q,QElemType e){
    QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
    if(!s)  //存储分配失败
        exit(OVERFLOW);
    s->data = e;
    s->next = NULL;
    Q->rear->next = s;  //把拥有元素e新结点s赋值给原队尾结点的后继
    Q->rear = s;        //将队尾指针移到s结点
    return Ok;
}

//出队操作，链队列
Status DeLinkQueue(LinkQueue *Q,QElemType e){
    if(Q->front==Q->rear)   //若队尾与队头相同，则为空队列
        return ERROR;
    QueuePtr p;
    p = Q->front->next; //先保存头指针指向的结点p
    *e = p->data;       //将要出列的结点数据传给e
    Q->front->next = p->next;    //将队头指针往后移一个位置，将原队头结点后继p->next赋值给偷结点后继
    if(Q->rear==p)      //出队后,队头与队尾相等
        Q->rear=Q->front;
    free(p);
    return Ok;
}
