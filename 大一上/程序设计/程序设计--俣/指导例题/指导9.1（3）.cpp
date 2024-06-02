#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	struct {
		int x;
		int y;
	}a[2]={{1,2},{3,4}},*p=a;
	printf("%d,",++p->x);
	printf("%d\n",(++p)->x);
	system("PAUSE");
	return 0;
}
