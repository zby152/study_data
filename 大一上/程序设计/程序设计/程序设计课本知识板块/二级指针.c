#include<stdio.h>
#include<stdlib.h>
int main()
{
	int i;
	char **p,*name[2]={"1234567","abcdefgh"};
	
	printf("两个字符串是：\n");
	for(p=name;p<name+2;p++) printf("%s\n",*p);
	
	printf("\n两个字符串的第一个字符是：\n");
	for(i=0,p=name;p<name+2;p++) printf("%c\n",*(*p+i));
	system("PAUSE");
	return 0;
}
