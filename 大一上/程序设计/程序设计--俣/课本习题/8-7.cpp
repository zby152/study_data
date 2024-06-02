#include<stdio.h>
#include<stdlib.h>
#define MAX 6
//计算浮点数组中正数总和和负数总和及个数并用函数返回四个变量 
void hanshu(double *a,int i,int *n1,int *n2,double *sum1,double *sum2);
int main(void)
{
	int i,n1,n2;
	double a[MAX];
	double sum1,sum2;
	printf("请输入浮点型数组a\n");
	for(i=0;i<MAX;i++)
	    scanf("%lf",&a[i]);
	hanshu(a,i,&n1,&n2,&sum1,&sum2);
	printf("所有正数总和是%lf\n",sum1);
	printf("正数的个数是%d\n",n1);
	printf("所有负数的和是%lf\n",sum2);
	printf("负数的个数是%d\n",n2);
	system("PAUSE");
	return 0;
}
void hanshu(double *a,int i,int *n1,int *n2,double *sum1,double *sum2)
{
	*n1=*n2=0;
	*sum1=*sum2=0;
	for(i=0;i<MAX;i++)
	{
		if(a[i]>0)
		{
			(*n1)++;
			*sum1=*sum1+a[i];
		}
		else
		{
			(*n2)++;
			*sum2=*sum2+a[i];
		}
	}
}
