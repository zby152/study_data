#include<stdio.h>
typedef struct list{
	int data;
	struct list *pNext;
}node;

typedef node *link;
link creatlink(int m)
{
	link head,tail,new;
	int i=0,n;
	head=tail=(link)malloc(sizeof(node));
	head=NULL;
	printf("请依次输入节点数据：\n"); 
	while(i<m){
		scanf("%d",&n);
		new=(link)malloc(sizeof(node));
		new->data=n;
		new->pNext=head;
		head=new;
		i++;
	}
	return head;
}
int main()
{
	int q=1,m;
	link t;
	printf("请输入节点数据：");
	scanf("%d",&m);
	t=creatlink(m);
	printf("要求逆序输出节点的数据如下：\n");
	while(t!=NULL){
		printf("倒数第%d个节点数据是==>%d\n",q,t->data);
		q++;
		t=t->pNext;
	}
	return 0;
}
