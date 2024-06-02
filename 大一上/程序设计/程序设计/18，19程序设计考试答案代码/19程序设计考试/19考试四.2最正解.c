#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int isValid(char * s);
 
int main()
{
	int t;//判断是否为有效括弧 
	char str[100];//储存用户输入的括弧 
	printf("请输入若干括弧："); 
	gets(str);
	t=isValid(str);
	printf("\n%d",t);
	return 0; 
}
int isValid(char * s){
	int len1=strlen(s),i,j=0;
	char str[len1];
	for(i=0;i<len1;i++){
		if(s[i]!=' '){
			str[j]=s[i];
			j++;
		}
	}
	char str1[strlen(str)];
	if(strlen(str)%2!=0) return 0;
	else{
		i=0;
		j=0;//模拟栈的输入输出 
		while(i<strlen(str)){
			while(str[i]=='('||str[i]=='{'||str[i]=='['){
				str1[j]=str[i];
				j++;
				i++; 
			}
			while(str[i]==')'){
				j--;
				if(j<0) return 0;
				else if(str1[j]=='(') i++;
				else return 0;
			}
			while(str[i]=='}'){
				j--;
				if(j<0) return 0;
				else if(str1[j]=='{') i++;
				else return 0;
			}
			while(str[i]==']'){
				j--;
				if(j<0) return 0;
				else if(str1[j]=='[') i++;
				else return 0;
			}
		}
		if(i==strlen(str)&&j==0) return 1;
		else return 0;
	}
}

