#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	int*p,*q;
	int i,k,sum=0;
	q=(int*)malloc(6*sizeof(int));
	p=(int*)malloc(6*sizeof(int));
	printf("***��ӭ������Ʊ����***\n");
	srand((unsigned)time(NULL));
	printf("������ȫ���н����֣�\n");
	for(i=0;i<6;i++)
	{
		p[i]=rand()%10;
		printf("%d\t",p[i]);
	}
	printf("\n�������������֣�\n");
	for(i=0;i<6;i++)
	{
		scanf("%d",&q[i]);
	}
	printf("������������н����֣�\n"); 
	for(i=0;i<6;i++)
	{
		if(p[i]==q[i]) 
		{
		printf("%d\t",q[i]);
		sum++;
		}
	}
	printf("����%d��",sum);
	free(p);
	free(q);
	return 0;
}
