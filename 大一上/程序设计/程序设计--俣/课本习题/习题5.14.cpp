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
		printf("\n ‰»Î");
		scanf("%d",&number);
	}while(number<=0);
	printf("\nΩ·π˚");
	convert(number);
	printf("\n");
	system("PAUSE");
	return 0; 
}
