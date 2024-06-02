#include<stdio.h>
typedef FILE *stream;
int main()
{
	stream my_out;
	my_out=fopen("hhh.txt","w");
	if(my_out==NULL)
	{
		fputs("File can not open!\n",stderr);
		exit(0);
	}
	fputs("The C language",my_out);
	fclose(my_out);
 } 
