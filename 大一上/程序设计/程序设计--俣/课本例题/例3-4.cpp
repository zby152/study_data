#include<stdio.h>
#include<stdlib.h>
#define GRAVITY 9.81
int main(void)
{
	double t,y,v;
	printf("\n\nWelcome.\n"
	            "Calculate the height from which a grapefruit fell\n"
				"given the number of seconds that it was falling.\n\n");
	printf("Input the seconds:"); 
	scanf("%lg",&t);
	y=.5*GRAVITY*t*t;
	v=GRAVITY*t;
	printf("Time of fall=%g seconds\n",t);
	printf("Distance of fall=%g meters\n",y);
	printf("Velocity of fall=%g m/s\n",v);
	system("PAUSE");
	return 0;				 
}
