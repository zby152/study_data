#include<stdio.h>
#include<stdlib.h>
	struct node{
		int data;
		struct node *next;
	}*head;
struct node * creat( )
{
	int n;
	struct node *newone, *tail;
	head=NULL;
	printf("请输入单链表的数据，输入-1停止\n");
	scanf("%d",&n);
	while(n!=-1)
	{
		newone=(struct node *)malloc(sizeof(struct node));
		newone->data=n;
		newone->next=NULL;
		if(head==NULL)
		    head=newone;
		else
		    tail->next=newone;
		tail=newone;
		scanf("%d",&n);
	}
	return(head);
}
struct node * concatenate(struct node *head1,struct node *head2)
{
	struct node *p,*marker,*second;
	p=head1;
	while(p!=NULL)
	{
	p=p->next;
    }
    p=second;
    return (head1);
}
int main(void)
{
	struct node *n1,*n2,*p;
	n1=creat();
	n2=creat();
	concatenate(n1,n2);
	p=n1;
	while(p!=NULL)
	{
		printf("%d\n",p->data);
		p=p->next;
	}
	system("PAUSE");
	return 0;
}
