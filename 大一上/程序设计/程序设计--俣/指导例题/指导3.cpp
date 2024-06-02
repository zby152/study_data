#include<stdlib.h>
#include<stdio.h>

int main(void)
{
	int a,b,c,d;
	
	a=12;
	b=45;
	c=++a;
	d=b--;
	
	printf("%d,%d\n",a,b);
	printf("%d,%d\n",c,d);
	
	system("PAUSE");
	return 0;
}
