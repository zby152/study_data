#include<stdio.h>
#include<stdlib.h>
long fib(long n)
{
	if(n>=3)
    {
	printf("形参是%d\n",n);
	    return (fib(n-1)+fib(n-2));
	}
	else
	{
	printf("\n形参是2\n形参是1"); 
	    return 1;
	}
}
int main()
{
	int n;
	long result;
	printf("请输入n的数值\n");
	scanf("%d",&n);
	result=fib(n);
	printf("结果是%8ld\n",result);
	system("PAUSE");
	return 0;
}
