#include<stdio.h>
#include<stdlib.h>
#include<math.h>
long int cacseconds(int a,int b,int c)
{
	int a_,b_,result;
	a_=a*3600;
	b_=b*60;
	result=a_+b_+c;
	return result;
}
int main(void)
{
	int a1,a2,a3,b1,b2,b3,x1,x2,result;
	printf("请输入第一个时分秒");
	scanf("%d,%d,%d",&a1,&a2,&a3); 
	printf("请输入第二个时分秒");
	scanf("%d,%d,%d",&b1,&b2,&b3); 
	x1=cacseconds(a1,a2,a3);
	x2=cacseconds(b1,b2,b3);
	result=x1-x2;
	printf("间隔时间是%d",result);
	system("PAUSE");
	return 0;
	
}
