#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int n;
	int m;
	printf("\n��ӭʹ��13�ı����жϳ���\n"); 
	printf("������һ��������");
	scanf("%d",&n);
	m=n%13;
	if(m==0)
	printf("%d��13�ı���\n",n);
	else
	printf("%d����13�ı���\n",n);
	system("PAUSE");
	return 0;
}
