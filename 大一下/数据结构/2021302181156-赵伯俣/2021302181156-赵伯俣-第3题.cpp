#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
#define INF 32767

typedef struct node
{
	int data;
	struct node *lchild;
	struct node *rchild;
}BTNode;//二叉树节点类型 

typedef struct
{
	BTNode * data[MaxSize];
	int front,rear;
}SqQueue;//环形队列 


void CreateBTree(BTNode *&b,char*str)//创造二叉树函数 
{
	BTNode *St[MaxSize],*p=NULL;
	int top=-1,k,j=0;  
	char ch;
	b=NULL;				
	ch=str[j];
	while (ch!='\0')  	
	{
   	   	switch(ch) 
		{
		case '(':top++;St[top]=p;k=1; break;		
		case ')':top--;break;
		case ',':k=2; break;                      		
		default:p=(BTNode *)malloc(sizeof(BTNode));
				p->data=ch;p->lchild=p->rchild=NULL;
				if (b==NULL)                    	 
					b=p;
				else  								
				{	
					switch(k) 
					{
					case 1:St[top]->lchild=p;break;
					case 2:St[top]->rchild=p;break;
					}
				}
		}
		j++;
		ch=str[j];
	}
}

void DestroyBTree(BTNode *&b)//摧毁二叉树函数 
{	if (b!=NULL)
	{	DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		free(b);
	}
}

void DispBTree(BTNode *b) //输出二叉树函数 
{
	if (b!=NULL)
	{	printf("%c",b->data);
		if (b->lchild!=NULL || b->rchild!=NULL)
		{	printf("(");						
			DispBTree(b->lchild);				
			if (b->rchild!=NULL) printf(",");	
			DispBTree(b->rchild);				
			printf(")");					
		}
	}
}

void InOrder(BTNode *b)//递归中序遍历 
{
	if(b!=NULL)
	{
		InOrder(b->lchild);
		printf("%c ",b->data);
		InOrder(b->rchild);
	}
}

void InitQueue(SqQueue *&qu)//初始化队列 
{
	qu=(SqQueue *)malloc(sizeof(SqQueue));
	qu->front=qu->rear=0;
}

bool enQueue(SqQueue *&q,BTNode* e)	//进队函数 
{	if ((q->rear+1)%MaxSize==q->front)	
		return false;
	q->rear=(q->rear+1)%MaxSize;
	q->data[q->rear]=e;
	return true;
}

bool QueueEmpty(SqQueue *q)	//判断队列是否为空 
{
	return(q->front==q->rear);
}

bool deQueue(SqQueue *&q,BTNode *&e)	//出队 
{	if (q->front==q->rear)		
		return false;
	q->front=(q->front+1)%MaxSize;
	e=q->data[q->front];
	return true;
}

void DestroyQueue(SqQueue *&q)	//摧毁队列 
{
	free(q);
}
void bottom_up(BTNode *b)//自底向上层次遍历 
{
	BTNode *p;
	SqQueue *qu;
	InitQueue(qu);
	enQueue(qu,b);
	while(!QueueEmpty(qu))
	{
		deQueue(qu,p);
	    printf("%c ",p->data);
		if(p->lchild!=NULL)
		    enQueue(qu,p->lchild);
		if(p->rchild!=NULL)
		    enQueue(qu,p->rchild);
	}
	DestroyQueue(qu);
}

int main()//主函数 
{
	BTNode *b;
    b=(BTNode *)malloc(sizeof(BTNode));
	char str[MaxSize]="A(B(C,D(E,F)),G(,H(I,)))";
	CreateBTree(b,str);
	printf("转化为二叉链存储为:\n");
	DispBTree(b);
	printf("\n这个二叉树的中序遍历结果为:\n");
	InOrder(b);
	printf("\n这个二叉树的自底向上层次遍历结果为:\n");
	bottom_up(b);
	DestroyBTree(b);
	return 0;
}
