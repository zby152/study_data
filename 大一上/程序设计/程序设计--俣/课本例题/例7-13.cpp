#include<stdio.h>
#include<stdlib.h>
void printArray(int a[][]);
int main()
{
	int array1[2][3]={{1,2,3},{4,5,6}};
	int array2[2][3]={1,2,3,4,5,6};
	int array3[][3]={{1,2},{4}};
	printf("\n��ά�����ʼ��ʾ��\n\n");
	printf("����array1��ֵ��(������ʾ):\n");
	printArray(array1);
	printf("����array2��ֵΪ��������ʾ��:\n");
	printArray(array2);
	printf("����array3��ֵΪ��������ʾ��:\n");
	printArray(array3);
	printf("\n");
	system("PAUSE");
	return 0;
}
void printArray(int a[][3])
{
	int i;
	int j;
	for(i=0;i<=1;i++)
{
	for(j=0;i<=2;j++)
	printf("%6d",a[i][j]);
	printf("\n");
}
}
