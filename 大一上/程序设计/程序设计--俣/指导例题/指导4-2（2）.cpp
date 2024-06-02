#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int i=1,j=1;
	for( ;j<10;i++)
	{
		if(j>5)break;
		if(j%2!=0)
		{
			j+=3;
			continue; 
		}
		j-=1;
	}
	printf("%d,%d\n",i,j);
	system("PAUSE");
	return 0;
}
