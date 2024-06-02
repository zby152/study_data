#include<stdio.h>
#include<stdlib.h>
#define MAX 10
int main()
{
	int a[MAX];
	int i,j,t;
	printf("\nÃ°ÅÝÅÅÐò·¨Ê¾Àý\n\n");
	printf("Input 10 numbers:\n");
	for(i=0;i<MAX;i++)
	{
		printf("\t%i>",i+1);
		scanf("%d",&a[i]);
	}
	printf("\n");
	for(j=0;j<MAX-1;j++)
	{
		for(i=MAX-1;i>=0;i--)
		{
			if(a[i]>a[i+1])
			{
				t=a[i];
				a[i]=a[i+1];
				a[i+1]=t;
			}
		}
	}
			printf("The sorted numbers:\n");
			for(i=0;i<MAX;i++)
			    printf("%d\n",a[i]);
	system("PAUSE");
	return 0;
}
