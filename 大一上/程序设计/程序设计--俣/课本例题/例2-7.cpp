#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	short int a,b;
	
	a=9;
	b=++a;
	printf("(1)a=%d***b=%d\n",a,b);
	
	a=9;
	b=a++;
	printf("(2)a=%d***b=d\n",a,b);
	
	system("PAUSE");
	return 0;
 } 
