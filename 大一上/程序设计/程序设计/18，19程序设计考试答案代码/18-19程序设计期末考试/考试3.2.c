#include<stdio.h>
#include<stdlib.h>
#define STR_LEN 80
#include<string.h>
int main()
{
	char str[STR_LEN+1];
	int nLetter=0,nDigit=0,nSpace=0,nOthers=0;
	
	printf("Please input a string:");
	gets(str);
	int i;
	for(i=0;i<strlen(str);i++)
	{
		if((str[i]>='a'&&str[i]<='z'||(str[i]>='A'&&str[i]<='Z')))
		nLetter++;
		else if(str[i]>=48&&str[i]<=57)
		nDigit++;
		else if(str[i]==' ')
		nSpace++;
		else
		nOthers++;
	}
	printf("English character:%d\n",nLetter);
	printf("Digit character:%d\n",nDigit);
	printf("Space character:%d\n",nSpace);
	printf("Other character:%d\n",nOthers);
	
	return 0;
 } 
