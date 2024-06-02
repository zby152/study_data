#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
	int data;
	struct node*next;
};
int DeleteNum(int r,int m);
void InputData(int*n,int*m) 
{
	do{
	printf("请输入人数n，以及判断退出的数字：");
	scanf("%d%d",n,m);
	}while(*m<2||*m>9||*m>*n);
}
void DeleteNode(int n,int m)
{
	int b; 
	struct node*head,*tail,*new,*p,*q;
	head=tail=(struct node*)malloc(sizeof(struct node));
	head->data=-1;
	head->next=NULL;
	int i,answer;
	for(i=0;i<n;i++){
		new=(struct node*)malloc(sizeof(struct node));
		new->data=i+1;
		tail->next=new;
		new->next=head->next;
		tail=new;
	}
	p=head->next;
	q=tail;
	i=1;
	while(p!=q){
		if(DeleteNum(i,m)==0){
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
}
int DeleteNum(int r,int m)
{
	if(r%m==0) return 0;
	else{
	char str[10],ch[2];
	int i;
	itoa(r,str,10);
	itoa(m,ch,10);
	int t=strlen(str);
	for(i=0;i<t;i++){
		if(str[i]==ch[0]) return 0;
	}
	return 1;
	}
}
int main()
{
	int n,m,t;
	InputData(&n,&m);
	DeleteNode(n,m);
	return 0;
}
