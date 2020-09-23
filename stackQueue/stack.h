// 后进先出的线性表 last in first out(LIFO)
// How to use this head file
// first of all, you should typedef **your data type** SElemType

//#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int SElemType;

typedef struct {
    SElemType* base;	   //栈底指针 NULL表示结构不存在
    SElemType* top;	   //栈顶指针 top==base可表示空栈
    int stacksize; //最大容量
} SqStack;

int InitStack(SqStack* s)
{
    s->base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!s->base)
	exit(0);
    s->top = s->base;
    s->stacksize = STACK_INIT_SIZE;
    return 1;
}

int DestoryStack(SqStack* s)
{
    free(s->base);
    return 1;
}

int ClearStack(SqStack* s)
{
    s->top = s->base;
    return 1;
}

bool StackEmpty(SqStack s)
{
    return (s.base == s.top) ? true : false;
}

int SqStackLength(SqStack s)
{
    return s.top - s.base;
}

int GetTop(SqStack s, SElemType* e)
{
    if (s.top == s.base)
	return 0;
    *e = *(s.top - 1);
    return 1;
}

int Push(SqStack* s, SElemType e)
{
    if (s->top - s->base >= s->stacksize) {
	s->base = (SElemType*)realloc(s->base, (s->stacksize + STACKINCREMENT) * sizeof(SElemType));
	if (!s->base)
	    exit(0);
	s->top = s->base + s->stacksize;
	s->stacksize += STACK_INIT_SIZE;
    }
    *(s->top++) = e;
    return 1;
}

int Pop(SqStack* s, SElemType* e)
{
    if (s->top == s->base)
	return 0;
    *e = *(--s->top);
    return 1;
}
