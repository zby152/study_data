#include<stdio.h>
#include<stdlib.h>
#define MAX 10
int main(void)
{
	char words[6][16]={"cat","dog","cow","hat","car"};
	char s[MAX];
	char *c;
	int n[6]={0};
	int i,j;
	printf("��������Ҫ�Ƚϵ��ַ���\n");
    gets(s);
	for(i=0;i<5;i++)
	{
		j=0;
		while(s[j]!='\0')
		{
		    c=words[i];
			if(*c==s[j])
			{
				for( ; s[j]!='\0'&&*c!='\0'&&*c==s[j];j++,c++);
				if(*c=='\0')
				{
			    n[i]++;
			    }
			}
			else
			{
			    j++;
			}
		}
	printf("�ؼ�����%s����%d��\n",words[i],n[i]);
	}
system("PAUSE");
return 0;
	
}
