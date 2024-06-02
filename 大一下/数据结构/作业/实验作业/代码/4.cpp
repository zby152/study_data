#include<stdio.h>

typedef  char ElemType;
typedef struct node
{
    ElemType data;
    struct node *lchild;
    struct node *rchild;
} BTNode;
int leef_number(int k,BTNode *b,int &n,int h)
//k代表要寻找的层次,b代表根节点,n代表第k层的叶子节点个数,h代表当前根节点层数
{
    if(b==NULL)
        return;
    else
    {
        if(h==k&&(b->lchild)==NULL&&(b->rchild)==NULL)
            n++;
        else if(h<k)
        {
            leef_number(k, b->lchild, n, h + 1);
            leef_number(k, b->rchild, n, h + 1);
        }
    }
}
