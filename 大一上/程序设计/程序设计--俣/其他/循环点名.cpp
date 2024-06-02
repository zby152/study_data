#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(void)
{
    int i=1;
    srand((unsigned int) time(0));
	printf("点名请输入1，结束请输入其他\n");
	scanf ("%d",&i);
	while(i==1)
	{
	    int num=rand()%10;
	    switch(num)
	    {
	    	case 0:printf("白谨睿\n") ;break;
	    	case 1:printf("刘行健\n") ;break;
	    	case 2:printf("孙悦然\n") ;break;
	        case 3:printf("吴佳励\n") ;break;
	        case 4:printf("汪若晗\n") ;break;
	        case 5:printf("方思煜\n") ;break;
            case 6:printf("颜婕妤\n") ;break;
	        case 7:printf("赵伯俣\n") ;break;
         	case 8:printf("张  烁\n") ;break;
	        case 9:printf("张宇哲\n") ;break;
        }
        scanf ("%d",&i);
    }
}
