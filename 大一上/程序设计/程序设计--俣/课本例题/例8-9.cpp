#include<stdio.h>
#include<stdlib.h>
#define CHOICES 6
int menu(char title[],int max,char *menu_list[]);
int main()
{
	char *greeting = "��ӭ���Ĺ��٣����ǽ����ر��ṩ:";
	char *flavor[CHOICES]={"Empty","���","�ɿ���","ţ��","��Ƥ","����"};
	double price[CHOICES]={0.00,1.50,1.80,1.20,2.00,1.80};
	int choice;
	choice=menu(greeting,CHOICES,flavor);
	printf("\n��������ǣ�%s ��ζ�ı�����\n�۸�%.2f Ԫ\n",flavor[choice],price[choice]);
	puts("\nлл���Ĺ��٣���ӭ�´�����\n");
	system("PAUSE");
	return 0;
}
int menu(char title[],int max,char *menu_list[])
{
	int choice;
	int n=0;
	printf("\n%s\n",title);
	for(n=0;n<max;++n)
	    printf("\t%i.%s\n",n,menu_list[n]);
	    printf("����ѡ��:");
	    for( ; ; )
	    {
	    	scanf("%i",&choice);
	    	if(choice>=0&&choice<max)
	    	    break;
	    	printf("����0��%i֮��ѡ��:",max-1);
		}
		return choice;
}
