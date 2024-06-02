#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int x,*p;
	p=(int *)malloc(10);
	x=10;
	*p=x;
	return 0;
}
