#include<stdlib.h>
#include<stdio.h>
#define MaxSize 20
typedef struct node
{
    char data;
    struct node *lchild;
    struct node *rchild;
} BTNode;
int n1 = 0;
int n2 = 0;
int n3 = 0;
int n4 = 0;
void CreateBTree(BTNode *&b,char *str)//��������������
{
    BTNode *St[MaxSize], *p;
    int top = -1, k, j = 0;
    char ch;
    b = NULL;
    ch = str[j];
    while(ch!='\0')
    {
        switch(ch)
        {
            case '(':
                top++;
                St[top] = p;
                k = 1;
                break;
            case ')':
                top--;
                break;
            case ',':
                k = 2;
                break;
            default:
                p = (BTNode *)malloc(sizeof(BTNode));
                p->data = ch;
                p->lchild = p->rchild = NULL;
                if(b==NULL)
                    b = p;
                else
                {
                    switch(k)
                    {
                        case 1:
                            St[top]->lchild = p;
                            break;
                        case 2:
                            St[top]->rchild = p;
                            break;
                    }

                }
        }
        j++;
        ch = str[j];
    }
}
void DispBTree(BTNode *b)
{
    if(b!=NULL)
    {
        printf("%c", b->data);
        if(b->lchild!=NULL||b->rchild!=NULL)
        {
            printf("(");
            DispBTree(b->lchild);
            if(b->rchild!=NULL)
                printf(",");
            DispBTree(b->rchild);
            printf(")");
        }
    }
}
void number1(BTNode *b)//��������Ľ�����
{
    
    if(b!=NULL)
    {
        n1++;
        number1(b->lchild);
        number1(b->rchild);
    }
}
void number2(BTNode *b)//��Ҷ�ӽ�����

{
    if(b!=NULL)
        {
            if(b->lchild==NULL&&b->rchild==NULL)
            n2++;
            number2(b->lchild);
            number2(b->rchild);
        }
}
typedef struct 
{
    BTNode *data[MaxSize];
    int front, rear;
} SqQueue;
void InitQueue(SqQueue *&q)
{
    q = (SqQueue *)malloc(sizeof(SqQueue));
    q->front = q->rear = 0;
}
bool QueueEmpty(SqQueue *q)
{
    return (q->front == q->rear);
}
bool enQueue(SqQueue *&q,BTNode *e)
{
    if((q->rear+1)%MaxSize==q->front)
        return false;
    q->rear = (q->rear + 1) % MaxSize;
    q->data[q->rear] = e;
    return true;
}
bool deQueue(SqQueue *&q,BTNode* &e)
{
    if(q->front==q->rear)
        return false;
    q->front = (q->front + 1) % MaxSize;
    e = q->data[q->front];
    return true;
}
int floor=1;
void number3(BTNode*b,char x)
{
BTNode *p;
    SqQueue *qu;

    InitQueue(qu);
    enQueue(qu, b);
    while(!QueueEmpty(qu))
    {
        deQueue(qu, p);
        if(p->data==x)
        n3 = floor;
        if(p->lchild!=NULL)
        {
            floor++;
            enQueue(qu, p->lchild);

        }
        if (p->rchild != NULL)
        {
            floor++;
            enQueue(qu, p->rchild);

        }       

    }
}



void number4(BTNode*b)//���ò�α����������b�Ŀ��
{

}
int main()
{
    char str[50] = "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))";
    BTNode *b;

    CreateBTree(b, str);
    number1(b);
    printf("������B�Ľ�����Ϊ%d\n", n1);
    number2(b);
    printf("��������Ҷ�ӽ�����Ϊ%d\n", n2);  
    char x; 
    number3(b,x);  
    printf("��Ҫ���εĽ��ֵΪ\n");
    scanf(" %c", &x);
    printf("������ֵΪ%c�Ľ��Ĳ��Ϊ%d\n",x,n3);
    number4(b);
    printf("�������Ŀ��Ϊ%d\n", n4);
    return 1;
}
