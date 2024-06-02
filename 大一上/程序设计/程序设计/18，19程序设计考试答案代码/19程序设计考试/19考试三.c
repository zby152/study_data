#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void found(char str[]);
int main()
{
	char str[201];
	gets(str);
	while(strcmp(str,"BEGIN")==0){
		found(str);
		printf("%s\n",str);
		gets(str);
	}
	return 0;
}
void found(char str[])
{
	char plain[27]="VWXYZABCDEFGHIJKLMNOPQRSTU";
	char strEnd[201];
	gets(str);
	int t=strlen(str);
	int i,j;
	for(i=0;i<t;i++){
		for(j=0;j<27;j++){
			if(plain[j]==str[i]){
			str[i]=plain[(j+21)%26];
			break;}
		}
	}
	gets(strEnd);
	return;
}
