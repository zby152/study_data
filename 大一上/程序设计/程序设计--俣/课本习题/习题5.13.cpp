  #include<stdio.h>
#include<stdlib.h>
#define MAX 50

long Fibonacci (long num);
void push(int i);
int pop(void);
int stack[MAX];
int tos=0;

int main()
{
	int seriesSize=0;
	printf("\n�˳�������Fibonacci����\n\n");
	printf("������ϣ���������������");
	scanf("%d",&seriesSize);
	printf("\nFibonacci���еĵ�%d����%8ld\n",seriesSize,Fibonacci(seriesSize));
	printf("\n");
	system("PAUSE");
	return 0;
}
long Fibonacci(long num)
{
	static int d=0;
	int i;
	if(d==0)push(0);
	d++;
		printf("��%d��ݹ����  �β�num=%ld\n",d,num);
	if(num==0 ||num==1)
	{
		d=pop();
		return 1;
	}
	else
	{
		push(d);
		return (Fibonacci(num-1)+Fibonacci(num-2));
	}
}
	void push(int i)
	{
		if(tos>=MAX){
			printf("Stack Full\n");
		}
		stack[tos]=i;
		tos++;
	}
	int pop(void)
	{
		tos--;
		if(tos<0){
			printf("Stack Underflow\n");
			return 0;
		}
		return stack[tos];
	}

