#include<stdio.h>
#include<stdlib.h>
int max(int a[2][10])
{
	int maxnumber=0;
	int m=0;
	for(m=0;m<9;m++)
	{
		if(a[1][maxnumber]<=a[1][m+1])
		    maxnumber=m+1;
	}
	return maxnumber;
}
int min(int a[2][10])
{
	int minnumber=0;
	int m;
	for(m=0;m<9;m++)
	{
		if(a[1][minnumber]<=a[1][m+1])
		    minnumber=minnumber;
		else
		    minnumber=m+1;
	}
	return minnumber;
}
int mid(int a[2][10])
{
	int midnumber=0;
	int m=0,sum=0,midscore=0;
	int n=0;
	int x,y;
	for(m=0;m<10;m++)
	sum+=a[1][m];
	midscore=sum/10;
	for(n=0;n<9;n++)
	{
		x=a[1][midnumber]-midscore;
		if(x<0)
		x=-x;
		y=a[1][n+1]-midscore;
		if(y<0)
		y=-y;
	if(x>=y)
	    midnumber=n+1;
	}
	return midnumber;
}
int main()
{
	int i,maxn,minn,midn;
    int a[2][10];
	for(i=0;i<10;i++)
	{
		printf("请输入第%d位学生的学号\n",i+1); 
		scanf("%d",&a[0][i]);
	}
    for(i=0;i<10;i++)
    {
    	printf("请输入第%d位学生的成绩\n",i+1);
		scanf(" %d",&a[1][i]); 
	}
	maxn=max(a);
	minn=min(a);	
	midn=mid(a);
	printf("最佳学生成绩为%d,学号为%d\n",a[1][maxn],a[0][maxn]);
	printf("最差学生成绩为%d,学号为%d\n",a[1][minn],a[0][minn]);
	printf("最平均学生成绩为%d,学号为%d\n",a[1][midn],a[0][midn]);
	system("PAUSE");
	return 0;
}
