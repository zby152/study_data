#include"c:/cpp/linklist.cpp"
void add(LinkNode *L1,LinkNode *L2,LinkNode *&L3)
{
	LinkNode*p1=L1->next,*p2=L2->next,*r;
    L3=L1;
    r=L3;
    free(L2);
    while(p1!=NULL && p2!=NULL)
    {
        r->next=p1;
		r=r->next;
		p1=p1->next;
		r->next=p2;
		r=r->next; 
		p2=p2->next;
	}
    r->next=NULL;
    if(p2!=NULL)
        p1=p2;
    r->next=p1;
}
int main()
{
	LinkNode *L1, *L2, *L3;
	ElemType a[]="aaaaa";
	ElemType b[]="bbb";
	int n1=5,n2=3;
    CreateListR(L1,a,n1);
    CreateListR(L2,b,n2);
    printf("L1:");
    DispList(L1);
    printf("L2:");
	DispList(L2);
    add(L1,L2,L3);
    printf("L3:");
    DispList(L3);
    return 1;
}
