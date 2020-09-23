#include "maze.h"
#include <stdio.h>

void InitMaze(Maze* m, int n[][MAZE_ROW])
{
    for (int i = 0; i < MAZE_ROW; i++) {
	for (int j = 0; j < MAZE_COL; j++) {
	    m->map[i][j] = n[i][j];
	}
    }
}

//the function to print the maze
void ptmaze(Maze* m)
{
    for (int i = 0; i < 20; i++) {
	for (int j = 0; j < 20; j++) {
	    switch (m->map[i][j]) {
	    case 0:
		printf("\033[47;31m   \033[0m");
		break;
	    case 1:
		printf("[ ]");
		break;
	    case 2:
		printf("\033[47;31m * \033[0m");
		break;
	    default:
		break;
	    }
	}
	printf("\n");
    }
}

int PassAble(PosType now, Maze* m)
{
    if (m->map[now.x][now.y] == 1)
	return 0;
    return 1;
}

PosType NextPos(SElemType s)
{
    PosType pos;
    pos.x = s.seat.x;
    pos.y = s.seat.y;
    pos.step = 0;
    switch (s.di) {
    case 1:
	pos.y++;
	break;
    case 2:
	pos.x++;
	break;
    case 3:
	pos.y--;
	break;
    case 4:
	pos.x--;
	break;
    }
    return pos;
}

int main()
{
    int maze[20][20] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1 },
	{ 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
	{ 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1 },
	{ 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1 },
	{ 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1 },
	{ 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
	{ 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
	{ 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
	{ 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1 },
	{ 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1 },
	{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    };
    Maze* m = (Maze*)malloc(sizeof(Maze));
    InitMaze(m, maze);
    printf("This is my maze\n");
    ptmaze(m);

    //数据准备
    PosType start = { 1, 1, 0 }; //入口
    PosType end = { 18, 18, 0 }; //出口
    PosType test = { 1, 1, 1 };	 //出口
    PosType curpos = start;
    int curstep = 1;

    //栈
    SqStack* L = (SqStack*)malloc(sizeof(SqStack));
    InitStack(L);

    int j;

    do {
	j = PassAble(curpos, m);
	if (j == 1) {
	    m->map[curpos.x][curpos.y] = 1;
	    SElemType e = { curstep, curpos, 1 };
	    Push(L, e);
	    if (curpos.x == end.x && curpos.y == end.y)
		break;
	    curpos = NextPos(e);
	    curstep++;
	} else {
	    if (!StackEmpty(*L)) {
		SElemType* p = (SElemType*)malloc(sizeof(SElemType));
		Pop(L, p);
		while (p->di == 4 && !StackEmpty(*L)) {
		    Pop(L, p);
		    free(p);
		}
		if (p->di < 4) {
		    p->di++;
		    Push(L, *p);
		    curpos = NextPos(*p);
		    free(p);
		}
	    }
	}
    } while (!StackEmpty(*L) && curstep < 100);
    printf("The length of the Stack is %d\n", SqStackLength(*L));

    SElemType* p = (SElemType*)malloc(sizeof(SElemType));
    while (!StackEmpty(*L)) {
	Pop(L, p);
	maze[p->seat.x][p->seat.y] = 2;
    }
    Maze* n = (Maze*)malloc(sizeof(Maze));
    InitMaze(n, maze);
    printf("This is my solution\n");
    ptmaze(n);

    return 0;
}
