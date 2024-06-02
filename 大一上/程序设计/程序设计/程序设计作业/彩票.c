#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	int*p,*q;
	int i,k,sum=0;
	q=(int*)malloc(6*sizeof(int));
	p=(int*)malloc(6*sizeof(int));
	printf("***欢迎来到彩票程序***\n");
	srand((unsigned)time(NULL));
	printf("下面是全部中奖数字：\n");
	for(i=0;i<6;i++)
	{
		p[i]=rand()%10;
		printf("%d\t",p[i]);
	}
	printf("\n请输入您的数字：\n");
	for(i=0;i<6;i++)
	{
		scanf("%d",&q[i]);
	}
	printf("下面输出您的中奖数字：\n"); 
	for(i=0;i<6;i++)
	{
		if(p[i]==q[i]) 
		{
		printf("%d\t",q[i]);
		sum++;
		}
	}
	printf("共计%d个",sum);
	free(p);
	free(q);
	return 0;
}
