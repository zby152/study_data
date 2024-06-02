#include<stdio.h>
#include<string.h> 
void fun(char*ss)
{
	int i;
	for(i=0;i<strlen(ss);i++){
		if(i%2!=0){
			if(ss[i]>=97&&ss[i]<=122)
			ss[i]=ss[i]-32;
		}
	}
	
}
int main()
{
	char ss[81];
	printf("\nPlease enter an string within 80 characters:\n");
	gets(ss);
	
	printf("\n\nAfter changing,the string\n   %s\n",ss);
	fun(ss);
	printf("\nbecomes\n   %s\n",ss);
}
