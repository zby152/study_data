#include<stdio.h>
#include<stdlib.h>
union{
	char ch;
	short int s;
	int i;
	long int b;
}x;
int main(void)
{
	printf("ÇëÊäÈëÒ»¸ö×Ö·û\n");
	scanf("%c",&x.ch);
	printf("ch=%c\n s=%d\n i=%d\n b=%ld\n",x.ch,x.s,x.i,x.b);
	system("PAUSE");
	return 0;
}
