#include<stdio.h>
#include<stdlib.h>
void getNumbers(int* inputOne,int* inputTwo);
void swapNumbers(int* variableOne,int* variableTwo);
int main(void)
{
	int firstNum=0,secondNum=0;
	getNumbers( &firstNum,&secondNum);
	printf("firstNum is :%d \n secondNum is: %d\n\n",firstNum,secondNum);
	printf("����������\n");
	swapNumbers(&firstNum,&secondNum);
	printf("firstNum is :%d\n secondNum is: %d \n",firstNum,secondNum);
	system("PAUSE");
	return 0;
}
void getNumbers(int* inputOne,int* inputTwo)
{
	printf("��������������:");
	scanf("%d %d",inputOne,inputTwo);
}
void swapNumbers(int* variableOne,int* variableTwo)
{
	int temp=0;
	temp= *variableOne;
	*variableOne=*variableTwo;
	*variableTwo=temp;
}
