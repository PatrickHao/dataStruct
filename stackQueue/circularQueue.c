#include <stdio.h>
#include <stdlib.h>

#define MAXQSIZE 10

typedef struct {
    int* base;
    int front;
    int rear;
} SqQueue;

int InitQueue(SqQueue q)
{
    q.base = (int*)malloc(MAXQSIZE * sizeof(int));
    if (!q.base)
	return 0;
    q.front = q.rear = 0;
    return 1;
}

int QueueLength(SqQueue q)
{
    return (q.rear - q.front + MAXQSIZE) % MAXQSIZE; //消除负数
}

int EnQueue(SqQueue* q, int e)
{
    if ((q->rear + 1) % MAXQSIZE == q->front)
	return 0;
    q->base[q->rear] = e;
    q->rear = (q->rear + 1) % MAXQSIZE;
    return 1;
}

int DeQueue(SqQueue* q, int* e) //e接受返回值
{
    if (q->front == q->rear)
	return 0;
    *e = q->base[q->front];
    q->front = (q->front + 1) % MAXQSIZE;
    return 1;
}

//No drive
