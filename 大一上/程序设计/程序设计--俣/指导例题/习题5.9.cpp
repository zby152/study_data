#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int flip()
{
	int randnum;
	randnum=rand();
	if(randnum%2==0)
	    return 1;
	else
	    return 0;
}
int main()
{
	int i,n,zheng,fan;
	time_t t;
	srand ((unsigned int)time(&t));
	for(i=1;i<=100;i++)
	{
	n=flip();
	    if(n==1)
	    {
	    printf("����"); 
	    zheng++;
	}
	    else
	    {
	    printf("����"); 
	    fan++;
	}
	}
	printf("\n���泯�ϵĴ�����%d\n",zheng);
	printf("\n���泯�ϵĴ�����%d\n",fan);
	system("PAUSE");
	return 0;
}
