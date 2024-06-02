#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int a,b,c,x,y;
	scanf("%d %d %d",&a,&b,&c);
	x=a*b;
	y=x*c;
	printf("a=%d, b=%d, c=%d\n",a,b,c);
	printf("x=%d,y=%d\n",x,y);
	system("PAUSE");
	return 0;
}
