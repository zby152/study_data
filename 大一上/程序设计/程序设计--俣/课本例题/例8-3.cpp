#include<stdio.h>
#include<stdlib.h>
#define SIZE 50
void push(int i);
int pop(void);
int *tos,*p1,stack[SIZE];
int main(void)
{
	int value;
	tos=stack;
	p1=stack;
	do
	{
		printf("����һ������:");
		scanf("%d",&value);
		if(value!=0) push(value);
		else printf("��ջ������%d\n",pop());
	}while(value!=-1);
	system("PAUSE");
	return 0;
}
void push(int i)
{
	p1++;
	if(p1==(tos+SIZE))
	{
		printf("��ջ����\n");
		system("PAUSE");
		exit(1);
	}
	*p1=i;
}
int pop(void)
{
	if(p1==tos)
	{
		printf("��ջ��\n");
		system("PAUSE");
		exit(1);
	}
	p1--;
	return *(p1+1);
}
