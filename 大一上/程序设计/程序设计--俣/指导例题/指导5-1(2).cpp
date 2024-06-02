#include<stdio.h>
#include<stdlib.h>
#include<math.h>
void printstar()
{
	printf("****************\n");
}
void printmessage()
{
	printf("The result is ");
}

int main(void)
{
	double x;
	printf("Please input a number:");
	scanf("%lf",&x);
	printstar();
	printmessage();
	printf("%.4f\n",sqrt(fabs(x)));
	printstar();
	system("PAUSE");
	return 0;
}

