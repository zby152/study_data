#include<stdlib.h>
#include<stdio.h>
int main()
{
	int ar[10]={11,13,15,17,19,21,23,25,27,29};
	int *pt;
	int **ptt;
	pt=ar;
	ptt=&pt;
	printf("%p\n",ar[0]);
	printf("%p\n",ptt);
	printf("%p\n",pt);
	printf("%d\n",*pt+3);
	printf("%d\n",*pt);
	printf("%d\n",pt[3]);
	printf("%d\n",&*pt);
	printf("%d\n",*(pt+3));
	printf("%d\n",*pt++);
	printf("%d\n",*(pt++));
	printf("%d\n",(*pt)++);
	system("PAUSE");
	return 0;
 } 
