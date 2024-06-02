#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int a,b,c,x,y;
	scanf("%d,%d,%d",a,b,c);
	x=a*b;
	y=x*c;
	printf("%d %d %d",a,b,c);
	printf("x=%f\n",x,"y=%f\n",y);
}
