#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char *a="\tab\b\b\x53\np\104\"";
    printf("%d",strlen(a));
	system("PAUSE");
	return 0;
}
