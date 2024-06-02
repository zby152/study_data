#include<stdio.h>
#include<stdlib.h>
#define MAXa 6
#define MAXb 4
void paixu(int a[],int b[],int c[])
{
	int i=0,k=0,n=0;
	while(i<MAXa&&k<MAXb)
	{
	if(a[i]>b[k])
	{
	    c[n]=b[k];
	    k++;
	    n++;
	}
	else
	{
	    c[n]=a[i];
	    i++;
	    n++;
	}
}
	while(i<MAXa)
	{
		c[n]=a[i];
		n++;
		i++;
	}
	while(k<MAXb)
	{
		c[n]=b[k];
		n++;
		k++;
	}
 } 
int main(void)
{
	int a[MAXa],b[MAXb],c[MAXa+MAXb];
	int n,k,i;
	printf("请输入a数组的值共%d个\n",MAXa);
	for(i=0;i<MAXa;i++)
	{
	    scanf("%d",&a[i]);
	    fflush(stdin);
	}
	printf("请输入b数组的值共%d个\n",MAXb);
	for(k=0;k<MAXb;k++)
	{
	    scanf("%d",&b[k]);
	    fflush(stdin);
	}
	paixu(a,b,c);
	printf("排序的结果是\n");
	for(n=0;n<MAXa+MAXb;n++)
	    printf("%4d\n",c[n]);
	system("PAUSE");
	return 0; 
}
