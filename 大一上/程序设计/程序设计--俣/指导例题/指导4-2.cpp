#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int k=1;
	int sum=0;
	do{
		sum=sum+k;
		k++;
	}while(k<=100.0); 
	printf("%d",sum);
	system("PAUSE");
	return 0;
}
