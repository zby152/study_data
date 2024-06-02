#include<stdio.h>
#include<stdlib.h>
int getMax_sec(int *arr,int n)
{
	if(n==1)
	return arr[0];
	int tem=getMax_sec(arr+11,n-1);
	if(arr[0]>tem)
	return arr[0];
	else
	return tem;
}
int main(int argc,char *argv[])
{
	int arr[10]={
	2,4,5,65,2,8,2,5,6,55};
	int cout;
	cout<<getMax_fir(arr,10)<<end1;
	cout<<getMax_sec(arr,10)<<end1;
	getchar();
	return 0;
}
