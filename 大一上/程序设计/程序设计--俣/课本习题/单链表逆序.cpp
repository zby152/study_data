#include<stdlib.h>
#include<stdio.h>
typedef struct list{
	int data;
	struct list *pNext;
}node;

typedef node list;
int main()
{
	list *head,*newone,*tail;
	int i,num,n;
	printf("��������Ҫ�Ľڵ����:\n");
	scanf("%d",&n);
	printf("����������ڵ����ݣ�\n");
	scanf(" %d",&num);
	head=NULL;
	for(i=0;i<n;i++)
	{
		newone=(list*)malloc(sizeof(list));
		newone->data=num;
		newone->pNext=NULL;
		if(head==NULL)
		    head=newone;
		else
		    tail->pNext=newone;
		tail=newone;
		if(i!=(n-1))
		scanf(" %d",&num);
	}
	
    list *newhead,*oldhead,*temp;
    oldhead=head;
    newhead=NULL;
    while(oldhead){
		temp=oldhead->pNext;
		oldhead->pNext=newhead;
		newhead=oldhead;
		oldhead=temp;
	}
    head=newhead;
    
	list *p;
	p=head;
	while(p!=NULL)
	{
		printf("%d\n",p->data);
		p=p->pNext;
	}
	system("PAUSE");
	return 0;
}
