#include<stdio.h>
#include<stdlib.h>
#define MAX 10
//查找数组最小值 
int hanshu(int a[MAX],int n)
{
    if(n==1)
    return a[0];
    int tem=hanshu(a,n-1);
    if (a[0]<tem)
    return a[0];
    else
    return tem;
    
}
int main(void)
{
	int a[MAX];
	int n,x,i;
		printf("请输入数组个数\n");
	scanf("%d",&n);
	printf("请输入数组值\n");
	for(i=0;i<n;i++)
	{
	    scanf("%d",&a[i]);
	}
	x=hanshu(a,n);
	printf("数组的最小值是%d",x);
    system("PAUSE");
    return 0;
}
