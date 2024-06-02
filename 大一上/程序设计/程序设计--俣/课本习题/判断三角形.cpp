#include<stdio.h>
#include<stdlib.h>

int main()
{
	int a,b,c;
	printf("请输入三角形的三边\n");
	scanf("%d%d%d",&a,&b,&c);
	if(a+b>c&&a+c>b&&b+c>a)
	{
		printf("构成三角形\n");
		if(a*a+b*b==c*c)
		    printf("直角三角形\n");
		if(a*a+b*b>c*c)
		    printf("锐角三角形\n");
	    if(a*a+b*b<c*c)
		    printf("钝角三角形\n");
		if(a==b&&b==c)
		    printf("等边三角形\n");
		else if(a==b||b==c||c==a)
		    printf("等腰三角形\n"); 
	}
	else
	printf("不构成三角形\n");
	system("PAUSE");
	return 0;
}
