#include<stdio.h>
#include<stdio.h>
#define N 500
#define Q 10
int main()
{
	int a[N],b[Q],i,n,k,m=0,q,sum=0;
	a[0]=1;
	for(i=2;i<=N;i++)
	a[i]=a[i-1]+1;
	printf("请输入需要求多少以内的素数：");
	scanf("%d",&n);
	for(k=n;k>1;k--){
	for(i=2;i<=k;i++){
		if(a[k]%i==0) break;
	}
	if(i==a[k]) {
		printf("%d\t",a[k]);
		sum+=a[k];
		b[m]=a[k];
		m++;
	}
	if(m==10) break;
}
printf("\n该素数之和为：%d\n",sum);
printf("请输入需要确定位置的数：");
scanf("%d",&q);
int p;
p=search(q,b,m);
printf("%d",p);
return 0;
}
int search(int key,int a[],int len)
{
	int left=0,right=len-1;
	int res=-1;
	while(right>=left){
		int mid=(left+right)/2;
		if(a[mid]==key){
			res=mid;
			break;
		}
		else if(a[mid]>key){
			left=mid+1;
		}
		else right=mid-1;
	}
	return res;
}
