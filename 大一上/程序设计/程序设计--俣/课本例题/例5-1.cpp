#include<stdio.h>
#include<stdlib.h>
long u,v;
void addrat(int a,int b)
{
	u=u*b+v*a;
	v*=b;
}
void lowterm()
{
	int numcopy,dencopy;
	int remainder;
	numcopy=u;
	dencopy=v;
	while(dencopy!=0)
	{
		remainder=numcopy%dencopy;
		numcopy=dencopy;
		dencopy=remainder;
	}
	if(numcopy!=0)
	{
		u/=numcopy;
		v/=numcopy;
	}
}
int main()
{
	int n,nterm;
	printf("\n欢迎使用调和级数求和程序\n\n");
	printf("请输入需要求和调和级数的项数:");
	scanf("%d",&n);
	if(n<=0)
	printf("Bad data!");
	else
	{
		u=0;
		v=1;
		for(nterm=1;nterm<=n;nterm++)
		{
			addrat(1,nterm);
			lowterm();
			printf("%d个项数的和：%d/%d\n",nterm,u,v);
		}
	}
	system("PAUSE");
	return 0;
}
