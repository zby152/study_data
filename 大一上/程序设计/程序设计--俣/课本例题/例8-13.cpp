#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	int a,b;
	a=0;
	b=0;
	scanf("%d",&a);
	scanf("%d",&b);
	int max(int,int),min(int,int),add(int,int);
	void process(int a,int b,int(*fun)(int a, int b));
	process(a,b,max);
	process(a,b,min);
	process(a,b,add);
	system("PAUSE");
	return 0; 
}
void process(int x,int y,int(*fun)(int x,int y))
{
	int result;
	result=(*fun)(x,y);
	printf("%d\n",result);
}
int max(int x,int y)
{
	printf("max=");
	return (x>y?x:y);
}
int min(int x,int y)
{
	printf("min=");
	return(x<y?x:y);
}
int add(int x,int y)
{
	printf("sum=");
	return(x+y);
}
