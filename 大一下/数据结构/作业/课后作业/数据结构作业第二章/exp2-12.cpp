#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define MAX 50
typedef struct node
{
	int data;
	struct node * next;
}nodetype;
void creatlink(nodetype *&L,char a[],int n)
{
	nodetype *p,*r;
	int i=0;
	L=(nodetype*)malloc(sizeof(nodetype));
	r=L;
	while(i<n)
	{
		p=(nodetype*)malloc(sizeof(nodetype));
		p->data=a[n-i-1]-'0';
		r->next=p;
		r=p;
		i++;
	}
	r->next=NULL;
 } 
displink(nodetype*L)
{
	nodetype *p=L->next;
	while(p!=NULL)
	{
		printf("%d",p->data);
		p=p->next;
	}
	printf("\n");
}
void add(nodetype *L1,nodetype*L2,nodetype*&L3)
{
	nodetype *p1=L1->next,*p2=L2->next,*p,*r;
	int carry=0;
	L3=(nodetype*)malloc(sizeof(nodetype));
	r=L3;
	while(p1!=NULL&&p2!=NULL)
	{
		p=(nodetype*)malloc(sizeof(nodetype));
		p->data=(p1->data+p2->data+carry)%10;
		r->next=p; r=p;
		carry=(p1->data+p2->data+carry)/10;
		p1=p1->next;
		p2=p2->next;
	}
	if(p1==NULL)  p1=p2;
	while(p1!=NULL)
	{
		p=(nodetype*)malloc(sizeof(nodetype));
		p->data=(p1->data+carry)%10;
		r->next=p;  r=p;
		carry=(p1->data+carry)/10;
		p1=p1->next;
	}
	if(carry>0)
	{
		p=(nodetype*)malloc(sizeof(nodetype));
		p->data=carry;
		r->next=p;
		r=p;
	}
	r->next=NULL;
}
void reverse(nodetype *&L)
{
	nodetype*p=L->next,*q;
	L->next=NULL;
	while(p!=NULL)
	{
		q=p->next;
		p->next=L->next;
		L->next=p;
		p=q;
	}
}
int mid(nodetype*L)
{
	nodetype *slow=L,*quick=L;
	while(quick!=NULL&&quick->next!=NULL)
	{
		slow=slow->next;
		quick=quick->next->next;
	}
	return slow->data;
}
int main()
{
	nodetype *L1,*L2,*L3;
	char s[MAX],t[MAX];
    printf("输入第一组整数\n");
	scanf("%s",s);
	printf("输入第二组整数\n");
	scanf("%s",t);
	creatlink(L1,s,strlen(s));
	creatlink(L2,t,strlen(t));
	printf("整数单链表L1:");
	displink(L1);
	printf("整数单链表L2:");
	displink(L2);
	add(L1,L2,L3);
	printf("结果单链表是:");
	displink(L3);
	reverse(L3);
	printf("对应的整数:");
	displink(L3);
	printf("中间位:%d\n",mid(L3));
	return 1;
}
