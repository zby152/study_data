#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100
//����ת�� 
char resever(char array[])
{
	int i,j;
	char a;
	for(i=0,j=strlen(array)-1;i<j;i++,j--)
	{
		a=array[i];
		array[i]=array[j];
		array[j]=a;
	}
}
void change(long int numbera,int digit,char numberb[])
{

	int b,i=0;
	while(numbera)
	{
		b=numbera%digit;
		if(b>9)
		numberb[i]='A'+b-10;	
		else
		numberb[i]='0'+b;
		i++;
		numbera=numbera/digit;
	}
	numberb[i]='\0';
	resever(numberb);
}
int main(void)
{
	long int numbera;
	int digit;
	char numberb[MAX];
	printf("��������Ҫת����ʮ����������Ҫת���Ľ���\n");
	scanf("%ld,%d",&numbera,&digit);
	change(numbera,digit,numberb);
	printf("%ldת��Ϊ%d���ƽ����%s",numbera,digit,numberb);
	system("PAUSE");
	return 0;
}
