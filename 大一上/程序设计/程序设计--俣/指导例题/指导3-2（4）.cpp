#include<stdio.h>
#include<stdlib.h>
int max(int x,int y,int z)
{
	int c;
	c=(x>y)?x:y;
	c=(c>z)?c:z;
	return c;
}

int min(int x,int y,int z)
{
	int c;
	c=(x<y)?x:y;
	c=(c<z)?c:z;
	return c;
}
int main(void)
{
	int x1,x3,x4,x5,a,b,c;
	float x2;
	printf("��������������\n");
	scanf("%d,%d,%d",&a,&b,&c);
	x1=a+b+c;
	x2=(a+b+c)/3;
	x3=a*b*c;
	x4=min(a,b,c);
	x5=max(a,b,c);
	printf("����%d\n",x1);
	printf("ƽ��ֵ��%f\n",x2);
	printf("�˻���%d\n",x3);
	printf("��Сֵ��%d\n",x4);
	printf("���ֵ��%d\n",x5);
	system("PAUSE");
	return 0;
}
