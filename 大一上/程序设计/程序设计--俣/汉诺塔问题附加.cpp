#include<stdio.h>
#include<stdlib.h>
void move(char  getone,char  putone,int n)
{
	printf("%c->%c\n",getone,putone); 
	printf("%d\n",n);
}
void hanoi(int n,char one,char two,char three)
{
	if(n==1)
	    move(one,three,1);
    else
    {
    	hanoi(n-1,one,three,two);
    	move(one,three,n);
    	hanoi(n-1,two,one,three);
	}
}
int main()
{
	int m;
	printf("Input the number of disks:");
	scanf("%d",&m);
	printf("The steps to moving %3ddisks:\n",m);
	hanoi(m,'A','B','C');
	system("PAUSE");
	return 0;
} 
