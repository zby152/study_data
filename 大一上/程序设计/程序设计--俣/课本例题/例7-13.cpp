#include<stdio.h>
#include<stdlib.h>
void printArray(int a[][]);
int main()
{
	int array1[2][3]={{1,2,3},{4,5,6}};
	int array2[2][3]={1,2,3,4,5,6};
	int array3[][3]={{1,2},{4}};
	printf("\n二维数组初始化示例\n\n");
	printf("数组array1的值是(按行显示):\n");
	printArray(array1);
	printf("数组array2的值为（按行显示）:\n");
	printArray(array2);
	printf("数组array3的值为（按行显示）:\n");
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
