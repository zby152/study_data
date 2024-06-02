#include<stdlib.h>
#include<stdio.h>

int main(void)
{
	int a,b;
	unsigned int c,d;
	long int e,f;
	a=100;
	b=-100;
	c=a;
	d=b;
	
	printf("%d, %d\n",a,b);
	printf("%u, %u\n",a,b);
	printf("%d, %d\n",c,d);
	printf("%u, %u\n",c,d);
	
	e=50000;
	f=32767;
	c=a=e;
	d=b=f;
	
	printf("%d,%d\n",a,b);
	printf("%u,%u\n",c,d);
	
	system("PAUSE");
	return 0;
}
