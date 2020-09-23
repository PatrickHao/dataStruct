#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 12500
#define MAXRC 1000

typedef int ElemType;
typedef struct {
    int i, j;
    ElemType e;
} Triple;
typedef struct {
    Triple data[MAXSIZE + 1]; //data[0]未使用
    int mu, nu, tu;	      //行数、列数、非零元个数
} TSMatrix;

void display_matrix(TSMatrix M)
{
    printf("======\n");
    printf("i j v\n");
    printf("------\n");
    for (int a = 1; a <= M.tu; a++) {
	printf("%d %d %d\n", M.data[a].i, M.data[a].j, M.data[a].e);
    }
    printf("======\n");
}

void display_matrix_normal(TSMatrix M)
{
    int arr[M.nu][M.mu];
    for (int a = 0; a < M.nu; a++) {
	for (int b = 0; b < M.mu; b++) {
	    arr[a][b] = 0;
	}
    }
    for (int a = 1; a <= M.tu; a++) {
	arr[M.data[a].i - 1][M.data[a].j - 1] = M.data[a].e;
    }
    for (int a = 0; a < M.nu; a++) {
	for (int b = 0; b < M.mu; b++) {
	    printf("%2d ", arr[a][b]);
	}
	printf("\n");
    }
}

void TransposeMatrix(TSMatrix M, TSMatrix* T)
{
    T->mu = M.nu;
    T->nu = M.mu;
    T->tu = M.tu;

    if (T->tu) {
	int q = 1;
	for (int a = 1; a <= M.nu; a++) {
	    for (int b = 1; b <= M.tu; b++) {
		if (M.data[b].j == a) {
		    T->data[q].i = M.data[b].j;
		    T->data[q].j = M.data[b].i;
		    T->data[q].e = M.data[b].e;
		    ++q;
		}
	    }
	}
    }
}

int main()
{
    //M输入
    int mu, nu, tu;
    mu = nu = tu = 0;
    scanf("%d%d%d", &mu, &nu, &tu);
    TSMatrix M;
    TSMatrix T;
    M.tu = tu;
    M.mu = mu;
    M.nu = nu;
    for (int i = 1; i <= M.tu; i++) {
	scanf("%d %d %d", &M.data[i].i, &M.data[i].j, &M.data[i].e);
    }
    printf("\nThe matrix is:\n");
    display_matrix_normal(M);

    //矩阵转置
    TSMatrix* pt = &T;
    printf("\nAfter transpose:\n");
    TransposeMatrix(M, pt);
    printf("\n=========\n");
    display_matrix_normal(*pt);
}
