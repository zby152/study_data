#include<stdio.h>
#include<stdlib.h>
#define MAX 10
int hanshu(int a[],int key)
{
	int mid;
	int start=0;
	int end=MAX-1;
	while(start<=end)
	{
		mid=(start+end)/2;
		if(key>a[mid])   start=mid+1;	
		else if(key<a[mid])	end=mid-1;
		else return mid;
	}
	return -1;
}
int main(void)
{
	int a[MAX];
	int i,x,result;		
	printf("请输入想要查找的数\n");
	scanf("%d",&x);
	printf("请输入有序整型数组的值\n");
	for(i=0;i<MAX;i++)
	{
	scanf(" %d",&a[i]);
}
	result=hanshu(a,x);
	result++;
	if(result!=0)
		printf("找到关键数%d的下标是%d\n",x,result);
	else
	printf("未找到关键数\n");
	system("PAUSE");
	return 0;	
}
