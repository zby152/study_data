#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 1024
int main()
{
	int i,n,k; 
	double sum1=0,sum2=0,q,p,t,u,r;
	double distance[N],a[N],b[N];
	printf("��������Ҫ������ٸ��㣺");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
	printf("�������%d���������(��ʽΪ��x y):\n",i+1); 
	scanf("%lf%lf",&a[i],&b[i]);
	sum1+=a[i];
	sum2+=b[i];
}
	q=sum1/n;
	p=sum2/n;
	printf("��������Ϊ��%lf,%lf��",q,p);
	for(i=0;i<n;i++) {
	distance[i]=sqrt((a[i]-q)*(a[i]-q)+(b[i]-p)*(b[i]-p));
}
	for(i=0;i<n-1;i++){
		for(k=0;k<n-i-1;k++){
			if(distance[k]>distance[k+1]){
				r=distance[k];
				distance[k]=distance[k+1];
				distance[k+1]=r;
				t=a[k];
				u=b[k];
				a[k]=a[k+1];
				b[k]=b[k+1];
				a[k+1]=t;
				b[k+1]=u;
			}
		}
	}
	printf("\n����������ĵ�Ϊ��(%lf,%f)\n��������Զ�ĵ�Ϊ(%lf,%lf)\n",a[0],b[0],a[n-1],b[n-1]);
	return 0;
}
