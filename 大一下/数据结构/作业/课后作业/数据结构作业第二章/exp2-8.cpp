#include"c:/cpp/linklist.cpp"
void sort(LinkNode *&L)
{
    LinkNode*p,*q,*pre;
    p=L->next->next;
    L->next->next=NULL;
    while(p!=NULL)
    {
    	q=p->next;
    	pre=L;
    	while(pre->next!=NULL && pre->next->data < p->data)
    	    pre=pre->next;
    	p->next=pre->next;
    	pre->next=p;
    	p=q;
	}
}
void add(LinkNode *L1,LinkNode *L2,LinkNode *&L3)
{
	LinkNode *p1,*p2,*r,*s;
	p1=L1->next;
	p2=L2->next;
	L3=(LinkNode*)malloc(sizeof(LinkNode));
	r=L3;
	while(p1!=NULL && p2!=NULL)
	{
		if(p1->data < p2->data)
		{
			s=(LinkNode*)malloc(sizeof(LinkNode));
			s->data=p1->data;
			r->next=s;
			r=s;
			p1=p1->next;
		}
		else if(p1->data > p2->data)
		{
			s=(LinkNode*)malloc(sizeof(LinkNode));
			s->data=p2->data;
			r->next=s;
			r=s;
			p2=p2->next;
		}
		else
		{
			s=(LinkNode*)malloc(sizeof(LinkNode));
			s->data=p1->data;
			r->next=s;
			r=s;
			p1=p1->next;
			p2=p2->next;
		}
	}
	if(p2!=NULL)
	    p1=p2;
	while(p1!=NULL)
	{
		s=(LinkNode*)malloc(sizeof(LinkNode));
		s->data=p1->data;
		r->next=s;
		r=s;
		p1=p1->next;
	}
	s->next=NULL;
}
void Insect(LinkNode*L1,LinkNode*L2,LinkNode*&L3)
{
	LinkNode*p1,*p2,*r,*s;
	p1=L1->next;
	L3=(LinkNode*)malloc(sizeof(LinkNode));
	r=L3;
	while(p1!=NULL)
	{
		p2=L2->next;
		while(p2!=NULL && p2->data < p1->data)
		{
			p2=p2->next;
		}
		if(p2!=NULL && p2->data==p1->data)
		{
			s=(LinkNode*)malloc(sizeof(LinkNode));
			s->data=p1->data;
			r->next=s;
			r=s;
		}
		p1=p1->next;
	}
	r->next=NULL;
} 
void Sub(LinkNode*L1,LinkNode*L2,LinkNode*&L3)
{
	LinkNode*p1,*p2,*s,*r;
	p1=L1->next;
	p2=L2->next;
	L3=(LinkNode*)malloc(sizeof(LinkNode));
	r=L3;
	while(p1!=NULL)
	{
		p2=L2->next;
		while(p2!=NULL && p2->data < p1->data)
		{
			p2=p2->next;
		}
		if(p2!=NULL && p2->data > p1->data)
		{
			s=(LinkNode*)malloc(sizeof(LinkNode));
			s->data=p1->data;
			r->next=s;
			r=s;
		}
		p1=p1->next;
	}
	r->next=NULL;
}
int main()
{
	LinkNode*L1,*L2,*L3;
	ElemType a[]={'a','q','v','l'};
	int n1=4;
	CreateListR(L1,a,n1);
	printf("原始L1:");
	DispList(L1);
	ElemType b[]={'i','b','a','t','d','m'};
	int n2=6;
	CreateListR(L2,b,n2);
	printf("原始L2:");
	DispList(L2);
	sort(L1);
	printf("排序后L1:");
	DispList(L1);
	sort(L2);
	printf("排序后L2:");
	DispList(L2);
	add(L1,L2,L3);
	printf("L1与L2的并集为:");
	DispList(L3);
	Insect(L1,L2,L3);
	printf("L1,L2的交集为:");
	DispList(L3);
	Sub(L1,L2,L3);
	printf("L1,L2的差集为:");
	DispList(L3);
}
