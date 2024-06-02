#include<stdio.h>
#include<stdlib.h>
#difine MAX 81
int main(void)
{
	char word[][MAX]={"apple","banana","pitch","hose","cat"};
	char s[MAX];
	int i,n[MAX];
	printf("请输入想要判断的字符串\n");
	gets(s);
	for(i=1;i<=5;i++)
	{
		j=0;
		char w;
		while(s[j]!='\0')
		{
		    w=word[i];
		    if(w==s[j])
		        n[i]++;
		    else
		        j++
		}
	}
}
