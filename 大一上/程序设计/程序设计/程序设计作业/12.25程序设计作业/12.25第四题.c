#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *out,*in;
	out=fopen("upperstr.txt","w");
	char ch;
	int n,i=0;
	printf("请输入要输入的行数：");
	scanf("%d",&n); 
	getchar();
	do{
		ch=getchar();
		fputc(ch,out);
		if(ch=='\n') i++;
	}while(i<n);
	fclose(out);
	in=fopen("upperstr.txt","r");
	while(!feof(in)){
		ch=fgetc(in);
		if(ch>='a'&&ch<='z') ch=ch-32;
		printf("%c",ch);
	}
	fclose(in);
	return 0;
}
