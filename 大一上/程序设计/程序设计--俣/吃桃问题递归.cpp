#include<stdio.h>
#include<stdlib.h>
int picth(int a)
{
	int tao=1;
	if(a==1)
	    tao=(tao+1)*2;
	else
	    tao=((picth(a-1))+1)*2;
}
int main(void)
{
	int result;
	int a=9;
	result=picth(a);
	printf("¹²Õª%d",result);
	system("PAUSE");
	return 0;
}
