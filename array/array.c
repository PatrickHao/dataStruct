#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_ARRAY_DIM 8
#define ERROR 0
#define OK 1
typedef int Elemtype;
typedef struct {
	Elemtype *base;
	int dim;
	int *bounds;
	int *constants;
} Array;

//dim后的省略号表示参数个数未知
int InitArray(Array *A,int dim,...) {
	if(dim < 1 || dim > MAX_ARRAY_DIM)
		return ERROR;
	A->dim = dim;
	A->bounds = (int*)malloc(dim * sizeof(int));
	if(!A->bounds)
		return ERROR;
	//元素总数
	int elemtotal = 1;
	va_list ap;
	va_start(ap,dim);//dim是传给函数的最后一个已知的固定参数
	for(int i = 0;i < dim;i++) {
		A->bounds[i]=va_arg(ap,int);//检索参数列表中类型为int的下一个元素
		if(A->bounds[i]<0)
			return ERROR;
		elemtotal *= A->bounds[i];
	}
	va_end(ap);
	A->base = (Elemtype*)malloc(elemtotal * sizeof(Elemtype));
	if(!A->base)
		return ERROR;
	A->constants = (int*)malloc(dim * sizeof(int));
	if(!A->constants)
		return ERROR;
	//L=1,指针的增减以元素为单位
	A->constants[dim-1] = 1;
	for(int i = dim - 2;i >= 0;i--)
		A->constants[i] = A->bounds[i+1] * A->constants[i+1];
	return OK;
}

int DestoryArray(Array *A) {
	if(!A->base)
		return ERROR;
	free(A->base);
	A->base = NULL;
	if(!A->bounds)
		return ERROR;
	free(A->bounds);
	A->bounds = NULL;
	if(!A->constants)
		return ERROR;
	free(A->constants);
	A->constants = NULL;
	return OK;
}

int Locate(Array A,va_list ap,int *off) {
	//off为该元素在A中的相对地址
	*off = 0;
	for(int i = 0;i < A.dim;i++) {
		int ind = va_arg(ap,int);
		if(ind < 0 || ind > A.bounds[i])
			return ERROR;
		off += A.constants[i] * ind;
	}
	return OK;
}

int Value(Array A,Elemtype *e,...) {
	va_list ap;
	va_start(ap,e);
	int result = 0;
	int *off = (int*)malloc(sizeof(int));
	if((result = Locate(A,ap,off)) == 0)
			return result;
	*e = *(A.base + (*off));
	return OK;
}

//赋值
int Assign(Array *A,Elemtype e,...) {
	va_list ap;
	va_start(ap,e);
	int result = 0;
	int *off = (int*)malloc(sizeof(int));
	if((result = Locate(*A,ap,off)) ==0)
		return result;
	*(A->base + (*off)) = e;
	return OK;
}

int main() {
	Array a;
	Array *pa = &a;
	int* ret = (int*)malloc(sizeof(int));
	InitArray(pa,2,3,3);
	Assign(pa,9,1,1);
	Value(a,ret,1,1);


	printf("%d\n",*ret);
	
	return 0;
}
