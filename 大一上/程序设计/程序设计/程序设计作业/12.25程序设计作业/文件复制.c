#include<stdio.h>
#include<stdlib.h>
int main(int argc,char*argv[])
{
	FILE *in,*out;
	char ch;
	printf("�ļ����ƣ�\n");
	if(argc!=3){
		printf("�����и�ʽ����\n");
		exit(1);
	}
	
	if((in=fopen(argv[1],"r"))==NULL){
		printf("��Դ�ļ�����\n");
		exit(1);
	}
	if((out=fopen(argv[2],"w"))==NULL){
		printf("��Դ�ļ�����\n");
		exit(1);
	}
	printf("�ļ�������...\n");
	while(!feof(in)){
		ch=fgetc(in);
		if(!feof(in)) fputc(ch,out);
	}
	printf("�ļ�������ɣ�\n");
	fclose(in);
	fclose(out);
	system("PAUSE");
	return 0;
}
