#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(void)
{
    int i=1;
    srand((unsigned int) time(0));
	printf("����������1����������������\n");
	scanf ("%d",&i);
	while(i==1)
	{
	    int num=rand()%10;
	    switch(num)
	    {
	    	case 0:printf("�׽��\n") ;break;
	    	case 1:printf("���н�\n") ;break;
	    	case 2:printf("����Ȼ\n") ;break;
	        case 3:printf("�����\n") ;break;
	        case 4:printf("������\n") ;break;
	        case 5:printf("��˼��\n") ;break;
            case 6:printf("����\n") ;break;
	        case 7:printf("�Բ�ٶ\n") ;break;
         	case 8:printf("��  ˸\n") ;break;
	        case 9:printf("������\n") ;break;
        }
        scanf ("%d",&i);
    }
}
