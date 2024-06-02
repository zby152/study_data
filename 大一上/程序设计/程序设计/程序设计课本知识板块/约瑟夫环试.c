#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node*next;
};
int main()
{
	printf("欢迎来到约瑟夫环系统！\n");
	int m,n,answer;
	printf("请输入猴子的数量，以及数到多少退出：");
	scanf("%d%d",&n,&m);
	struct node*head,*tail,*new,*p,*q;
	head=tail=(struct node*)malloc(sizeof(struct node));
	head->data=-1;
	head->next=NULL;
	int i;
	for(i=0;i<n;i++){
		new=(struct node*)malloc(sizeof(struct node));
		new->data=i+1;
		tail->next=new;
		new->next=head->next;
		tail=new;
    }
  
    if(n==0||m==0){
    	free(head);
    	return 1;
	}
    else{
	p=head->next;
    q=tail;
    i=1; 
    while(p!=q){
    	if(i==m){
    		printf("%d\t",p->data);
    		q->next=p->next;
    		free(p);
    		p=q->next;
    		i=1;
		}
		else{
			q=p;
			p=p->next;
			i++;
		}
	}
	answer=p->data;
	free(p); 
}
printf("%d\n",answer);
return 0;
}
