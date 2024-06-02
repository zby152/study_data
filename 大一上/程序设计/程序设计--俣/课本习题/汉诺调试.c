#include<stdio.h>
#include<stdlib.h>
void move(char getone,char putone)
{
	printf("%c->%c\n",getone,putone);
}
void hanoi(int n,char one,char two,char three)
{
	if(n==1)
	    move(one,three);
	else
	{
		hanoi(n-1,one,three,two);
		move(one,three);
		hanoi(n-1,two,one,three);
	}
}
int main()
{
	int m;
	printf("Input the number of disks:");
	scanf("%d",&m);
	printf("The steps to moving %3d disks:\n",m);
	hanoi(m,'A','B','C');
	system("PAUSE");
	return 0;
}
