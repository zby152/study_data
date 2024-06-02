#include<stdio.h>
typedef FILE *stream;
int main()
{
	stream my_in;
	char s[80];
	my_in=fopen("hhh.txt","r");
	if(my_in==NULL){
		printf("File open error!\n");
		exit(0);
	}
	fgets(s,6,my_in);
	printf("%s",s);
}
