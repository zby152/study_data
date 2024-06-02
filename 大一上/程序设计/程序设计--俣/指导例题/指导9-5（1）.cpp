#include<stdio.h>
#include<stdlib.h>
typedef struct node{
	int x;
	int y;
}POINT;
int inCircle(POINT point,POINT circle,int r)
{
	int d;
	d=(point.x-circle.x)*(point.x-circle.x)+(point.y-circle.y)*(point.y-circle.y);
	if(d<(r*r))
	return 1;
	else
	return 0;
}
int main()
{
	int w,r;
	POINT point1,circle1;
	printf("请输入点的坐标\n");
	scanf("%d%d",&point1.x,&point1.y);
	printf("请输入圆心位置与半径\n");
	scanf(" %d%d%d",&circle1.x,&circle1.y,&r);
	w=inCircle(point1,circle1,r);
	switch(w)
	{
		case 0: printf("点不在圆内");break;
		case 1: printf("点在圆内"); 
	}
	system("PAUSE");
	return 0;
}
