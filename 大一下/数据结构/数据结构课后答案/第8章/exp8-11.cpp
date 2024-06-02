#include<stdio.h>
#include<stdlib.h>
#define MAXV 20
#define INF 32767
typedef char InfoType;

typedef struct ANode
{	int adjvex;					
	struct ANode *nextarc;		
	int weight;					
} ArcNode;					
typedef struct Vnode
{	InfoType info;				
	int count;					
	ArcNode *firstarc;			
} VNode;						
typedef struct 
{	VNode adjlist[MAXV];		
	int n,e;					
} AdjGraph;	

void CreateAdj(AdjGraph *&G,int A[MAXV][MAXV],int n,int e) //����ͼ���ڽӱ�
{
	int i,j;
	ArcNode *p;
	G=(AdjGraph *)malloc(sizeof(AdjGraph));
	for (i=0;i<n;i++)						//���ڽӱ�������ͷ�ڵ��ָ�����ó�ֵ
		G->adjlist[i].firstarc=NULL;
	for (i=0;i<n;i++)						//����ڽӾ�����ÿ��Ԫ��
		for (j=n-1;j>=0;j--)
			if (A[i][j]!=0 && A[i][j]!=INF)	//����һ����
			{	p=(ArcNode *)malloc(sizeof(ArcNode));	//����һ���ڵ�p
				p->adjvex=j;
				p->weight=A[i][j];
				p->nextarc=G->adjlist[i].firstarc;	//����ͷ�巨����ڵ�p
				G->adjlist[i].firstarc=p;
			}
	G->n=n; G->e=n;
}
void DispAdj(AdjGraph *G)
{
	ArcNode *p;
	for (int i=0;i<G->n;i++)
	{
		p=G->adjlist[i].firstarc;
		printf("%3d: ",i);
		while (p!=NULL)
		{
			printf("%3d[%d]->",p->adjvex,p->weight);
			p=p->nextarc;
		}
		printf("\n");
	}
}
void DestroyAdj(AdjGraph *&G)	//����ͼ���ڽӱ�
{
	ArcNode *pre,*p;
	for (int i=0;i<G->n;i++)		//ɨ�����еĵ�����
	{	pre=G->adjlist[i].firstarc;	//pָ���i�����������׽ڵ�
		if (pre!=NULL)
		{	p=pre->nextarc;
			while (p!=NULL)			//�ͷŵ�i�������������б߽ڵ�
			{	free(pre);
				pre=p; p=p->nextarc;
			}
			free(pre);
		}
	}
	free(G);						//�ͷ�ͷ�ڵ�����
}				//����ͼ�Ĵ洢�ṹ�����������㷨
int visited[MAXV];		//ȫ�ֱ���
int V1[MAXV],V2[MAXV],n,m; 
int count=0;
bool Cond(int path[],int d)			//�ж�����
{
	int flag1=0,f1,flag2=0,f2,i,j;
	for (i=0;i<n;i++)				//�ж�·�����Ƿ��бؾ���
	{
		f1=1;
		for (j=0;j<=d;j++)
			if (path[j]==V1[i])
			{
				f1=0; break;
			}
		flag1+=f1;
	}

	for (i=0;i<m;i++)		//�ж�·�����Ƿ��бرܵ�
	{
		f2=0;
		for (j=0;j<=d;j++)
			if (path[j]==V2[i])
			{
				f2=1; break;
			}
		flag2+=f2;
	}
	if (flag1==0 && flag2==0)	//������������true
		return true;
	else						//��������������false
		return false;
}
void TravPath(AdjGraph *G,int vi,int vj,int path[],int d) //��ͼG�в��ҴӶ���vi������vj������������·��
{
	int v,i;
	ArcNode *p;
	visited[vi]=1;
	d++; path[d]=vi;
	if (vi==vj && Cond(path,d))
	{
		printf(" 路径%d: ",++count);
		for (i=0;i<d;i++)
			printf("%d->",path[i]);
		printf("%d\n",path[i]);
	}
    p=G->adjlist[vi].firstarc;      //��vi�ĵ�һ���ڽӶ���
	while (p!=NULL)
	{
		v=p->adjvex;                //vΪvi���ڽӶ���
		if (visited[v]==0)          //���ö���δ��Ƿ���,��ݹ����֮
			TravPath(G,v,vj,path,d);
		p=p->nextarc;               //��vi����һ���ڽӶ���
	}
	visited[vi]=0;                  //ȡ�����ʱ��,��ʹ�ö��������ʹ��
	d--;
}
int main()
{ 
	int i,u,v;
	int path[MAXV];
	AdjGraph *G;
	int A[MAXV][MAXV] = {
		{0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
		{0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0},
		{0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0}};
	CreateAdj(G,A,15,21);
	printf("图的邻接表:\n"); DispAdj(G);
	for (i=0;i<n;i++) visited[i]=0;
	printf("起点和终点:");
	scanf("%d%d",&u,&v);
	printf("必经点个数");
	scanf("%d",&n);
	printf("必经点:");
	for (i=0;i<n;i++)
		scanf("%d",&V1[i]);
	printf("必避点个数:");
	scanf("%d",&m);
	printf("必避点:");
	for (i=0;i<m;i++)
		scanf("%d",&V2[i]);
	printf("\n所有路径:\n");
    TravPath(G,u,v,path,-1);
	DestroyAdj(G);
	return 1;
}