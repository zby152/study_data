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
	printf("��������Ҫ�Ľڵ�����");
	scanf("%d",&n);
	printf("����������ڵ����ݣ�\n");
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
		printf("������%d���ڵ�������==>%d\n",i+1,p->data);
	}
	return 0;
}
