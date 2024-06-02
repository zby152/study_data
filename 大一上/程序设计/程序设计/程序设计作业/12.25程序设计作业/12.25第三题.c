#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *in;
	char ch;
	int i=1;
	in=fopen("mylife.txt","r");
	printf("%d ",i);
	while(!feof(in)){
		ch=fgetc(in);
		if(ch=='\n'){
		i++;
		printf("%c",ch);
		printf("%d ",i);
		}
		else printf("%c",ch);
	}
	return 0;
 } 
