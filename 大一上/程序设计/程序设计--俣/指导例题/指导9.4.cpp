#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char weekstring[][10]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
int main(void)
{
	int d,today,w,s,i;
	char x[4];
	char *p;
	p=x;
	printf("����������:");
	gets(x);
	if(strcmp(p,"Sun")==0)
	    today=0;
	else if(strcmp(p,"Mon")==0)
	    today=1;
	    else if(strcmp(x,"Tue")==0)
	    today=2;
	    else if(strcmp(x,"Wed")==0)
	    today=3;
	    else if(strcmp(x,"Thu")==0)
	    today=4;
	    else if(strcmp(x,"Fri")==0)
	    today=5;
	    else if(strcmp(x,"Sat")==0)
	    today=6;
	printf("��������:");
	scanf("%d",&d);
	printf("����������%s\n",weekstring[today]);
	w=(d+today)%7;
	printf("%d���������%s\n",d,weekstring[w]);
	system("PAUSE");
	return 0; 
}
