#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	char *p;
	p=(char *)malloc(100);
	gets(p);
	printf("%s",p);
	return 0;
	
}
