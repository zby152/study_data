#include<stdio.h>
#include<stdlib.h>
void change(char *p,int n);
int main()
{
	char* str;
	int n;
	printf("***��ӭ������������ϵͳ***\n");
	printf("����������Ҫ������ٸ��ַ����ո�Ҳ�㣩��\n");
	scanf("%d",&n);
	getchar();
	str=(char*)malloc(n*sizeof(char));
	gets(str);
	change(str,n);
	free(str);
	return 0;
}
void change(char*p,int n)
{
	int k,i;
	int*t;
	t=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++) t[i]=p[i];
	for(i=0;i<n;i++)
	{
		if(p[i]>=('a')&&p[i]<=('w')||p[i]>=('A')&&p[i]<=('W'))
		{
			t[i]+=3;
		}
		if(p[i]>('w')&&p[i]<=('z')||p[i]>('W')&&p[i]<=('Z')){
			t[i]-=23;
		}
	}
	for(k=0;k<n;k++) p[k]=t[k];
    puts(p);
}
