#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int x,n;
	printf("请输入分数\n");
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
	printf("错误");
	switch(n)
	{
	case 1: printf("等级为A"); break;
	case 2: printf("等级为B"); break;
	case 3: printf("等级为c"); break;
	case 4: printf("等级为D"); break;
	case 5: printf("等级为E"); 
}
system("PAUSE");
return 0;
}
	
