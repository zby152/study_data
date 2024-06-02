#include<stdio.h>
#include<stdlib.h>
int s=0;
int add(int a);

int main(void)
{
	int i,sum=0;
	for(i=1;i<=5;i++)
	{
	sum=add(i);
    }
	printf("sum=%d\n",sum);
	system("PAUSE");
	return 0;
}
int add(int a)
{
	s=s+a;
	return s;
}
