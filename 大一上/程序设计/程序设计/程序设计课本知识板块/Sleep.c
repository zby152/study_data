//#include <windows.h> //winͷ�ļ�
//#include<stdio.h>
//int main()
//{
//    int i;
//    printf("��");
//    fflush(stdout); //ǿ��ˢ�»��棬�����ʾ
//    for( i=0;i<10;i++ )
//    {
//        Sleep(1000);    /* windows ʹ��Sleep������Ϊ���� */
//        printf(".");
//        fflush(stdout);//ǿ��ˢ�»��棬�����ʾ
//    }
//    printf("��\n");  /*������㡱�͡��á�֮�����10��,�����10����*/
//    return 0;
//}
//1s=1000ms
#include <stdio.h>
#include <windows.h>
main()
{
	int time;
	printf("Please input a time(unit:second):\n");
	scanf("%d",&time);
	printf("Starting to calculate the time~\n");
	while(1)
	{
		Sleep(1000);
		time--;
		printf("%d\n",time);
		if(time==0)
		{
			break;
		}
	}
	printf("OK!! It's the time!\n");
}

