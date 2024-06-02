#include <stdio.h>
#include <string.h>
void found(char str[]);
int main(void)
{
char str[201];
gets(str);
while (strcmp(str, "BEGIN") == 0)
{
found(str);
printf("%s\n", str);
gets(str);
}
return 0;
}
void found(char str[])
{
char plain[27] = "VWXYZABCDEFGHIJKLMNOPQRSTU";
char strEnd[201];
gets(str);
int i,j;
for(i=0;i<strlen(str);i++){
	for(j=0;j<27;j++){
		if(str[i]==plain[j]){
			str[i]=plain[(j+21)%26];
			break;
		}
	}
}
gets(strEnd);
return;
}
