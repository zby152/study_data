#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int isValid(char * s)
{
	char a[99];
	int t1=strlen(s),i,j=0;
	char str[t1];
	for(i=0;i<t1;i++){
		if(s[i]!=' '){
			str[j]=s[i];
			j++;
		}
	}
	int t2=strlen(str);
	j=0;
	for(i=0;i<t2;i++)
	{
		if(str[i]=='('||str[i]=='{'||str[i]=='[')
		{
			a[j]=str[i];
			j++;
		}
		else if(str[i]==')'){
			j--;
			if(a[j]!='(') return 0;  
		}
		else if(str[i]==']'){
			j--;
			if(a[j]!='[') return 0;
		}
		else if(str[i]=='}'){
			j--;
			if(a[j]!='{') return 0; 
		}
	}
	if(j==0) return 1;
	else return 0;
}
int main()
{
	//do{
	char s[99];
	printf("ÇëÊäÈëÒ»´®À¨»¡£º");
	gets(s);
	int t=isValid(s);
	printf("%d\n",t);//}while(1);
	return 0;
 } 
