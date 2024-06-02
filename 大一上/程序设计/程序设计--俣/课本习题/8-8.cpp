#include<stdio.h>
#include<stdlib.h>
#define MAX 6
//替换字符 
int substitute(char x1,char x2,char *a)
{
	int i=0,n=0;
    while(a[i]!='\0')
    {
		if(a[i]==x1)
		{
			n++;
		    a[i]=x2;
		}
	    i++;
    }
	return n;
}
int main(void)
{
	char a[MAX];
	char x1,x2;
	int j,i,n;
	printf("请输入想要替换的字符\n");
	scanf("%c%c",&x1,&x2);
	printf("请输入字符串\n");
	for(j=0;j<MAX;j++)
	    scanf(" %c",&a[j]);
	n=substitute(x1,x2,a);
	printf("结果是\n");
	for(i=0;a[i]!='\0';i++)
	printf("%c",a[i]);
	system("PAUSE");
	return 0;
}
