#include<stdio.h>
#include<stdlib.h>
int main()
{
	char str[10];
	char letters[10];
	fgets(str,10,stdin);
	fputs(str,stdout);
	fgets(letters,10,stdin);
	fputs(letters,stdout);
	return 0;
 } 
