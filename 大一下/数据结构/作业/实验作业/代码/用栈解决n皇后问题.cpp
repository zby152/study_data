#include<stdio.h>
#include<stdlib.h>
#define MAX 20  
int n = 0;
typedef struct
{
    int place[MAX];
    int top;
} SqStack;
void disp_answer(SqStack st)//输出解
{
   static int count=0;
    printf("第%d个解：", ++count);
    for (int i = 1; i <=st.top;i++)
    {
        printf("（%d，%d）", i, st.place[i]);
    }
    printf("\n");
}
void InitStack(SqStack *&s)
{
    s = (SqStack *)malloc(sizeof(SqStack));
    s->top = -1;
}
bool Push(SqStack *&s,int e)
{
    if(s->top==MAX-1)
        return false;
    s->top++;
    s->place[s->top] = e;
    return true;
}
//看第k个皇后能否落在（k，j）位置上
bool tryplace(SqStack st,int k,int j)//k表示第几行的皇后，j表示测试该皇后的位置（K，j）
{

    int i = 1;
    if(k==1)
        return true;
    while(k-1>=i)
    {
        if(st.place[i]==j||(abs(st.place[i]-j)==abs(k-i)))
            return false;
        i++;
    }
    return true;
}
void queen(int n)//求解算法
{
    SqStack st;
    bool find;
    int k, j;
    st.top = 0;
    st.top++;
    st.place[st.top] = 0;
    while(st.top!=0)
    {
        find = false;
        k = st.top;
        for (j = st.place[k]+1; j <= n;j++)
            if(tryplace(st,k,j))
            {
                find = true;
                st.place[st.top] = j;
                break;
            }
        if(find)
        {
            if(st.top==n)
                disp_answer(st);
            else
            {
                st.top++;
                st.place[st.top] = 0;
            }
        }
        else
            st.top--;
    }
}
int main()
{
    printf("请输入皇后个数\n");
    scanf("%d", &n);
   if(n>=1&&n<=20)
       queen(n);
    else
        printf("请重新输入n的值在1-20之间\n");
    return 0;
}