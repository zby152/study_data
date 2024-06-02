#include<stdio.h>
#include<stdlib.h>
typedef FILE *stream;
int main()
{
	stream my_out;
	char ch='Z';
	my_out=fopen("hhh.txt","w");
	if(my_out==NULL){
		printf("File can not open!\n");
		exit(0);
	}
	fputc(ch,my_out);
	fclose(my_out);
}
