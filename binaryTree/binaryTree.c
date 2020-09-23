#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum PointerTag{Link, Thread} PointerTag;
typedef char TElemType;
typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
    PointerTag LTag, RTag;
} BiTNode, *BiTree;

//先序输入
BiTree CreateBiTree() {
    char c;
    BiTree t;
    if((c = getchar()) == ' ') {
        t = NULL;       
    }
    else {
        t = (BiTree)malloc(sizeof(BiTNode));
        t->data = c;
        t->lchild = CreateBiTree();
        t->rchild = CreateBiTree();
    }
    return t;
}

void PreOrderTraverse(BiTree t) {
    char c;
    if(t) {
        printf("%c", t->data);
        PreOrderTraverse(t->lchild);
        PreOrderTraverse(t->rchild);
    }
}

void InOrderTraverse(BiTree t) {
    char c;
    if(t) {
        InOrderTraverse(t->lchild);
        printf("%c", t->data);
        InOrderTraverse(t->rchild);
    }
}

int main() {
    BiTree t = CreateBiTree();
    printf("Pre Order Traverse:\n");
    PreOrderTraverse(t);
    printf("\nIn Order Traverse:\n");
    InOrderTraverse(t);
    return 0;
}