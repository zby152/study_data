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
	printf("\n��ӭʹ�õ��ͼ�����ͳ���\n\n");
	printf("��������Ҫ��͵��ͼ���������:");
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
			printf("%d�������ĺͣ�%d/%d\n",nterm,u,v);
		}
	}
	system("PAUSE");
	return 0;
}
