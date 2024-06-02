#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int data;
	struct node*next;
}node;

node* creatlink()
{
	node*head,*tail,*new;
	head = tail = (node*)malloc(sizeof(node));
	head = NULL;
	int i = 0;
	while(i < 10)
	{
		new = (node*)malloc(sizeof(node));
		new->next = NULL;
		scanf("%d",&new->data);
		if(head == NULL)
		head = new;
		else
		tail->next =new;
		tail = new;
		i++;
	}
	return head;
}

node* reverse(node*head){
	node*p1,*p2,*p3;
	p1 = head;
	p2 = head->next;
	while(p2 != NULL){
		p3 = p2->next;
		p2->next = p1;
		p1 = p2;
		p2 = p3;
	}
    head->next = NULL;
	head = p1;
	return head;
}

int main()
{
	node*t;
	t = creatlink();
	t = reverse(t);
	while(t != NULL){
		printf("%d",t->data);
		t = t->next;
	}
	return 0;
 } 

