#include<stdio.h>
#include<stdlib.h>
int changenumber(int a)
{
	int b;
    while (a>=1)
    {
	    b=b*10+a%10;
	    a=a/10;
	}
    	return b;
}
int main(void)
{
	int number;
	printf("��������������\n");
	scanf("%d",&number);
	number=changenumber (number);
	printf("ת��������%d",number);
	system("PAUSE");
	return 0;
}

