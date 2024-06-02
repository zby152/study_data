#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double distent(double x1,double x2,double y1,double y2)
{
	double s,x;
	s=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
	x= sqrt (s);
}
int main()
{
	double x1,x2,y1,y2,result;
	printf("请输入x1,x2,y1,y2的值\n");
	scanf("%lf%lf%lf%lf",&x1,&x2,&y1,&y2);
	result=distent(x1,x2,y1,y2);
	printf("结果是%lf",result);
	system("PAUSE");
	return 0;
}
