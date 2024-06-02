#include<stdio.h>
#include<stdlib.h>
long f(short int n)
{
	int tmp=1,i;
	if(n>=2)
	{
	for(i=1;i<=n;i++)
	    tmp=tmp*i;
	}
	    return tmp;
}
int main()
{
	short int a;
	long b;
	a=10;
	b=f(a);
	printf("%d!=%ld\n",a,b);
	system("PAUSE");
	return 0;
}
