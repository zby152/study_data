#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int x;
	printf("请输入分数\n");
	scanf("%d",&x);
	if(x>0,x<=100)
	{
	    if(x>=90)
	        printf("等级为A");
	    if(x>=80&x<=89)
	        printf("等级为B");
	    if(x>=70&x<=79)
	        printf("等级为C");
	    if(x>=60&x<=69)
	        printf("等级为D");
	    if(x<60)
	        printf("等级为E");
}
    else
    printf("错误"); 
	system("PAUSE");
	return 0;
	 
}
