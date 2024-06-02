#include<stdlib.h>
#include<stdio.h>
struct node{
	int data;
	struct node *next;
};
struct node *insertSort(struct node *head,int n)
{
	struct node *newone,*p,*marker;
	newone=(struct node*)malloc(sizeof(struct node));
	newone->data=n;
	p=head;
	while(p!=NULL&&p->data<n)
	{
		marker=p;
		p=p->next;
	}
	if(p==head)
	{
		newone->next=head;
		head=newone;
	}
	else
	{
		newone->next=marker->next;
		marker->next=newone;
	}
	return (head);
}
struct node* creatSortLink(struct node *head)
{
	int n;
	head=NULL;
	scanf("%d",&n);
	while(n!=-1)
	{
		head=insertSort(head,n);
		scanf(" %d",&n);
	}
	return head;
}
int main()
{
    struct node *head;
	head=creatSortLink(head);
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
