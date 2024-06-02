#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct node{
	int data;
	struct node*next;
};
/*struct node *createlink()
{
	struct node *head,*new;
	head=NULL;
	int n;
	scanf("%d",&n);
	while(n!=-1){
		new=(struct node*)malloc(sizeof(struct node));
		new->data=n;
		new->next=head;
		head=new;
		scanf("%d",&n);
	}
	return head;
}
int count(struct node*head){
	int count=0;
	while(head!=NULL){
		count++;
		head=head->next;
	}
	return count;
}
int queryNode(struct node*head,int x)
{
	int n=0;
	while(head){
		if(head->data==x){
			return true;
		}
		head=head->next;
	}
	return false;
	}
int main()
{
	struct node *t;
	int m,q;
	t=createlink();
	m=count(t);
	printf("\n%d\n\n",m);
	printf("你想要查找的数：");
	scanf("%d",&q);
	if(queryNode(t,q)==0) printf("\n没有\n");
	else printf("\n有\n");
	while(t!=NULL){
		printf("%d\n",t->data);
		t=t->next;
	}
	
	return 0;
}*/
struct node*creatlink()
{
	struct node *new,*tail,*head;
	int n;
	
	head=NULL;
	
	scanf("%d",&n);
	while(n!=-1)
	{
		new=(struct node*)malloc(sizeof(struct node));
		new->data=n;
		new->next=NULL;
		
		if(head==NULL)
		head=new;
		else
		tail->next=new;
		tail=new;
		scanf("%d",&n);
	}
	return head;
}
int main()
{
	struct node*t;
	t=creatlink();
	while(t!=NULL){
		printf("%d\n",t->data);
		t=t->next;
	}
	return 0;
}
