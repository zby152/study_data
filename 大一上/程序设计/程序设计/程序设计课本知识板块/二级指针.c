#include<stdio.h>
#include<stdlib.h>
int main()
{
	int i;
	char **p,*name[2]={"1234567","abcdefgh"};
	
	printf("�����ַ����ǣ�\n");
	for(p=name;p<name+2;p++) printf("%s\n",*p);
	
	printf("\n�����ַ����ĵ�һ���ַ��ǣ�\n");
	for(i=0,p=name;p<name+2;p++) printf("%c\n",*(*p+i));
	system("PAUSE");
	return 0;
}
