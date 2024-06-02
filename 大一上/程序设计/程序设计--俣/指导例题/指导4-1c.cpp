#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int y=-1;
	int x;
	scanf("%d",&x);
	if(x!=0)
	    if(x>0)
	        y=1;
	    else
	        y=0;
	printf("y=%d",y); 
}
