struct ListNode
{
	int val;
	struct ListNode *pNext;
 } ;
 
struct ListNode *removeNthFromEnd(struct ListNode*head,int n)
{
	struct ListNode *p1,*p2;
	p1=p2=head;
    int i;
    for(i=1;i<=n;i++)
    {
    	p1=p1->pNext;
	}
	while(p1!=NULL)  // ����ʱp1����NULL����p1,p2ͬʱ�� 
	{
		p1=p1->pNext;
		p2=p2->pNext;
	}
	head=head->pNext;  //����ʱp1��NULL������n����Ч��ֵ����ͷ�ڵ���Ҫɾȥ�Ľڵ� 
	
	p2->pNext=p2->pNext->pNext; //ɾȥp2����һ���ڵ� 
	
};

