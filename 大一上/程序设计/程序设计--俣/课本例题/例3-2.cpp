#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main(void)
{
	char ch;
	printf("Enter a text:\n");
	ch=getchar();
	if(islower(ch))
	    ch=toupper(ch);
	putchar(ch);
	system("PAUSE");
	return 0;
}
