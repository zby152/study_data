#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node*next;
};
struct node * deleteLink_1(struct node *head,int n)
{
	struct node *current,*p;
	current=head;
	while(current->data!=n&&current->next!=NULL)
	{
		p=current;
		current=current->next;
	}
	if(current->data==n)
	{
		if(current==head)
		head=current->next;
		else
		p->next=current->next;
		free(current);
	}
	return (head);
}
int main()
{
	struct node *head_;
	int n;
	printf("输入像删除的数据\n");
	scanf("%d",&n);
	head_=deleteLink_1(head_,n);
	system("PAUSE");
	return 0;
}
