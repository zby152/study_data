#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *out;
	char ch;
	
	printf("\n从键盘读字符并写入到文件中!\n\n");
	
	if((out=fopen("hh.txt","w"))==NULL)
	{
		printf("打开的目标文件错误！\n");
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
