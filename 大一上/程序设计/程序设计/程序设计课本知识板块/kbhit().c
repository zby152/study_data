#include<stdio.h>
#include<stdlib.h>
int main()
{
	int a;
	system("PAUSE");
	a=_kbhit();
	printf("%d\n",a);
	
	return 0;
}
//int main()
//{
//	while(1){
//		if(_kbhit()){
//			printf("The user presses a key.\n");
//			_getch();
//		}
//	}
//	return 0;
//}
//实践部-姜子宽 11:45:32
//就是他一直检测

//实践部-姜子宽 11:45:47
//他检测的那一瞬间你输入才好使

//实践部-姜子宽 11:46:04
//就应该配合着while用


