#include<stdio.h>
#include<stdlib.h>
#ifdef MAX
int Max(int x,int y,int z)
{
	return(x>y)?x:y;
}
#else
int Max(int x,int y,int z)
{
	int k;
	k=x>y?x:y;
	return(z>k)?z:k;
}
#endif
int main(void)
{
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	printf("max=%d\n",Max(a,b,c));
	system("PAUSE");
	return 0;
}
