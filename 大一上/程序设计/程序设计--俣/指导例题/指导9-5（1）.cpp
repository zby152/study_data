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
	printf("������������\n");
	scanf("%d%d",&point1.x,&point1.y);
	printf("������Բ��λ����뾶\n");
	scanf(" %d%d%d",&circle1.x,&circle1.y,&r);
	w=inCircle(point1,circle1,r);
	switch(w)
	{
		case 0: printf("�㲻��Բ��");break;
		case 1: printf("����Բ��"); 
	}
	system("PAUSE");
	return 0;
}
