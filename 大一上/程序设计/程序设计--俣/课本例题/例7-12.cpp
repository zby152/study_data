#include<stdio.h>
#include<stdlib.h>
#define IN 1
#define OUT 0
int main()
{
	int nw,state;
	char c;
	printf("\n统计单词个数\n\n");
	printf("请输入一行字符\n");
	nw=0;
	state=OUT;
	while((c=getchar())!=EOF)
	if(c==' '||c=='\n'||c=='\t')
	    state=OUT;
	    else if(state==OUT)
	    {
	    	nw++;
	    	state=IN;
		}
		printf("There are %d words.\n",nw);
		system("PAUSE");
		return 0;
}
