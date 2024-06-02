#include<stdio.h>
typedef FILE *stream;
int main()
{
	stream my_in;
	char ch;
	my_in=fopen("hhh.txt","r");
	if(my_in==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	ch=fgetc(my_in);
	printf("%c",ch);
	fclose(my_in);
}
