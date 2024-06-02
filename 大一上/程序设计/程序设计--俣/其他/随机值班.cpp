#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(void)
{
	srand((unsigned int) time(0));
	int num=rand()%10;
	switch(num)
	{
	case 0:printf("·½Ë¼ìÏ");   break;
	case 1:printf("ÁõĞĞ½¡"); break;
	case 2:printf("ËïÔÃÈ»") ;break;
	case 3:printf("Îâ¼ÑÀø") ;break;
	case 4:printf("ÍôÈôº­") ;break;
	case 5:printf("ÑÕæ¼æ¥");break;
	case 6:printf("ÕÔ²®Ù¶"); break;
	case 7:printf("ÕÅË¸");break;
	case 8:printf("ÕÅÓîÕÜ"); break;
	case 9:printf("°×½÷î£") ;break;
    }
	system("PAUSE");
	return 0;
}
