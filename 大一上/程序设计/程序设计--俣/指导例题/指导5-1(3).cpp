#include<stdio.h>
#include<stdlib.h>
int fat(int n)
{
	static int f=1;
	f=f*n-1;
	return(f);
}
int main(void)
{
	int i;
	for(i=1;i<=5;++i)
	printf("%d\t",fat(i));
	system("PAUSE");
	return 0;
}
