#define M 8
#define N 5
#include<stdio.h>
void merge(int x[],int y[]);
int main()
{
	int x[M]={-7,1,3,5,7,9,12,45},y[N]={0,2,4,6,8};
	merge(x,y);
	return 0;
}
void merge(int x[],int y[])
{
	int xy[M+N];
	int i=0,j=0,k=0;
	while(i<M&&j<N)
	if(x[i]<y[j]){
		xy[k]=x[i];
		i++;k++;
	}
	else{
		xy[k]=y[j];
		j++;k++;
	}
	while(i<M){
		xy[k]=x[i];
		k++;i++;
	}
	while(j<N){
		xy[k]=x[j];
		k++;j++;
	}
	
	printf("\n%d个有序数为：",M+N);
	for(i=0;i<M+N;i++){
		printf("%d,",xy[i]);
	}
	
}

