#include<stdio.h>
#include<stdlib.h>
char*getWord(char c);
int main()
{
	char input;
	printf("Please input a charactar:");
	input=getchar();
	printf("%c\n",input);
	printf("%s",getWord(input));
	getchar();
	return 0;
}
char *getWord(char c)
{
	switch(c){
		case'A':return"Apple";
		case'B':return"Banana";
		case'C':return"Cat";
		case'D':return"Dog";
		default:return"None";
	}
}
