#include<stdio.h>
#include<stdlib.h>
void reverse(long n)
{
	if(n>=1000)
	reverse(n/1000);
	printf("%d",n%1000);
	putchar(',');
	
}
int main()
{
	long a;
	scanf("%ld",&a);
	reverse(a);
	system("PAUSE");
	return 0;
}
