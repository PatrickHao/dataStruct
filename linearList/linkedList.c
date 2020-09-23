//单链表的相关算法
#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {
    int data;
    struct LNode* next;
} LNode, *LinkList;

int CreateList(LinkList L, int n) //n元素个数
{
    L->next = NULL;
    for (int i = 0; i < n; i++) {
	LinkList p = (LinkList)malloc(sizeof(LNode));
	scanf("%d", &p->data);
	p->next = L->next;
	L->next = p;
    }

    return 0;
}

int LocateList(LinkList L, int n, int* m) //m接受返回值
{
    LinkList p = L->next;
    int i = 1;
    while (p && i < n) {
	i++;
	p = p->next;
    }
    if (!p || i > n)
	return 0;
    *m = p->data;
    return 1;
}

int InsertList(LinkList L, int n, int m) //m为data
{
    LinkList p = L;
    int j = 0;
    while (p->next && j < n - 1) {
	p = p->next;
	j++;
    }
    if (!p || j > n - 1) {
	//要找到n前一个即n-1
	return 0;
    }
    LinkList s = (LinkList)malloc(sizeof(LNode));
    s->data = m;
    s->next = p->next;
    p->next = s;
    return 1;
}

int DeleteList(LinkList L, int n, int* m) //m接受返回值
{
    LinkList p = L;
    int j = 0;
    while (p->next && j < n - 1) {
	j++;
	p = p->next;
    }
    if (!p || j > n - 1)
	return 0;
    LinkList q = p->next;
    *m = q->data;
    p->next = q->next;
    free(q);
    return 1;
}

void MergeList(LinkList La, LinkList Lb, LinkList Lc)
{
    LinkList a = La;
    LinkList b = Lb;
    LinkList c = Lc = La;
    while (a && b) {
	if (a->data <= b->data) {
	    c->next = a;
	    c = a;
	    a = a->next;
	} else {
	    c->next = b;
	    c = b;
	    b = b->next;
	}
	c->next = a ? a : b;
	free(b);
    }
}

int main()
{
    LinkList L = (LinkList)malloc(sizeof(LNode));
    CreateList(L, 6);
    int* m = (int*)malloc(sizeof(int));
    LocateList(L, 3, m);
    printf("%d\n", *m);
}
