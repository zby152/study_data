#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int data;
	struct node*next;
}node;

node*creatlink()
{
	node*head,*tail,*new;
	head=tail=(node*)malloc(sizeof(node));
	head=NULL;
	int n;
	scanf("%d",&n);
	while(n!=-1){
		new=(node*)malloc(sizeof(node));
		new->data=n;
		new->next=NULL;
		if(head==NULL)
		head=new;
		else tail->next=new;
		tail=new;
		scanf("%d",&n);
	}
	return head;
}

node* removeNthFromEnd(node* head, int n)
{
	node*p,*q;
	int i=0;
	p=head;
	while(p!=NULL){
		i++;
		p=p->next;
	}
	p=head;
	int u=0;
	if(n==i) head=head->next;
	else {
	while(u<i-n){
		q=p;
		p=p->next;
		u++;
	}
	q->next=p->next;
	free(p);
}
return head;
}
int main()
{
	node*t,*r;
	t=creatlink();
	printf("请输入删除倒数第几个节点：");
	int n;
	scanf("%d",&n);
	r=removeNthFromEnd(t,n);
	while(r!=NULL){
		printf("%d\n",r->data);
		r=r->next;
	}
	return 0;
}
