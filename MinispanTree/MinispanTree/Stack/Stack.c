//
//  Stack.c
//  MinispanTree
//
//  Created by qianfeng on 15/3/29.
//  Copyright (c) 2015年 qianfeng. All rights reserved.
//

#include "Stack.h"
#include "../structtype.h"


//使用顺序存储栈之前，初始化栈
void initSqStack(SqStack *S){
    S->top=-1;  //顺序存储栈是从0开始的，所以初始化是从-1开始
}

//进栈操作push
Status Push(SqStack *S,SElemType e){
    if(S->top==MAXSIZE-1)   //栈满了
        return ERROR;
    S->top++;               //栈顶指针加1
    S->data[S->top]=e;         //将新插入元素赋值给栈顶空间
    return OK;
}

//出栈操作pop
Status Pop(SqStack *S,SElemType e){
    if(S->top==0)   //栈为空
        return ERROR;
    e=S->data[S->top];
    S->top--;
    return OK;
}



//初始化两栈共享空间结构
void initSqDoubleStack(SqDoubleStack *S){
    S->top1=-1;     //注意栈1是从0下标开始的，所以初始化时是从-1开始
    S->top2=MAXSIZE;    //栈2是栈1相反的方向开始的，其值是从MAXSIZE-1开始，所以是从MAXSIZE开始的
}

//对于两栈共享空间的push方法，除了要插入元素值参数外，还需要有一个判断是栈1还是栈2的栈号参数stackNumber
//插入元素e为新的栈顶元素
Status SqPush(SqDoubleStack *S,SElemType e,int stackNumber){
    if(S->top1+1==S->top2)   //栈已满，不能再push元素了
        return ERROR;
    if(stackNumber==1)  //栈1有元素进入
        S->data[++S->top1] = e; //若栈1则先top1+1后给数组元素赋值
    else if(stackNumber==2) //栈2有元素进入
        S->data[++S->top2] = e; //若栈2则先top2+1后给数组元素赋值
    return OK;
}

//对于两栈共享空间的pop方法，参数就是判断栈1栈2的参数stackNumber
//若栈不空，则删除S的栈顶元素，则e返回其值，并返回OK；否则返回ERROR
Status SqPop(SqDoubleStack *S,SElemType e,int stackNumber){
    if(stackNumber==1){
        if(S->top1==-1)
            return ERROR;   //说明栈1已经是空栈，溢出
        e=S->data[S->top1--];  //将栈1的栈顶元素出栈
    }else if(stackNumber==2){
        if(S->top2==MAXSIZE)
            return ERROR;   //说明栈2已经是空栈，溢出
        e=S->data[S->top2++];  //将栈2的栈顶元素出栈
    }
    return OK;
}




//使用前，初始化链式栈
void initLinkStack(LinkStack *S){
    S->top=NULL;    //初始化是，栈顶指针为空
    S->count=0;     //初始化时，栈的元素个数为空
}
//判断链式栈是否为空
Status LinkStackEmpty(LinkStack *S){
    if(S->count==0)
        return OK;
    return ERROR;
}

/*在链式栈中插入元素e为新的栈顶元素*/
Status LinkStackPush(LinkStack *S,SElemType e){
    LinkStackPtr s=(LinkStackPtr)malloc(sizeof(StackNode));
    s->data = e;
    s->next = S->top;   //将当前的栈顶元素赋值给新结点的直接后继
    S->top = s;         //将新的结点元素赋值给栈顶指针，
    S->count++;
    return OK;
}

//在链式栈中删除一个结点e
//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR
Status LinkStackPop(LinkStack *S,SElemType e){
    LinkStackPtr p;
    if(LinkStackEmpty(S))
        return ERROR;
    e=S->top->data;     //将栈顶结点元素赋值给e
    p=S->top;           //将栈顶指针赋值给p
    S->top=p->next;     //将栈顶指针向下移一位，指向后一个结点
    free(p);            //释放结点p
    S->count--;
    return OK;
}
