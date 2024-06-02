#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void swap(int*r,int*t);
int main()
{
	srand((unsigned)time(NULL)); 
	int len,k,i,m;
	int*p;
	printf("请输入需要的数组长度："); 
	scanf("%d",&len); 
	p=malloc(sizeof(int)*len);
	for(i=0;i<len;i++)
	{
		p[i]=rand();
	 } 
	 for(i=0;i<len-1;i++)
	 {
	 	for(k=0;k<len-i-1;k++){
	 		if(p[k]>p[k+1]) swap(&p[k],&p[k+1]);
		 }
	 }
	 for(i=0;i<len;i++){
	 	printf("p[%d]=%d\n",i,p[i]);
	 }
	 free(p);
	 return 0;
}
void swap(int*r,int*t)
{
	int q;
	q=*r;
	*r=*t;
	*t=q;
}
