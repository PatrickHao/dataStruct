#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 10
#define LISTINCREAMENT 10

typedef struct {
    int* elem;
    int length;
    int listsize;
} SqList;

int InitList_Sq(SqList * L)
{
    L->elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
    if (!L->elem)
	exit(0);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
	return 1;
}

int Insert_Sq(SqList* L, int i, int m)
{
    if (i <= 0 || i > L->listsize)
	exit(0);
    if (L->length >= L->listsize) {
	int* newbase = (int*)realloc(L->elem, (L->listsize + LISTINCREAMENT) * sizeof(int));
	if (!newbase)
	    exit(0);
	L->elem = newbase;
	L->listsize += LISTINCREAMENT;
    }
    int* q = &(L->elem[i - 1]);
    for (int* p = &(L->elem[L->length - 1]); p >= q; --p) //elem[]是一个数组，要减去1
	*(p + 1) = *p;
	*q=m;
    L->length++;
    return 1;
}

int Delete_Sq(SqList* L, int i, int* m)
{
    if (i <= 0 || i > L->listsize)
	exit(0);
    int* p = &(L->elem[i - 1]); //删除元素位置
    *m = *p;
    int* q = L->elem + L->length - 1;
    for (++p; p <= q; ++p)
	*(p - 1) = *p;
    --L->length;
    return 1;
}

int Location_Sq(SqList* L, int m)
{
    int* p = L->elem;
    int i = 1;
    for (; i <= L->length; i++)
	if (L->elem[i - 1] == m)
	    break;
    return i <= L->length ? i : -1;
}

int MergeList_Sq(SqList* A, SqList* B, SqList* C)
{
    int* a = A->elem;
    int* b = B->elem;
    int* a_l = A->elem + A->length - 1;
    int* b_l = B->elem + B->length - 1;

    //创立C表
    C->listsize = C->length = A->length + B->length;
    int* c = C->elem = (int*)malloc(C->listsize * sizeof(int));
    if (!c)
	exit(0);
    while (a <= a_l && b <= b_l) {
	if (*a <= *b)
	    *c++ = *a++;
	else
	    *c++ = *b++;
    }
    while (a < a_l)
	*c++ = *a++;
    while (b < b_l)
	*c++ = *b++;
    return 1;
}

int main(){
	//不能直接SqList * L;其未被初始化，指向的地址不一定有足够的空间;
	//方案一
	//SqList LL;
	//SqList * L=&LL;
	//方案二
	SqList * L=(SqList *)malloc(sizeof(SqList));
	InitList_Sq(L);
	for(int i=1;i<6;i++)
		printf("%d\n",Insert_Sq(L,i,i));
	printf("%d\n",L->listsize);
	printf("%d\n",L->length);
	for(int i=0;i<5;i++)
		printf("%d\n",L->elem[i]);
}
