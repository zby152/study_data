#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
#define INF 32767

typedef struct {
	int no;
} VertexType;

typedef struct {
	int edges[MaxSize][MaxSize];
	int n;//顶点数
	int e;//边数
	VertexType vexs[MaxSize];
} MatGraph;

typedef struct {
	int u;
	int v;
	int w;
} EdgeType;

typedef struct node
{
	int data;
	int rank;
	int parent;
}UFSTree;

void swap(EdgeType &x,EdgeType &y)//交换函数 
{
	EdgeType tmp;
	tmp=x;
	x=y;
	y=tmp;
}
void Create_MatGraph(MatGraph &g,int A[MaxSize][MaxSize],int n,int e) //创造邻接矩阵函数 
{
	int i,j;
	g.n=n; g.e=e;
	for (i=0;i<g.n;i++)
		for (j=0;j<g.n;j++)
			g.edges[i][j]=A[i][j];
}

void DispMat(MatGraph g)	//输出邻接矩阵函数 
{
	int i,j;
	for (i=0;i<g.n;i++)
	{
		for (j=0;j<g.n;j++)
			if (g.edges[i][j]!=INF)
				printf("%4d",g.edges[i][j]);
			else
				printf("%4s","∞");
		printf("\n");
	}
}

void sift(EdgeType R[],int low,int high)//筛选算法 
{
	int i=low,j=2*i;
	EdgeType tmp=R[i];
	while(j<=high)
	{
		if(j<high&&R[j].w<R[j+1].w)
		    j++;
		if(tmp.w<R[j].w)
		{
			R[i]=R[j];
			i=j;
			j=2*i;
		}
		else break;
	}
	R[i]=tmp;
}

void HeapSort(EdgeType R[],int n)//堆排序算法 
{

	int i;
	for(i=n/2;i>=1;i--)
	{
		sift(R,i,n);
	}
	for(i=n;i>=2;i--)
	{
		swap(R[1],R[i]);
		sift(R,1,i-1);
	}	
	
}

void MAKE_SET(UFSTree t[],int n)//并查集初始化 
{
	int i;
	for(i=1;i<=n;i++)
	{
		t[i].data=i;
		t[i].rank=0;
		t[i].parent=i;
	}
}

int FIND_SET(UFSTree t[],int x)
{
	if(x!=t[x].parent)
	t[x].parent=FIND_SET(t,t[x].parent);
	return t[x].parent;
}

void UNION(UFSTree t[],int x,int y)//合并和查询函数 
{
	x=FIND_SET(t,x);
	y=FIND_SET(t,y);
	if(t[x].rank>t[y].rank)
	t[y].parent=x;
	else
	{
		t[x].parent=y;
		if(t[x].parent==y)
		    t[y].rank++;
	}
}

void adjustDown(EdgeType edge_set[],int pos1, int pos2)//下堆操作函数 
{
	int sum;
    int i,j,k,u1,v1,sn1,sn2;
    UFSTree t[MaxSize];				
	k=1;							
	HeapSort(edge_set,24);
	MAKE_SET(t,7);				
	k=1;                 		
	j=1;       		
	while (k<7)       		
	{	
		u1=edge_set[j].u;
		v1=edge_set[j].v;        
		sn1=FIND_SET(t,u1);
		sn2=FIND_SET(t,v1); 				
		if (sn1!=sn2)     	  		
		{	
			printf("  (%d,%d):%d\n",u1+1,v1+1,edge_set[j].w);
			sum=sum+edge_set[j].w;
			k++; 
			UNION(t,u1,v1);                  
		}
		j++;   						
	}
	printf("\n最终的最小生成树的总代价为：\n");
	printf("%d",sum);

}

int main() //主函数 
{
	int i,j,k;
	EdgeType edge_set[MaxSize];
	MatGraph g;
	int n=7;
	int e=12;
	int pos1,pos2;
	int A[MaxSize][MaxSize]={
		{0,1,4,INF,INF,INF,INF},
		{1,0,2,5,3,INF,INF},
		{4,2,0,4,INF,3,INF},
		{INF,5,4,0,4,3,6},
		{INF,3,INF,4,0,INF,4},
		{INF,INF,3,3,INF,0,5},
		{INF,INF,INF,6,4,5,0}
	};
    Create_MatGraph(g,A,n,e);
    printf("图的邻接矩阵表示形式为:\n");
    DispMat(g);
	k=0;
	for(i=0;i<g.n;i++)
	{
		for(j=0;j<g.n;j++)
		{
			if(g.edges[i][j]!=0&&g.edges[i][j]!=INF)
			{
				edge_set[k].u=i;
				edge_set[k].v=j;
				edge_set[k].w=g.edges[i][j];
				k++;
			}
		}
	}
	printf("\n按照边加入生成树的顺序输出每一条边为:\n");
	adjustDown(edge_set,pos1,pos2);
	return 0; 
}
