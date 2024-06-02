#include<stdlib.h>
#include<stdio.h>
typedef struct list{
	int data;
	struct list *pNext;
}node;

typedef node list;
int main()
{
	list *head,*newone; 
	int i,num,n;
	printf("请输入需要的节点个数:\n");
	scanf("%d",&n);
	printf("请依次输入节点数据：\n");
	scanf(" %d",&num);
	head=NULL;
	while(n!=-1)
	{
		newone=(list*)malloc(sizeof(list));
		newone->data=n;
		newone->pNext=head;
		head=newone;
		scanf("%d",&n);
	}
system("PAUSE");
return 0;
 } 
