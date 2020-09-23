#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned int weight;
    unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;
typedef char ** HuffmanCode;

void Select(HuffmanTree HT, int m, int *s1, int *s2) {
    int minTemp = 0;
    for(int i = 1; i <= m; i++) {
        if(HT[i].parent == 0) {
            minTemp = i;
            break;
        }
    }
    for(int i = 1; i <= m; i++) {
        if(HT[i].parent == 0) {
            if(HT[i].weight < HT[minTemp].weight) {
                minTemp = i;
            }
        }
    }
    *s1 = minTemp;
    for(int i = 1; i <= m; i++) {
        if(HT[i].parent == 0 && i != *s1) {
            minTemp = i;
            break;
        }
    }
    for(int i = 1; i <= m; i++) {
        if(HT[i].parent == 0 && i != *s1) {
            if(HT[i].weight < HT[minTemp].weight) {
                minTemp = i;
            }
        } 
    }
    *s2 = minTemp;
}

void HuffmanCoding(HuffmanTree HT, HuffmanCode HC, int *w, int n) {
    if (n <= 1) {
        return;
    }
    int m = 2 * n - 1;
    HuffmanTree p = HT + 1;
    int i = 1;
    while(i <= n) {
        p->weight = *w; 
        p->parent = 0;
        p->lchild = 0;
        p->rchild = 0;
        i++;
        p++;
        w++;
    }
    while(i <= m) {
        p->weight = 0;
        p->parent = 0;
        p->lchild = 0;
        p->rchild = 0;
        i++;
        p++;
    }
    for(int i = n + 1; i <= m; i++) {
        int s1, s2;
        Select(HT, i - 1, &s1, &s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    char *cd = (char *)malloc(n * sizeof(char));
    cd[n - 1] = '\0';
    for(int i = 1; i <= n; i++) {
        int start = n - 1;
        for(int c = i, p = HT[i].parent; p != 0; c = p, p = HT[p].parent) {
            if(HT[p].lchild == c) {
                cd[--start] = '0';
            }
            else {
                cd[--start] = '1';
            }
        }
        HC[i] = (char *)malloc((n - start) * sizeof(char));
        strcpy(HC[i], cd + start);
    }  
    free(cd);
}

int main() {
    int w[] = {5, 2, 3, 1, 1};
    int n = 5;
    HuffmanTree HT = (HuffmanTree)malloc((2 * n) * sizeof(HTNode));
    HuffmanCode HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));
    HuffmanCoding(HT, HC, w, n);
    for(int i = 1; i <= n; i++) {
        printf("%s\n", HC[i]);
    }
    
    return 0;
}