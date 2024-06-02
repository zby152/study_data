#include<stdlib.h>
#include<stdio.h>
#define N 6
struct data{
	int no;
	int num;
};
void sort(struct data x[],int n);
void readData(struct data x[],int n);
int main()
{
	struct data x[N],temp;
	int i,j;
	printf("\n数据排列：输出排序后的数据和原有的序号。\n\n");
	printf("请输入%i个整数: ",N);
	readData(x,N);
	sort(x,N);
	printf("\n原来序号   值\n");
	for(i=0;i<N;i++)
	    printf("%5d%10d\n",x[i].no,x[i].num);
	    return 0;
}
void sort(struct data x[],int n)
{
	int i,j;
	struct data temp;
	for(i=0;i<n-1;i++)
	   for(j=0;j<n-i-1;j++)
	        if(x[j].num>x[j+1].num)
	        {
	            temp=x[j];
	       	    x[j]=x[j+1];
	       	    x[j+1]=temp;
		    }
}
void readData(struct data x[],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		scanf(" %d",&x[i].num);
		x[i].no=i+1;
	}
}
