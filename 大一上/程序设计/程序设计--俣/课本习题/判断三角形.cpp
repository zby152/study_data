#include<stdio.h>
#include<stdlib.h>

int main()
{
	int a,b,c;
	printf("�����������ε�����\n");
	scanf("%d%d%d",&a,&b,&c);
	if(a+b>c&&a+c>b&&b+c>a)
	{
		printf("����������\n");
		if(a*a+b*b==c*c)
		    printf("ֱ��������\n");
		if(a*a+b*b>c*c)
		    printf("���������\n");
	    if(a*a+b*b<c*c)
		    printf("�۽�������\n");
		if(a==b&&b==c)
		    printf("�ȱ�������\n");
		else if(a==b||b==c||c==a)
		    printf("����������\n"); 
	}
	else
	printf("������������\n");
	system("PAUSE");
	return 0;
}
