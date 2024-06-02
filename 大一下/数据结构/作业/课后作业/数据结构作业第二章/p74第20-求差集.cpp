void sub(SqList *A,SqList*B)
{
	SqList *a,*b,*prea,*preb;
	prea=A;
    int T;
    for(a=A->next;a!=NULL;a=a->next)
    {
    	preb=B;
    	T=1;
    	for(b=B->next;b!=NULL;b=b->next)
    	{
    		if(a->data==b->data)
    		{
    			T=0;
    			prea->next=a->next;
    			free(a);
    			a=prea;
    			preb->next=b->next;
    			free(b);
    			b=preb->next;
    			break;
			}
			preb=preb->next;
		}
		if(T==1)
		prea=prea->next;
	}
} 
