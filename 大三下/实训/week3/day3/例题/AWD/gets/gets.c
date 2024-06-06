#include<string.h>
#include<stdlib.h>
#include<stdio.h>
char bin_sh_str[8] = "/bin/sh";
void init_data()
{
    setbuf(stdin, 0);
    setbuf(stdout, 0);
    setbuf(stderr, 0);
}
void vul()
{
	char s[100];
	puts("input:");
	gets(s);
	puts("OK,Bye!");
}
int main()
{
	init_data();
	vul();

	
}
void getshell()
{
	system("echo no no no!!!");
}
