#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int n;
	int m;
	printf("\n欢迎使用13的倍数判断程序\n"); 
	printf("请输入一个整数：");
	scanf("%d",&n);
	m=n%13;
	if(m==0)
	printf("%d是13的倍数\n",n);
	else
	printf("%d不是13的倍数\n",n);
	system("PAUSE");
	return 0;
}
