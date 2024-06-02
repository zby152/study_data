#include<stdio.h>
#include<stdlib.h>
//递归遍历链表 
struct node{
	int data;
	struct node *next;
};
struct node* creat()/*创造函数*/
{
	struct node *head,*newone,*tail;
	int n;
	head=NULL;
	printf("请输入链表数据：\n");
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
	return head; 
}
struct node *find(struct node *n,int x)/*查找函数*/
{
	if(n)
	{
        struct node * head;
        head=n;
	    head=find(n->next,x);
	    if(head)
	    {
		    return head;
	    }
	    else
	    {
		    if(n->data==x)
		    return n;
	    }
    }
    return NULL;
}

int main()/*主函数*/
{
	struct node *n,*p;
	int x;
	printf("请输入要查找的值\n");
	scanf("%d",&x);
	n=creat();
	p=find(n,x);
	printf("%p",p);
	system("PAUSE");
	return 0;
 } 
