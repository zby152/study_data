#include<stdio.h>
#include<stdlib.h>
int main(int argc,char*argv[])
{
	FILE *in,*out;
	char ch;
	printf("文件复制！\n");
	if(argc!=3){
		printf("命令行格式错误！\n");
		exit(1);
	}
	
	if((in=fopen(argv[1],"r"))==NULL){
		printf("打开源文件错误！\n");
		exit(1);
	}
	if((out=fopen(argv[2],"w"))==NULL){
		printf("打开源文件错误！\n");
		exit(1);
	}
	printf("文件复制中...\n");
	while(!feof(in)){
		ch=fgetc(in);
		if(!feof(in)) fputc(ch,out);
	}
	printf("文件复制完成！\n");
	fclose(in);
	fclose(out);
	system("PAUSE");
	return 0;
}
