#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(void)
{
	srand((unsigned int) time(0));
	int num=rand()%10;
	switch(num)
	{
	case 0:printf("��˼��");   break;
	case 1:printf("���н�"); break;
	case 2:printf("����Ȼ") ;break;
	case 3:printf("�����") ;break;
	case 4:printf("������") ;break;
	case 5:printf("����");break;
	case 6:printf("�Բ�ٶ"); break;
	case 7:printf("��˸");break;
	case 8:printf("������"); break;
	case 9:printf("�׽��") ;break;
    }
	system("PAUSE");
	return 0;
}
