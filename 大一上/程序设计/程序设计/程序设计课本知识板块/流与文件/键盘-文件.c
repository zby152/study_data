#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *out;
	char ch;
	
	printf("\n�Ӽ��̶��ַ���д�뵽�ļ���!\n\n");
	
	if((out=fopen("hh.txt","w"))==NULL)
	{
		printf("�򿪵�Ŀ���ļ�����\n");
		exit(1); 
	}
	
	do{
		ch=getchar();
		fputc(ch,out);
	}while(ch!='$');
	fclose(out);
	
	system("PAUSE");
	return 0;
}
