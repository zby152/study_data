#include<stdio.h>
#include<stdlib.h>
#include <Windows.h>//windows编程头文件
#include <time.h>
#include <conio.h>//控制台输入输出头文件
#include<stdbool.h> 
#define SNAKESIZE 100//蛇的身体最大节数
#define MAPWIDTH 118 //宽度
#define MAPHEIGHT 29//高度
int changeFlag,key=72,hard;
struct {           //食物的坐标
	    int x;
	    int y;
    }food; 
struct {//蛇的相关属性
	    int speed;//蛇移动的速度
	    int len;//蛇的长度
	    int x[SNAKESIZE];//组成蛇身的每一个小方块中x的坐标
	    int y[SNAKESIZE];//组成蛇身的每一个小方块中y的坐标
    }snake;
void gotoxy(int x, int y)     //将控制台光标移到（x,y）处
    {
	    COORD coord;
	    coord.X = x;
	    coord.Y = y;
	    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
void creatfood(int *score)
{
	//第一个食物的创建在drawmap之中//
	int i,flag;
	switch(snake.x[0]==food.x&&snake.y[0]==food.y){
		case 1: do{
			    flag=1;
		        srand((unsigned int)time(NULL));
		        food.x = rand() % (MAPWIDTH - 4) + 2;
		        food.y = rand() % (MAPHEIGHT - 2) + 1;
		        for(i=0;i<snake.len;i++){
		        	if(snake.x[i]==food.x&&snake.y[i]==food.y)
		        	   flag=0;
				}
		        }while(food.x%2!=0&&flag==1);
		        gotoxy(food.x,food.y);
		        printf("㊣");
		        snake.len++;
		        *score += 10;
				if(hard==1){
		        snake.speed -= 5;
				} 
		        changeFlag = 1;
		        break;
	} 
	return;
}
void keydown()
{
	//72对应上，80对应下，75对应←，77对应→ 
	int pre_key ;
	pre_key= key;//记录前一个按键的方向
	if (_kbhit())//如果用户按下了键盘中的某个键
	{
		fflush(stdin);//清空缓冲区的字符
		//getch()读取方向键的时候，会返回两次，第一次调用返回0或者224，第二次调用返回的才是实际值
		key = _getch();//第一次调用返回的不是实际值
		if(key==0||key==224) key = _getch();//第二次调用返回实际值
	}
    if(key!=72&&key!=80&&key!=75&&key!=77){//防止玩家按错键而导致游戏异常 
    	key=pre_key;
	}
	//如果当前移动方向和前一次方向相反的话，把当前移动的方向改为前一次的方向
	if (pre_key == 72 && key == 80){
		key = 72;
		}
	if (pre_key == 80 && key == 72){
		key = 80;
		}
	if (pre_key == 75 && key == 77){
		key = 75;
	}
	if (pre_key == 77 && key == 75){
		key = 77;
	}
	return;
}
void move()
{	/*
	*蛇移动时候先擦去蛇尾的一节
	*changeFlag为0表明此时没有吃到食物，因此每走一步就要擦除掉蛇尾，以此营造一个移动的效果
	*为1表明吃到了食物，就不需要擦除蛇尾，以此营造一个蛇身增长的效果
	*/
	if (changeFlag == 0)
	{
		gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
		printf("  ");//在蛇尾处输出空格即擦去蛇尾
	}
    int i;
	for ( i = snake.len - 1; i > 0; i--)//将蛇的每一节依次向前移动一节（蛇头除外）
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}
	//if(snake.speed>=230) snake.speed=230;
	switch (key)
	{
	case 75:
		snake.x[0] -= 2;//往左
		break;
	case 77:
		snake.x[0] += 2;//往右
		break;
	case 72:
		snake.y[0]--;//往上
		break;
	case 80:
		snake.y[0]++;//往下
		break;
	}
	//*t=((*t)++)%15+1;//变换蛇身颜色，同时防止蛇身颜色和背景颜色相同 
	gotoxy(snake.x[0], snake.y[0]);//打印出蛇头
	printf("■"); 
	gotoxy(MAPWIDTH - 2, 0);
	changeFlag = 0;//由于目前没有吃到食物，changFlag值为0
	return;
 }     
bool die()//返回值为false游戏结束 
    {	
	    int i;
    	if (snake.y[0] == 0 || snake.y[0] == MAPHEIGHT)//蛇头碰到上下边界，游戏结束
		    return false;
        if(hard==0||hard==1)
        {
        	if (snake.x[0] == 0 || snake.x[0] == MAPWIDTH)
		    return false;
		}
		if(hard==2)
		{
		if(snake.x[0]==0)
			{
			snake.x[0]=MAPWIDTH;
	        gotoxy(snake.x[0]+1,snake.y[0]);
	        gotoxy(0,snake.y[0]);
			printf("  "); 
			}
		else if(snake.x[0]==MAPWIDTH){
			snake.x[0]=0;
			gotoxy(snake.x[0],snake.y[0]);
			gotoxy(MAPWIDTH,snake.y[0]);
			printf("  ");
			}
}
	    for ( i = 1; i < snake.len; i++)//蛇头咬蛇尾，游戏结束 
	    {
		    if (snake.x[i] == snake.x[0] && snake.y[i] == snake.y[0])
			    return false;
	    }
	    return true;
    }
void failure(int *score)
    {
    	system("cls");
    	gotoxy(MAPWIDTH/2,(MAPHEIGHT-1)/2);
        printf("Game Over!");
        gotoxy(MAPWIDTH/2,(MAPHEIGHT-1)/2+2);
	    printf("本次游戏得分为：%d\n", *score);
	    gotoxy(MAPWIDTH/2,(MAPHEIGHT-1)/2+4);
	    printf("按任意键重新开始游戏，按ESC结束游戏！");
	    char a;
	    a=getch();
	    if(a!=0x1b)
		{
		system("cls");
		main();
		}
	} 
void drawmap()//创造地图函数 
    {
    	//地图一仅有边框 地图三也仅有边框但会加速。 
        int i;
	    if(hard==0||hard==1)
	    {
	        for(i=0;i<=MAPWIDTH;i=i+2)
	        {
		        gotoxy(i, 0);
		        printf("■");
		        gotoxy(i, MAPHEIGHT);
		        printf("■");
	        }
	        for(i=1;i<MAPHEIGHT;i++)
	        {
	            gotoxy(0, i);
	            printf("■");
	            gotoxy(MAPWIDTH, i);
	            printf("■");
	        }
	    }
        else if(hard==2)//地图二可穿墙地图 
        {
            for(i=0;i<=MAPWIDTH;i=i+2)
	        {
		        gotoxy(i, 0);
		        printf("■");
		        gotoxy(i, MAPHEIGHT);
		        printf("■");
	        }
	    }  
	while (1)//随机生成初试食物
	{
		srand((unsigned int)time(NULL));
		food.x = rand() % (MAPWIDTH - 4) + 2;
		food.y = rand() % (MAPHEIGHT - 2) + 1;
		if (food.x % 2 == 0)
			break;
	}
	gotoxy(food.x, food.y);//将光标移到食物的坐标处打印食物
	printf("㊣");
	snake.len = 3;//初始化蛇的长度与速度 
	snake.speed = 200;
	//在屏幕中间生成蛇头
	snake.x[0] = MAPWIDTH / 2 + 1;
	snake.y[0] = MAPHEIGHT / 2;
	gotoxy(snake.x[0], snake.y[0]);//打印蛇头
	printf("■");
	for (i = 1; i < snake.len; i++)//生成初试的蛇身
	{//蛇身的打印，纵坐标不变，横坐标为上一节蛇身的坐标值+2
		snake.x[i] = snake.x[i - 1] + 2;
		snake.y[i] = snake.y[i - 1];
		gotoxy(snake.x[i], snake.y[i]);
		printf("■");
	}
	gotoxy(MAPWIDTH - 2, 0);
    }
int menu()
{
	char *option[]={"普通模式","困难模式","穿墙模式"};
	char key = 0,a=0;
	int i, select = 0,j=0,k=0,p=0;
	HANDLE ohandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X=58;
	coord.Y=14;
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(ConsoleHandle, coord);
	SetConsoleTextAttribute(ohandle,FOREGROUND_GREEN|FOREGROUND_BLUE);
	printf("欢迎来到游戏“贪吃蛇”！");
	key=getch();
	if(key!=' ');
	system("cls");
	while(true){
		for(i=0;i<3;i++){         //共3个选项
		    coord.X=58;
			coord.Y=14+i+1; 
			HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
         //设置光标位置
         SetConsoleCursorPosition(ConsoleHandle, coord);
			if(i==select)//设置焦点高亮
				SetConsoleTextAttribute(ohandle,BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
			else if(i==select+1)//恢复设置
				SetConsoleTextAttribute(ohandle,FOREGROUND_GREEN|FOREGROUND_BLUE );
			puts(option[i]);
		}
		SetConsoleTextAttribute(ohandle,FOREGROUND_GREEN|FOREGROUND_BLUE );//恢复设置
		key=getch();
		if(key==0x1b)  //ESC 键
			return 0;
		if(key==0xd)  //Enter 键
			break;
		if(key<0){  //非ascii码键2个字节
			key=getch();
			switch(MapVirtualKey(key,1)){
			case VK_UP:
				select = (select+2)%3,k++;//焦点上移，减一，滚动选择，共3个选项
				break;
			case VK_DOWN:
				select = (select+1)%3,p++;//焦点下移，加一
				break;
			}
		}
		system("cls");
	}
	if(p>k)
	j=(p-k)%3;
	else 
	if((k-p)%3!=0)
	j=3-(k-p)%3;
	else j=0;
	system("cls");
	coord.X=58;
	coord.Y=15; 
    SetConsoleCursorPosition(ConsoleHandle, coord);
	printf("你选择: %s\n",option[select]);
	a=getch();
	if(a!=0x1b)
	{
	system("cls");
	coord.X=28;
	coord.Y=15; 
    SetConsoleCursorPosition(ConsoleHandle, coord);
	switch(j)
	{
		case 0:printf("普通模式下蛇的移动速度较慢");break;
		case 1:printf("困难模式下蛇的移动速度较快");break;
		case 2:printf("穿墙模式下蛇可以任意穿梭左右方向的墙体，当蛇头遇到上下墙体或蛇身时，游戏结束");
	}
	}
	return j; 
}
int main()
    {
	    int *score;
	    score=(int*)malloc(sizeof(int));
	    *score=0;

	    hard=menu();
	    char b;
	    b=getch();
	    if(b!=0x1b)
	    system("cls");
	    drawmap();
	    while (1)
	    {
		keydown();
		move();
		if (!die())
			break;
		creatfood(score);
		Sleep(snake.speed);
	    }
	    failure(score);
	    free(score);
        system("PAUSE");
	    return 0;
    }
