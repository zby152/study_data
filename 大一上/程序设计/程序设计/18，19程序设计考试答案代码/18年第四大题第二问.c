#include<stdio.h>
#include<stdlib.h>
 
typedef struct list {
    int data;
    struct list *pNext;
}node;

typedef node *link;

int main()
{
	link head,tail,new;
	head=tail=new=(link)malloc(sizeof(node));
	head=NULL;
	int n,i=0;
	printf("请输入需要的节点数：");
	scanf("%d",&n);
	printf("请依次输入节点数据：\n");
	while(i<n){
		new=(link)malloc(sizeof(node));
		scanf("%d",&new->data);
		new->pNext=NULL;
		if(head==NULL) head=new;
		else tail->pNext=new;
		tail=new;
		i++;
	}
	int j;
	link p;
	for(i=0;i<n;i++){
		p=head;
		for(j=0;j<n-i-1;j++){
			p=p->pNext;
		}
		printf("倒数第%d个节点数据是==>%d\n",i+1,p->data);
	}
	return 0;
}
