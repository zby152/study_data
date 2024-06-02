#include<stdio.h>
#include<stdlib.h>
void reverse(long n)
{
	int i,a[10]={0}; 
	for(i=0;n>=1;i++)
	{
	a[i]=n%1000;
	n=n/1000;
    }
    for(; i>0;i--)
    {
	printf("%d",a[i-1]);
		putchar(',');
	}
}
int main()
{
	long a,b,i;
	scanf("%ld",&a);
	reverse(a);
	system("PAUSE");
	return 0;
}
