void sub2(SqList *&A,SqList*&B)
{
	SqList*a,*b,*prea;
	prea=A;
	a=A->next;
	b=B->next;
	while(a!=NULL&&b!=NULL)
	{
		if(a->data > b->data)
		    b=b->next;
		else if(a->data < b->data)
		{
			prea=a;
			a=a->next;
		}
        else
        {
        	prea->next=a->next;
        	free(a);
        	a=prea->next;
		}
	}
}
