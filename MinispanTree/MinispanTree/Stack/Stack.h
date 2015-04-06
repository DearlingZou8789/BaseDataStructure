#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "../structtype.h"


typedef int SElemType;	/*SElemType类型根据实际情况而定，这里假设是int*/

#ifndef STACKMAXSIZE
#define STACKMAXSIZE 100
#endif

typedef struct{     //定义顺序存储栈
    SElemType data[STACKMAXSIZE];
    int top;    //用于栈顶指针
}SqStack;

//使用顺序存储栈之前，初始化栈
extern void SqStackInit(SqStack *S);

//顺序存储栈为空函数
extern Status SqStackEmpty(SqStack *S);

//进栈操作push
extern Status SqStackPush(SqStack *S, SElemType e);

//出栈操作pop
extern Status SqStackPop(SqStack *S, SElemType e);


//两栈共享空间：它们是在数组的两端，向中间靠拢。top1和top2是栈1和栈2的栈顶指针，
//可以想想，只要它们俩不见面，两个占就可以一直使用
//两栈共享空间结构，顺序存储栈
typedef struct{
    SElemType data[STACKMAXSIZE];
    int top1;   //栈1栈顶指针
    int top2;   //栈2栈顶指针
}SqDoubleStack;

//初始化两栈共享空间结构
extern void SqDoubleStackInit(SqDoubleStack *S);

//判断两栈共享空间结构是否为空
extern Status SqDoubleEmpty(SqDoubleStack *S);

//对于两栈共享空间的push方法，除了要插入元素值参数外，还需要有一个判断是栈1还是栈2的栈号参数stackNumber
//插入元素e为新的栈顶元素
extern Status SqDoublePush(SqDoubleStack *S, SElemType e,
                           int stackNumber);

//对于两栈共享空间的pop方法，参数就是判断栈1栈2的参数stackNumber
//若栈不空，则删除S的栈顶元素，则e返回其值，并返回OK；否则返回ERROR
extern Status SqDoublePop(SqDoubleStack *S, SElemType e,
                          int stackNumber);

//栈的链式存储结构
//栈的链式结点
typedef struct StackNode{
    SElemType data;
    struct StackNode *next;
}StackNode,*LinkStackPtr;

typedef struct LinkStack{   //链式栈
    LinkStackPtr top;
    int count;  //链式栈的个数
}LinkStack;

//使用前，初始化链式栈
extern void LinkStackInit(LinkStack *S);

//判断链式栈是否为空
extern Status LinkStackEmpty(LinkStack *S);

/*在链式栈中插入元素e为新的栈顶元素*/
extern Status LinkStackPush(LinkStack *S, SElemType e);

//在链式栈中删除一个结点e
//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR
extern Status LinkStackPop(LinkStack *S, SElemType e);


#endif