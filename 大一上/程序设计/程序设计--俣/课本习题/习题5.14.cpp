#include<stdio.h>
#include<stdlib.h>
void convert(int n)
{
	int i;
	if((i=n/7)!=0) 
	convert(i);
	putchar(n%7+'0');
}
int main()
{
	int number;
	do{
		printf("\n����");
		scanf("%d",&number);
	}while(number<=0);
	printf("\n���");
	convert(number);
	printf("\n");
	system("PAUSE");
	return 0; 
}
