#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	struct node*next;
};

int deleteLink_2(struct node *phead,int n)
{
	struct node *current,*p;
	current=phead;
	while(current->data!=n&&current->next!=NULL)
	{
		p=current;
		current=current->next;
	}
	if(current->data==n)
	{
		if(current==phead)
		    phead=current->next;
		else
		    p->next=current->next;
		free(current);
		return 1;
	}
	else
	    return 0;
}
int main()
{
	struct node *head,*newone,*tail;
	int i,num,j;
	printf("请输入需要的节点个数:\n");
	scanf("%d",&j);
	printf("请依次输入节点数据：\n");
	scanf(" %d",&num);
	head=NULL;
	for(i=0;i<j;i++)
	{
		newone=(struct node*)malloc(sizeof(struct node));
		newone->data=num;
		newone->next=NULL;
		if(head==NULL)
		    head=newone;
		else
		    tail->next=newone;
		tail=newone;
		if(i!=(j-1))
		scanf(" %d",&num);
	}

	int m,result;
	printf("输入想删除的数据\n");
	scanf("%d",&m);
	result=deleteLink_2(head,m);
	if(result==1)
	printf("删除成功\n");
	else
	printf("删除失败\n");
	struct node *p;
	p=head;
	while(p!=NULL)
	{
		printf("%d\n",p->data);
		p=p->next;
	}
	system("PAUSE");
	return 0;
}
