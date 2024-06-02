#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node*next;
};
int main()
{
	int n,m;//猴子个数，报数数到m退出 
	int i;
	int answer;//保存每次答案，最后统一输出 
	int count=0;//count用来控制题目答案的下标 
	struct node *head,*tail,*p,*q;//p指向当前处理的节点，q总是指向p指针指向的前一个节点 
	
	//创建头节点，为方便debug跟踪，数据域设为-1
	head=(struct node*)malloc(sizeof(struct node));
	head->data=-1;
	head->next=NULL;
	
		scanf("%d%d",&n,&m);
		if(n==0||m==0){
			free(head);
			return 1; 
		}
		else{
			tail=head;
			for(i=0;i<n;i++){
				//采用尾插法创建循环链表，用tail指针指向最后一个节点
				p=(struct node*)malloc(sizeof(struct node));
				p->data=i+1;//填写猴子序号 
				tail->next=p;//插到尾部 
				p->next=head->next; //最后节点的next域指向第一个有效节点，形成循环链表 
				tail=p;//tail移动到最后一个节点，为下一次插入做准备 
			}
			p=head->next;
			q=tail;
			i=1;
			while(q!=p){//p,q总是一前一后，一旦他们相遇，则说明只剩一个节点了 
				if(i==m){
					//把当前节点从列表中删除
					q->next=q->next->next;
					free(p);
					//将p移动到下一个有效节点上，i=1重新开始报数
					p=q->next;
					i=1; 
				} 
				else{
					//p,q各自向后移动一个节点，其中q总是在p的前面
					q=p;
					p=p->next;
					//报数+1
					i++; 
				}
			} 
			//head->next=q
			//前面删除节点时，当最后只剩下两个结点的时候，有可能造成链表不完整，在这道题目中这条语句可以不要
			answer=p->data;
			free(p);
			head->next=NULL;//链表已空，只有头节点了，将头节点的next域赋值为NULL，虽然不是必须的，确是好习惯 
		}
	
		printf("%d\n",answer);
	 
	 free(head);
	 return 0;
}
