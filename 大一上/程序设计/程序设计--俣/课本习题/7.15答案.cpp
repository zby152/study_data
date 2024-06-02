#include<stdio.h>
#include<stdlib.h>
#define MAX 81
char words[][MAX]={"elapse","elucidate","elude","embody","embrace"};
int main(void)
{
	char s[MAX],*w;
	int i,j,n[5]={0};
	printf("输入一行字符：\n");
	gets(s);
	for(i=0;i<5;i++)
	{
		j=0;
		while(s[j]!='\0')
		{
			w=words[i];
			if(*w==s[j])
			{
				for( ;s[j]!='\0'&&*w!='\0'&&*w==s[j];j++,w++);
				if(*w=='\0')
				{
					n[i]++;
				}
			}
			else
			{
				j++;
			}
		}
		printf("相匹配的单词%s出现的个数是%d\n\n",words[i],n[i]);
	}
}
