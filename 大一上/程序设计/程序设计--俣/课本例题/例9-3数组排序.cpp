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
	printf("\n�������У�������������ݺ�ԭ�е���š�\n\n");
	printf("������%i������: ",N);
	readData(x,N);
	sort(x,N);
	printf("\nԭ�����   ֵ\n");
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
