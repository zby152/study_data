#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n=1,printf=1;
	while(n++<6){
		printf=n*printf;
		printf("%0d %0d\n",n,printf);
	}
	return 0;
}
