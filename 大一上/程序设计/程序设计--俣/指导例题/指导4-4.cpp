#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int x;
	printf("���������\n");
	scanf("%d",&x);
	if(x>0,x<=100)
	{
	    if(x>=90)
	        printf("�ȼ�ΪA");
	    if(x>=80&x<=89)
	        printf("�ȼ�ΪB");
	    if(x>=70&x<=79)
	        printf("�ȼ�ΪC");
	    if(x>=60&x<=69)
	        printf("�ȼ�ΪD");
	    if(x<60)
	        printf("�ȼ�ΪE");
}
    else
    printf("����"); 
	system("PAUSE");
	return 0;
	 
}
