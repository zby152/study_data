#include<stdio.h>
#include<stdlib.h>
int main()
{
	int a[10];
	int i,j,t;
	for(i=0;i<10;i++)
	scanf("%d",&a[i]);
	for(i=0;i<10;i+=2)
	for(j=i+2;j<12;j+=2)
		{
	    	if(a[i]>a[j])
			{
	    		t=a[i];
	    		a[i]=a[j];
	    		a[j]=t;
			}
			if(a[i+1]<a[j+1])
			{
			    t=a[i+1];
			    a[i+1]=a[j+1];
			    a[j+1]=t;
			}
		}
		for(i=0;i<10;i++)
		printf("%d\t",a[i]);
		system("PAUSE");
		return 0;
}
