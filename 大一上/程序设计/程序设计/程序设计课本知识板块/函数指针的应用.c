#include<stdio.h>
int add(int num1,int num2){
	return num1+num2;
}
int sub(int sum1,int sum2){
	return sum1-sum2;
}
int calculate(int(*fp)(int,int),int num1,int num2){
	return (*fp)(num1,num2);
}
int main()
{
	printf("3+5=%d\n",calculate(add,3,5));
	printf("3-5=%d\n",calculate(sub,3,5));
	return 0;
}
