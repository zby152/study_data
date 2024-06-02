#include<stdio.h>
#include<stdlib.h>
#define MAX 10
int main()
{
	int a10,i=0,n;
	int a2[MAX]={0};
	printf("请输入十进制整数\n");
	scanf("%d",&a10);
	do{
		n=a10%2;
		a2[i]=n;
		a10=a10/2;
		i++;
	}while(a10!=0);
	for( ;i>=0;i--)
	    printf("%d",a2[i]);
	system("PAUSE");
	return 0;
}
