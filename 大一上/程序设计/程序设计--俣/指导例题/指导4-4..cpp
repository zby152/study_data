#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int x,n;
	printf("���������\n");
	scanf("%d",&x);
	if(x>0,x<=100)
	{
	    if(x>=90)
	        n=1;
	    if(x>=80&x<=89)
	        n=2;
	    if(x>=70&x<=79)
	        n=3;
	    if(x>=60&x<=69)
	        n=4;
	    if(x<60)
	        n=5;
	}
	else
	printf("����");
	switch(n)
	{
	case 1: printf("�ȼ�ΪA"); break;
	case 2: printf("�ȼ�ΪB"); break;
	case 3: printf("�ȼ�Ϊc"); break;
	case 4: printf("�ȼ�ΪD"); break;
	case 5: printf("�ȼ�ΪE"); 
}
system("PAUSE");
return 0;
}
	
