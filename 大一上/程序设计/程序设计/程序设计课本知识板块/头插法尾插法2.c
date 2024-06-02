/*#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node*next;
};
struct node* createlink()
{
	struct node *head,*nail,*current;
	int n;
	head=nail=(struct node*)malloc(sizeof(struct node));
	head=NULL;
	scanf("%d",&n);
	while(n!=-1){
		current=(struct node*)malloc(sizeof(struct node));
		current->data=n;
		current->next=NULL;
		if(head==NULL)
		head=current;
		else
			nail->next=current;
			nail=current;
			scanf("%d",&n);
	}
	return head;
}
int main()
{
	struct node* t;
	t=createlink();
	while(t!=NULL){
		printf("%d\n",t->data);
		t=t->next;
	}
	return 0;
}*/
#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node*next;
};
struct node *createlink()
{
	struct node*head,*tail,*new;
	int n;
	head=tail=(struct node*)malloc(sizeof(struct node));
	head=NULL;
	scanf("%d",&n);
	while(n!=-1)
	{
		new=(struct node*)malloc(sizeof(struct node));
		new->data=n;
	    new->next=head;
	    head=new;
	    scanf("%d",&n);
	}
	return head;
 }
struct node*reserve(struct node*head)
{
	struct node*p1,*p2,*p3;
	p1=head;
	p2=head->next;
	while(p2){
		p3=p2->next;
		p2->next=p1;
		p1=p2;
		p2=p3;
	}
	head->next=NULL;
	head=p1;
	return head;
 } 
int main()
{
	struct node* t,*m;
	t=createlink();
	t=reserve(t);
	while(t!=NULL){
		printf("%d\n",t->data);
		t=t->next;
	}
	return 0;
}
 
