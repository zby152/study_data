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
	printf("����������ڵ����ݣ�\n"); 
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
	printf("������ڵ����ݣ�");
	scanf("%d",&m);
	t=creatlink(m);
	printf("Ҫ����������ڵ���������£�\n");
	while(t!=NULL){
		printf("������%d���ڵ�������==>%d\n",q,t->data);
		q++;
		t=t->pNext;
	}
	return 0;
}
