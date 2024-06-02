#include<stdio.h>
#include<stdlib.h>
typedef  char ElemType;
typedef struct node
{
    ElemType data;
    struct node *lchild;
    struct node *rchild;
} BTNode;
void sons(int x,BTNode *b)
{
    if(b==NULL)
        return;
    else if(b->data==x)
    {
        DispBTree(b->lchild);
        DispBTree(b->rchild);
    }
    else
    {
        sons(x, b->lchild);
        sons(x, b->rchild);
    }
}