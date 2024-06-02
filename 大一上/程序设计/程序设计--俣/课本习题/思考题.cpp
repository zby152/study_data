#include<stdio.h>
#include<stdlib.h>
int main()
{
    double fNum;
    int i,j;
    scanf("%lf",&fNum);
    unsigned int *pNum= (unsigned int*) &fNum;
    printf("指向的整数是%x\n",*pNum);
    if(fNum>0)
    printf("符号位是0\n");
    else
    printf("符号位是1\n");
    union a{
    	double fNUM;
    	int a[10];
	}number;
	number.fNUM=fNum;
	for(i=0;i<10;i++)
	{
		printf("%d\n",number.a[i]);
		if(number.a[i]=='e')
		printf("指数位是");
		for(j=i;j<10;j++)
		{
			printf("%d",number.a[j]);
		}
	}
		
}
