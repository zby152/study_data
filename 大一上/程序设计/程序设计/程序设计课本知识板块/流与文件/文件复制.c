#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *in,*out;
	char ch;
	
	printf("\n�ļ����Ƴ���\n\n");
	
	if((in=fopen("hhh.txt","r"))==NULL){
		printf("��Դ�ļ�����\n");
		exit(1);
	}
	if((out=fopen("hh.txt","w"))==NULL)
	{
		printf("��Ŀ���ļ�����\n");
		exit(1);
	}
	printf("�ļ�������...\n");
	while(!feof(in))
	{
		ch=fgetc(in);
		//if(!feof(in)) 
		putc(ch,out);
	}
	printf("�ļ��������\n");
	fclose(in);
	fclose(out);
	system("PAUSE");
	return 0;
}
