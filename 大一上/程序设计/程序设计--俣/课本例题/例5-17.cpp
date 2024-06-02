#include<stdio.h>
#include<stdlib.h>
#define R 0
int main(void)
{
	float c,r,s;
	printf("input a number: ");
	scanf("%f",&c);
	#if R
	r=3.14159*c*c;
	printf("area of round is:%f\n",r);
	#else
	s=c*c;
	printf("area of square is:%f\n",s);
	#endif
	system("PAUSE");
	return 0;
}
