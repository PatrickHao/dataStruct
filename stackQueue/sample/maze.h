#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define MAZE_ROW 20
#define MAZE_COL 20

typedef struct Maze {
    int map[MAZE_COL][MAZE_ROW];
} Maze;

typedef struct {
    int x;
    int y;
    int step;
} PosType;

typedef struct {
    int ord;	  //通道块在路径上的序号
    PosType seat; //坐标
    int di;	  //到下一块的方向
} SElemType;

typedef struct {
    SElemType* base; //栈底指针 NULL表示结构不存在
    SElemType* top;  //栈顶指针 top==base可表示空栈
    int stacksize;   //最大容量
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

int StackEmpty(SqStack s)
{
    return (s.base == s.top) ? 1 : 0;
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
