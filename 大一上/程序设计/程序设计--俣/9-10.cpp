#include<stdio.h>
#include<stdlib.h>
//链表逆序 
int main()
{
	struct node{
		char data[2];
		struct node *next;
	};
	struct node *head,*tail,*newone,*p;
	char n[2];
	int i,m,j;
	head=NULL;
	printf("请输入10个链表数据第十一位任意输入:\n");
	for(i=0;i<2;i++)
	scanf("%d",&n[i]);
	for(i=0;i<11;i++)
	{
	    newone=(struct node *)malloc(sizeof(struct node));
	    for(m=0;m<2;m++)
	    newone->data[m]=n[m];
	    newone->next=NULL;
	if(head==NULL)
	    head=newone;
	else
	    tail->next=newone;
	tail=newone;
	for(j=0;j<2;j++)
	scanf(" %c",&n[j]);
    }
    struct node *newhead,*oldhead,*temp;
    oldhead=head;
    newhead=NULL;
    while(oldhead){
		temp=oldhead->next;
		oldhead->next=newhead;
		newhead=oldhead;
		oldhead=temp;
	}
    head=newhead;
    p=head;
	while(p!=NULL){
		for(i=0;i<2;i++)
		printf("%c",p->data[i]);
		printf("\n");
		p=p->next;
	}
	for(i=0;i<2;i++)
	printf("%c",p->data);
	system("PAUSE");
	return 0;
}
