void LocateNode(SqList *&L,ElemType x)
{
	SqList *p=L->next,*pre;
    ElemType temp;
    int tempf;
    while(p!=NULL&&p->data!=x)
        p=p->next;
    if(p=NULL)
        return 0;
    else
    {
    	p->freq++;
    	pre=p->prior;
    	if(pre!=L)
    	{
    		while(pre!=L&&pre->freq < p->freq)
    		{
    			temp=p->data;
    			p-data=pre->data;
    			pre->data=temp;
    			tempf=p->freq;
    			p->freq=pre->freq;
    			prq->freq=temp;
    			p=pre;
    			pre=p->prior;
			}
		}
	}
}
