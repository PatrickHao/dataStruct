#include <stdio.h>
#include "stack.h"

//栈的应用    
//进制转换    
void conversion()    
{    
  SqStack* s = (SqStack*)malloc(sizeof(SqStack));    
    InitStack(s);    
    SElemType* N=(SElemType*)malloc(sizeof(SElemType));    
    scanf("%d",N);    
    while(*N){    
        Push(s,*N%8);    
        *N=*N/8;    
    }    
    while(!StackEmpty(*s)){    
        SElemType* e=(SElemType*)malloc(sizeof(SElemType));    
        Pop(s,e);    
        printf("%d",*e);    
    }    
}

int main(){
    
}
