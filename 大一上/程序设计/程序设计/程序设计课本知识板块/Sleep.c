//#include <windows.h> //win头文件
//#include<stdio.h>
//int main()
//{
//    int i;
//    printf("你");
//    fflush(stdout); //强制刷新缓存，输出显示
//    for( i=0;i<10;i++ )
//    {
//        Sleep(1000);    /* windows 使用Sleep，参数为毫秒 */
//        printf(".");
//        fflush(stdout);//强制刷新缓存，输出显示
//    }
//    printf("好\n");  /*输出“你”和“好”之间会间隔10秒,并输出10个点*/
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

