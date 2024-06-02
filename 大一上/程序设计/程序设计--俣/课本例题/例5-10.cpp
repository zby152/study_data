#include<stdio.h>
#include<stdlib.h>
int i;
int main()
{
	void prt();
	for(i=0;i<5;i++)
	prt();
	system("PAUSE");
	return 0;
}
void prt()
{
	for(i=0;i<5;i++)
	printf("%c",'*');
	printf("\n");
}
