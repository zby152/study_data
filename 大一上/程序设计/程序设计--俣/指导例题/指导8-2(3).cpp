#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(void)
{
	char *p;
	char s[5];
	do{
		gets(s);
		p=s;
		while(*p)    
		    printf("%d",*p++);
	}while(strcmp(s,"done"));
	return 0;
 } 
