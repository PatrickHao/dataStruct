#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* ch;
    int length;
} HString;

int StrAssign(HString* T, char* chars)
{
    if (T->ch)
	free(T->ch);
    char* c = chars;
    int i = 0;
    while (*c) {
	++i;
	++c;
    }
    if (!i) {
	T->ch = NULL;
	T->length = 0;
    } else {
	if (!(T->ch = (char*)malloc(i * sizeof(char))))
	    return 0;
	for (int j = 0; j < i; j++)
	    T->ch[j] = chars[j];
	T->length = i;
    }
    return 1;
}

int StrLength(HString S)
{
    return S.length;
}

int StrCompare(HString S, HString T)
{
    for (int i = 0; i < S.length && i < T.length; i++)
	if (S.ch[i] != T.ch[i])
	    return S.ch[i] - T.ch[i];
    return S.length - T.length;
}

int ClearString(HString* S)
{
    if (S->ch) {
	free(S->ch);
	S->ch = NULL;
    }
    S->length = 0;
    return 1;
}

//连接成新串
int Concat(HString* T, HString S1, HString S2)
{
    if (T->ch)
	free(T->ch);
    if (!(T->ch = (char*)malloc((S1.length + S2.length) * sizeof(char))))
	return 0;
    for (int i = 0; i < S1.length; i++)
	T->ch[i] = S1.ch[i];
    T->length = S1.length + S2.length;
    for (int i = S1.length; i < T->length; i++)
	T->ch[i] = S2.ch[i - S1.length];
    return 1;
}

int SubString(HString* Sub, HString S, int pos, int len)
{
    if(pos<1||pos>S.length||len<0||len>S.length-pos+1)
	return 0;
    if(Sub->ch)
	free(Sub->ch);
    if(!len){
	Sub->ch=NULL;
	Sub->length=0;
    }
    else{
	Sub->ch=(char*)malloc(len*sizeof(char));
	for(int i=0;i<pos;i++)
	    Sub->ch[i]=S.ch[i+pos-1];
	Sub->length=len;
    }
    return 1;
}
