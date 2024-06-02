#include<stdio.h>
int main()
{
	short int *p1;
	long int *p3;
	short int scorce[10]={1,2,3,4,5,6,7,8,9};
	p1=scorce;
	p3=(long int*)scorce;
	printf("%p   %p  %p\n",scorce,p1+1,p3+1);
	printf("%d  %d",*p1,*p3);
	return 0;
}
