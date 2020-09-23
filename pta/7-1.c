//Maximum Subsequence Sum
#include <stdio.h>
#include <stdlib.h>

int main()
{
    //拿到数据
    int length;
    scanf("%d", &length);

    int* num = (int*)malloc(length * sizeof(int));
    for (int i = 0; i < length; i++)
	scanf("%d", num + i);

    //求最大子列
    int sum_now = 0;
    int sum_max = -1;
    int a, b, len, p;
    len = p = 0;
    a = num[0];
    b = num[length - 1];

    //判断是否为全负
    for (int i = 0; i < length; i++)
	if (num[i] >= 0)
	    p = 1;
    if (p == 1) {
	for (int i = 0; i < length; i++) {
	    len++;
	    sum_now += num[i];
	    if (sum_now > sum_max) {
		sum_max = sum_now;
		b = num[i];
		a = num[i - len + 1];
	    } else if (sum_now < 0) {
		sum_now = 0;
		len = 0;
	    }
	}
	printf("%d %d %d", sum_max, a, b);
	return 0;
    } else {
	printf("0 %d %d", num[0], num[length - 1]);
	return 0;
    }
}
