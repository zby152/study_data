#include<stdio.h>
#include<stdlib.h>
long fib(long n)
{
	if(n>=3)
    {
	printf("�β���%d\n",n);
	    return (fib(n-1)+fib(n-2));
	}
	else
	{
	printf("\n�β���2\n�β���1"); 
	    return 1;
	}
}
int main()
{
	int n;
	long result;
	printf("������n����ֵ\n");
	scanf("%d",&n);
	result=fib(n);
	printf("�����%8ld\n",result);
	system("PAUSE");
	return 0;
}
