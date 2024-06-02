#include<stdio.h>
#include<stdlib.h>
int main()
{
	short int *p1,score[10]={84,65,77,60,88,86,92,93,70,66};
	long int *p2;
	p1=&score[0];
	p1++;
	p2=(long int *)&score[0];
	p2++;
	printf("%d\n",*p1);
	printf("%d\n",*p2);
	system("PAUSE");
	return 0;
}
