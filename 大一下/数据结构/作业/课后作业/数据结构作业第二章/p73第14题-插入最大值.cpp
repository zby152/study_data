void inset(SqList *&L,Elem Type x)
{
	SqList *p=L->next,*q;
	int i=1,j=1,k=0;
	int maxnumber=p->data;
	while(p!=NULL)
	{
		if(p->data > maxnumber)
		{
			maxnumber=p->data;
			j=i;
		}
		p=p->next;
		i++;
	}
	q=L->next;
	for(k=0;k<j-2;k++)
    {
    	q=q->next;
	}
	SqList newone=(SqList *)malloc(sizeof(SqList));
	newone->data=x;
	newone->next=q->next;
	q->next=newone;
}
