#include<stdio.h>
#include<stdlib.h>
int main(void)
{
    int left=0,right=0;
 	char c;
	printf("�������ַ���\n");
	while((c=getchar())!=EOF)
	{
	    if(c=='(')
	    left++;
	    else if(c==')')
	    right++;
    }
if(right<left)
    printf("������û�г���������\n");
if(right>left)
    printf("�����ų���������\n");
else if (left==right)
    printf("������������ƥ��\n");
system("PAUSE");
return 0; 
}
