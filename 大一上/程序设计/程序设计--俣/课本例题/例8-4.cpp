#include<stdio.h>
#include<stdlib.h>
void swapNumbers(int variableOne,int variableTwo);
int main(void)
{
	int firstNum=0,secondNum=0;
	printf("��������������:");
	scanf("%d%d",&firstNum,&secondNum);
	printf("firstNum is:%d\nsecondNum is:%d\n",firstNum,secondNum);
	printf("����������\n");
	swapNumbers( firstNum,secondNum);
	printf("firstNum is:%d\nsecondNum is:%d\n",firstNum,secondNum);
	system("PAUSE");
	return 0;
}
void swapNumbers(int variableOne,int variableTwo)
{
	int temp=0;
	temp=variableOne;
	variableOne=variableTwo;
	variableTwo=temp;
}
