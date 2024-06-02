#include<stdio.h>
#include<stdlib.h>
#define SIZE 1000
#define PWIDTH 10
void initialArray(short int sieve[],int s);
void prime(short int sieve[],int s);
void printArray(short int sieve[],int s);
int main()
{
	short int sieve[SIZE];
	initialArray(sieve,SIZE);
	printf("\n筛法求素数\n\n");
	printf("1到之间的素数包括:\n");
	prime(sieve,SIZE);
	printf("\n\n");
	printArray(sieve,SIZE);
	printf("\n\n");
	system("PAUSE");
	return 0;
}
void initialArray(short int sieve[],int s)
{
	int k;
	for(k=0;k<s;k++)
	sieve[k]=0;
}
void prime(short int sieve[],int s)
{
	int i,n;
	sieve[0]=1;
	for(n=2;n<=s;n++)
	    if(sieve[n-1]==0)
	        for(i=2*n;i<=s;i+=n)
	            sieve[i-1]=1;
}
void printArray(short int sieve[],int s)
{
	int n,printcol=0;
	for(n=1;n<=s;n++)
	    if(sieve[n-1]==0)
	    {
	    	printf("%5d",n);
	    	if(++printcol>=PWIDTH)
	    	{
	    		putchar('\n');
	    		printcol=0;
			}
		}
}
