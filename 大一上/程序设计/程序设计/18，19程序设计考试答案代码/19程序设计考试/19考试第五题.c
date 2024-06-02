#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
	struct node*next;	
}node;

void InputData(int*n,int*m)
{
	do{
	printf("请输入人数以及淘汰数字：");
	scanf("%d%d",n,m);
    }while((*n<*m)||*m<2||*m>9);
}

void DeleteNode(int n,int m)
{
	node*p,*q;
	int i;
	node*head,*tail,*new;
	head=tail=(node*)malloc(sizeof(node));
	head=NULL;
	for(i=0;i<n;i++){
		new=(node*)malloc(sizeof(node));
		new->data=i+1;
		new->next=head;
		if(head==NULL)
		head=new;
		else tail->next=new;
		tail=new;
	}
	i=1;
	p=head;
	q=tail;
	while(p!=q){
		if(DeleteNum(i,m)==1){
			printf("%d\t",p->data);
			q->next=p->next;
			free(p);
			p=q->next;
			i++;
		}
		else{
			q=p;
			p=p->next;
			i++;
		}
	}
	printf("%d",p->data);
	free(p);
}

int DeleteNum(int i,int m)
{
	if(i%m==0) return 1;
	else{
	char str1[99];
	itoa(i,str1,10);
	char str2[1];
	itoa(m,str2,10);
	int r;
	for(r=0;r<sizeof(str1);r++)
	if(str1[r]==str2[0]) return 1;
	}
	return 0;	
}

int main()
{
	int m,n,i;
	InputData(&n,&m);
	DeleteNode(n,m);
}
