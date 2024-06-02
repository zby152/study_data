#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct
{
	int a;//系数 
	int r;//指数 
}xArray;
typedef struct pnode
{
	int a;
	int r;
	struct pnode *next;
}xNode;
void DispList(xNode*y)
{
	int first=1;
	xNode *p=y->next;
	while(p!=NULL)
	{
		if(first==1)
		    first=0;
		else if(p->a > 0)
			printf("+");
		else if(p->a < 0)
		    printf("-");
		if(p->r==0)
		    printf("%d",p->a);
		else if(p->r==1)
		    printf("%dx",p->a);
		else
		    printf("%dx^%d",p->a,p->r);
		p=p->next;
	}
	printf("\n");
}
void sort(xNode*y1)
{
	xNode*p=y1->next,*pre,*q;
	if(p!=NULL)
	{
		q=p->next;
		p->next=NULL;
		p=q;
	}
	while(p!=NULL)
	{
		q=p->next;
		pre=y1;
		while(pre->next!=NULL && pre->next->r > p->r)
		   pre=pre->next;
		p->next=pre->next;
		pre->next=p;
		p=q;
	}
}
void CreateListR(xNode*&y,xArray a[],int n)
{
	xNode *s,*r;
	int i;
	y=(xNode* )malloc(sizeof(xNode));
	y->next=NULL;
	r=y;
	for(i=0;i<n;i++)
	{
		s=(xNode* )malloc(sizeof(xNode));
		s->a=a[i].a;
		s->r=a[i].r;
		r->next=s;
		r=s;
	}
	r->next=NULL;
}
void add(xNode*y1,xNode *y2,xNode*&y3)
{
	xNode *p1,*p2,*s,*r,*q;
	p1=y1->next;
	p2=y2->next;
	y3=(xNode*)malloc(sizeof(xNode));
	r=y3;
	while(p1!=NULL && p2!=NULL)
	{
		if(p1->r > p2->r)
		{
			s=(xNode*)malloc(sizeof(xNode));
			s->a=p1->a;
			s->r=p1->r;
			r->next=s;
			r=s;
			p1=p1->next;
		}
		else if(p1->r < p2->r)
		{
		    s=(xNode*)malloc(sizeof(xNode));
			s->a=p2->a;
			s->r=p2->r;
			r->next=s;
			r=s;
			p2=p2->next;
		}
		else
		{
			int add_a=p1->a + p2->a;
			s=(xNode*)malloc(sizeof(xNode));
			s->a=add_a;
			s->r=p2->r;
			r->next=s;
			r=s;
			p2=p2->next;
			p1=p1->next;
		}
	}
	if(p2!=NULL)    
	    p1=p2;
	while(p1!=NULL)
	{
	    s=(xNode*)malloc(sizeof(xNode));
		s->a=p1->a;
		s->r=p1->r;
		r->next=s;
		r=s;
		p1=p1->next;
	}
	r->next=NULL;
}
int main()
{
	xNode *y1,*y2,*y3;
	xArray a[]={{1,0},{2,5},{3,4},{4,1}};
	CreateListR(y1,a,4);
	xArray b[]={{2,0},{3,7},{4,5},{7,9},{4,4}};
    CreateListR(y2,b,5);
	printf("原多项式y1：");
	DispList(y1);
	printf("原多项式y2：");
	DispList(y2);
	sort(y1);
	sort(y2);
	printf("排序后多项式y1：");
	DispList(y1);
	printf("排序后多项式y2：");
	DispList(y2);
	add(y1,y2,y3);
	printf("相加的结果为:");
	DispList(y3);
	return 1;
}
