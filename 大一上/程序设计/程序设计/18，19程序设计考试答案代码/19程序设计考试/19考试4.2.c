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
	while(p1!=NULL)  // 若此时p1不是NULL，则p1,p2同时增 
	{
		p1=p1->pNext;
		p2=p2->pNext;
	}
	head=head->pNext;  //若此时p1是NULL，并且n是有效的值，则头节点是要删去的节点 
	
	p2->pNext=p2->pNext->pNext; //删去p2的下一个节点 
	
};

