#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int x;
	int a,b,c,d,n; 
	printf("请输入一个不大于4位的正整数：");
	scanf("%d",&x);
	if(x>999)
	    n=4;
	else if(x>99)
	    n=3;
	else if(x>9)
	    n=2;
	else
	   n=1;
	printf("位数是%d\n",n);
	a=x/1000;
	b=(x-a*1000)/100;
	c=(x-a*1000-b*100)/10;
	d=x%10;
	switch(n)
	{
		case 4: printf("%d*%d*%d*%d=%d\n",a,b,c,d,a*b*c*d);break;
		case 3: printf("%d*%d*%d=%d\n",b,c,d,b*c*d);break;
		case 2: printf("%d*%d=%d\n",c,d,c*d);break;
		default: printf("%d=%d\n",d,d);
	}
	system("PAUSE");
	return 0;
}
