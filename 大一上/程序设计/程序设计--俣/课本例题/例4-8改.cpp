#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int i,sum;
	printf("\nWelcome.\n"
	            "Calculate the result of 1+2+...+100\n\n");
	for(i=1;i<=100;i++)
	sum+=i;
	printf("1+2+...+100=%d\n",sum);
	system("PAUSE");
	return 0;
}
