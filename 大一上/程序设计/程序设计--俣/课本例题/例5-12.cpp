#include<stdio.h>
#include<stdlib.h>
int main()
{
	void increment(void);
	increment();
	increment();
	increment();
	system("PAUSE");
	return 0;
}
void increment(void)
{
	static int x=0;
	x++;
	printf("%d\n",x);
}
