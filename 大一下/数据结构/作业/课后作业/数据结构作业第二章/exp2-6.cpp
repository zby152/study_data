#include "c:/cpp/linklist.cpp"
void depart( LinkNode *&L,ElemType x)
{
    LinkNode*p,*q,*r;
    p=L->next;
    L->next=NULL;
    r=L;
    while(p!=NULL)
    {
    	if(p->data<x)
    	{
    		q=p->next;
    		p->next=L->next;
    		L->next=p;
    		if(p->next==NULL)
    		    r=p;
    		p=q;
		}
		else
		{
			r->next=p;
			r=p;
			p=p->next;
		}
	}
    r->next=NULL;
}
int main()
{
	LinkNode*L;
	ElemType a[]="abcdefgh";
	int n=8;
	CreateListR(L,a,n);
	printf("L:");
	DispList(L);
	ElemType x='d';
	printf("按%c进行划分:",x);
	depart(L,x);
	printf("L:");
	DispList(L);
	DestroyList(L);
	return 1;
}
