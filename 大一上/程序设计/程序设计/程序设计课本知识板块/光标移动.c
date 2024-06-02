//#include<stdio.h>
//#include<windows.h>
//int main()
//{
//    HANDLE hOut;
//  COORD pos={15,5};
//    hOut=GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleCursorPosition(hOut,pos);
     
//    SetConsoleTextAttribute(hOut,0x01|0x05);
     
//    printf("HelloWorld!\n");
//    return 0;
//}
#include<stdio.h>
#include<windows.h>
int main()
{
    HANDLE hOut;
    COORD pos={0,0};
    int i;
    
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut,0x01|0x05);
    for(i=0;i<20;i++)
    {
	    pos.X=i;
	    pos.Y=i;
	    SetConsoleCursorPosition(hOut,pos);
	     
	    printf("%d%d:HelloWorld!\n",pos.X,pos.Y);
	    getchar();
    }
    return 0;
}
