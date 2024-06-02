#include<stdio.h>
#include<stdlib.h>
struct ListNode{
    int val;
    struct ListNode *pNext;
};
struct ListNode *creatlink(){
	struct ListNode *head,*tail,*new;
	head=tail=(struct ListNode*)malloc(sizeof(struct ListNode));
	head=NULL;
	int n,i=0;
	while(i<5){
		scanf("%d",&n);
		new=(struct ListNode*)malloc(sizeof(struct ListNode));
		new->val=n;
		new->pNext=NULL;
		if(head==NULL) head=new;
		else tail->pNext=new;
		tail=new;
		i++;
	}
	return head;
}
struct ListNode* removeNthFromEnd(struct ListNode* head, int n)
{
	struct ListNode *p,*q;
	q=head;
	p=head->pNext;

	int i=1;
	if(n==1){
		head=p;
		free(q);
		return head;
	}
	else if(head!=NULL&&head->pNext!=NULL){
			n=n-1;
		while(p!=NULL){
			if(i==n){
				q->pNext=p->pNext;
				free(p);
				return head;
				}
			
			else{
				q=p;
				p=p->pNext;
				i++;
			}
		}
}
	return head;
};
int main()
{
	struct ListNode *t,*head;
	printf("请输入链表内容：\n");
	t=creatlink();
	int m;
	printf("请输入删除第几个：");
	scanf("%d",&m); 
    head=removeNthFromEnd(t,m);
	while(head!=NULL){
	printf("%d\n",head->val);
	head=head->pNext;
}
	return 0;
}
