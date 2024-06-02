#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *in,*out;
	char ch;
	
	printf("\n文件复制程序！\n\n");
	
	if((in=fopen("hhh.txt","r"))==NULL){
		printf("打开源文件错误！\n");
		exit(1);
	}
	if((out=fopen("hh.txt","w"))==NULL)
	{
		printf("打开目标文件错误！\n");
		exit(1);
	}
	printf("文件复制中...\n");
	while(!feof(in))
	{
		ch=fgetc(in);
		//if(!feof(in)) 
		putc(ch,out);
	}
	printf("文件复制完成\n");
	fclose(in);
	fclose(out);
	system("PAUSE");
	return 0;
}
