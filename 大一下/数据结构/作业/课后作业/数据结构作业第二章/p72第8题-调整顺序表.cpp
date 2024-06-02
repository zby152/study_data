void move(SeqList *&L)
{
    int i,j;
    int temp;
    for (i=0,j=L->length-1;i<j; )
    {
    	while(i<j&&L->data[i]<0)   i++;
    	while(i<j&&L->data[j]>0)   j--;
    	if(i<j)
    	{
    		temp=L->data[i];
    		L->data[i]=L->data[j];
    		L->data[j]=temp;
		}
	}
}
