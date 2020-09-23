#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100000

typedef struct {
    int data;
    int next;
} Node;

int main()
{
    int position_start;
    int len;
    int k;

    Node* line = (Node*)malloc(MAXSIZE * sizeof(Node));

    //拿到数据
    scanf("%d %d %d", &position_start, &len, &k);

    int b1, b2, b3;

    for (int i = 0; i < len; i++) {
	scanf("%d %d %d", &b1, &b2, &b3);
	line[b1].data = b2;
	line[b1].next = b3;
    }

    //拿到真实的长度
    int real_len = 1;

    int position_now = position_start;

    while (line[position_now].next != -1) {
	position_now = line[position_now].next;
	real_len++;
    }

    //反转节点
    int reverse_time = real_len / k;
    int curent_time = 0;

    int cur = position_start;
    int newHead = -1;
    int sectionHead = -1;
    int sectionTail = -1;
    int prevsectionTail = -1;

    int sectionNum = 0;

    while (curent_time++ < reverse_time) {
	int count = k;
	prevsectionTail = sectionTail;
	sectionTail = cur;
	while (count-- && cur != -1) {
	    int tmp = cur;
	    cur = line[cur].next;
	    line[tmp].next = sectionHead;
	    sectionHead = tmp;
	}
	++sectionNum;

	if (sectionNum == 1) {
	    newHead = sectionHead;
	} else {
	    line[prevsectionTail].next = sectionHead;
	}
    }
    if (real_len % k == 0)
	line[sectionTail].next = -1;
    else
	line[sectionTail].next = cur;

    //输出
    int p = newHead;

    int cnt = 0;
    while (cnt < real_len - 1) {
	printf("%05d %d %05d\n", p, line[p].data, line[p].next);
	p = line[p].next;
	cnt++;
    }
    printf("%05d %d %d\n", p, line[p].data, line[p].next);
    return 0;
}
