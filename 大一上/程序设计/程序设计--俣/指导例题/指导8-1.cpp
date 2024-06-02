#include<stdio.h>
#include<stdlib.h>
void swap(int *pa,int *pb)
{
	int p;
    p=*pa;
	*pa=*pb;
	*pb=p;
}
int main(void)
{
	int a,b;
	scanf("%d %d",&a,&b);
	swap(&a,&b);
	printf("a=%d,b=%d\n",a,b);
	system("PAUSE");
	return 0;
}
