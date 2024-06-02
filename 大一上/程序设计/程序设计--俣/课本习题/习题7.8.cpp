#include<stdio.h>
#include<stdlib.h>
int main(void)
{
    int left=0,right=0;
 	char c;
	printf("ÇëÊäÈë×Ö·û´®\n");
	while((c=getchar())!=EOF)
	{
	    if(c=='(')
	    left++;
	    else if(c==')')
	    right++;
    }
if(right<left)
    printf("ÓÒÀ¨ºÅÃ»ÓĞ³¬¹ı×óÀ¨ºÅ\n");
if(right>left)
    printf("ÓÒÀ¨ºÅ³¬¹ı×óÀ¨ºÅ\n");
else if (left==right)
    printf("×óÓÒÀ¨ºÅÊıÏàÆ¥Åä\n");
system("PAUSE");
return 0; 
}
