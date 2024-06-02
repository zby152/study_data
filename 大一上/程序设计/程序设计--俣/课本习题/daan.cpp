#include<stdio.h>
#include<stdlib.h>
int main()
{
	struct node{
		char data[2];
		struct node *next;
	};
	struct node *head,*tail,*newone,*p;
	char n[2];
	int i;
	head=NULL;
	printf("请输入链表数据:（输入-1停止）\n");
	for(i=0;i<2;i++)
	scanf("%d",&n[i]);
	while(n[0]!='ab')
	{
	    newone=(struct node *)malloc(sizeof(struct node));
	    for(i=0;i<2;i++)
	    newone->data[i]=n[i];
	    newone->next=NULL;
	if(head==NULL)
	    head=newone;
	else
	    tail->next=newone;
	tail=newone;
	for(i=0;i<2;i++)
	scanf("%d",&n[i]);
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
	while(p!=NULL)
	{
		for(i=0;i<2;i++)
		printf("%c\n",p->data[i]);
		p=p->next;
	}
	system("PAUSE");
	return 0;
}
