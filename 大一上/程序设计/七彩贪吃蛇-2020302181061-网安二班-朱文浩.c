#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>//windows编程头文件
#include <time.h>
#include <conio.h>//控制台输入输出头文件
#include<stdbool.h> 
#define SNAKESIZE 100//蛇的身体最大节数
#define MAPWIDTH 118 //宽度
#define MAPHEIGHT 29//高度
struct {//食物的坐标
	int x;
	int y;
}food; 
struct {//蛇的相关属性
	int speed;//蛇移动的速度
	int len;//蛇的长度
	int x[SNAKESIZE];//组成蛇身的每一个小方块中x的坐标
	int y[SNAKESIZE];//组成蛇身的每一个小方块中y的坐标
}snake;
void drawMap();//绘制游戏边框
void drawMap2();
void createFood();//随机生成食物
void keyDown(int m);//按键操作
void move(int*t,int q);//贪吃蛇移动 
bool snakeStatus();//蛇的状态
void gotoxy(int x, int y);//从控制台移动光标
void choose1();//游戏初始选择界面 
void failure(int*sorce);//游戏结束界面 
int color(int num)//上色 
{
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),num);
 return 0;
}

int key = 72;//表示蛇移动的方向，72为按下“↑”所代表的数字
int changeFlag = 0;//用来判断蛇是否吃掉了食物，这一步很重要，涉及到是否会有蛇身移动的效果以及蛇身增长的效果 
int q;//玩家选择贪吃蛇是否彩色 
int m;//玩家选择游戏模式：娱乐模式or挑战模式 
int n;//判断玩家是否重新挑战 
int pre_key;//记录上一次按键的方向 
void gotoxy(int x, int y)//将控制台光标移到（x,y）处
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawMap()
{
	int i;//打印上下边框
	for ( i = 0; i <= MAPWIDTH; i += 2)//i+=2是因为横向占用的是两个位置
	{
		gotoxy(i, 0);//将光标移动依次到(i,0)处打印上边框
		printf("■");
		gotoxy(i, MAPHEIGHT);//将光标移动依次到(i,MAPHEIGHT)处打印下边框
		printf("■");
	}
	for ( i = 1; i < MAPHEIGHT; i++)//打印左右边框
	{
		gotoxy(0, i);//将光标移动依次到(0,i)处打印左边框
		printf("■");
		gotoxy(MAPWIDTH, i);//将光标移动依次到(MAPWIDTH, i)处打印左边框
		printf("■");
	}
	while (1)//随机生成初试食物
	{
		srand((unsigned int)time(NULL));
		food.x = rand() % (MAPWIDTH - 4) + 2;
		food.y = rand() % (MAPHEIGHT - 2) + 1;
		//生成的食物横坐标的奇偶必须和初试时蛇头所在坐标的奇偶一致，因为一个字符占两个字节位置，若不一致
		//会导致吃食物的时候只吃到一半
		if (food.x % 2 == 0)
			break;
	}
	gotoxy(food.x, food.y);//将光标移到食物的坐标处打印食物
	printf("★");
	snake.len = 3;//初始化蛇的属性
	snake.speed = 200;
	//在屏幕中间生成蛇头
	snake.x[0] = MAPWIDTH / 2 + 1;//x坐标为偶数
	snake.y[0] = MAPHEIGHT / 2;
	gotoxy(snake.x[0], snake.y[0]);//打印蛇头
	printf("■");
	for (i = 1; i < snake.len; i++)//生成初试的蛇身
	{//蛇身的打印，纵坐标不变，横坐标为上一节蛇身的坐标值+2
		snake.x[i] = snake.x[i - 1] + 2;
		snake.y[i] = snake.y[i - 1];
		gotoxy(snake.x[i], snake.y[i]);
		printf("■");
	}//打印完蛇身后将光标移到屏幕最上方，避免光标在蛇身处一直闪烁
	gotoxy(MAPWIDTH - 2, 0);
	return;
}

void drawMap2(){
	int i;
	for(i=27;i<=MAPWIDTH-34;i+=2)
	{
		gotoxy(i, 12);
		printf("■");
		gotoxy(i, MAPHEIGHT-7);
		printf("■");
	}
		for ( i = 12; i < MAPHEIGHT-6; i++)
	{
		gotoxy(25, i);
		printf("■");
		gotoxy(MAPWIDTH-33, i);
		printf("■");
	}
}

void keyDown(int m)
{
	int pre_key ;
	pre_key= key;//记录前一个按键的方向
	if (_kbhit())//如果用户按下了键盘中的某个键
	{
		fflush(stdin);//清空缓冲区的字符
		//getch()读取方向键的时候，会返回两次，第一次调用返回0或者224，第二次调用返回的才是实际值
		key = _getch();//第一次调用返回的不是实际值
		if(key==0||key==224) key = _getch();//第二次调用返回实际值
	}
		if(m==1){
	    if(key==49){
		key=pre_key;
		snake.speed-=5;
	    }
    }
    if(key!=72&&key!=80&&key!=75&&key!=77){//防止玩家按错键而导致游戏异常 
    	key=pre_key;
	}
	//如果当前移动方向和前一次方向相反的话，把当前移动的方向改为前一次的方向
	if (pre_key == 72 && key == 80){
	    if(m==1) snake.speed+=5;
		key = 72;
		}
	if (pre_key == 80 && key == 72){
		key = 80;
		if(m==1) snake.speed+=5;
		}
	if (pre_key == 75 && key == 77){
		if(m==1) snake.speed+=5;
		key = 75;
	}
	if (pre_key == 77 && key == 75){
        if(m==1) snake.speed+=5;
		key = 77;
	}
	return;
}
void move(int*t,int q)
{
		/*
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

	if(snake.speed>=230) snake.speed=230;
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
	*t=((*t)++)%15+1;//变换蛇身颜色，同时防止蛇身颜色和背景颜色相同 
	gotoxy(snake.x[0], snake.y[0]);//打印出蛇头
	if(q==1) color(*t);
	printf("■"); 
	gotoxy(MAPWIDTH - 2, 0);
	changeFlag = 0;//由于目前没有吃到食物，changFlag值为0
	return;
 } 

void createFood(int*sorce)
{
	if (snake.x[0] == food.x && snake.y[0] == food.y)//蛇头碰到食物
	{
		while (1)//蛇头碰到食物即为要吃掉这个食物了，因此需要再次生成一个食物
		{
			int flag = 1;
			srand((unsigned int)time(NULL));
			food.x = rand() % (MAPWIDTH - 4) + 2;
			food.y = rand() % (MAPHEIGHT - 2) + 1;
            int i;
			for (i = 0; i < snake.len; i++)	//随机生成的食物不能在蛇的身体上
			{
				if (snake.x[i] == food.x && snake.y[i] == food.y)
				{
					flag = 0;
					break;
				}
			}
			if (flag && food.x % 2 == 0)//随机生成的食物不能横坐标为奇数，也不能在蛇身，否则重新生成
				break;
		}
		gotoxy(food.x, food.y);//绘制食物
		printf("★");
		snake.len++;//吃到食物，蛇身长度加1
		*sorce += 10;//每个食物得10分
		snake.speed -= 5;//随着吃的食物越来越多，速度会越来越快
		changeFlag = 1;//很重要，因为吃到了食物，就不用再擦除蛇尾的那一节，以此来造成蛇身体增长的效果
	}
	return;
}

bool snakeStatus()
{
	int gothroth=1;
	if (snake.y[0] == 0 || snake.y[0] == MAPHEIGHT)//蛇头碰到上下边界，游戏结束
		return false;
       if(gothroth==0)
        {
        	if (snake.x[0] == 0 || snake.x[0] == MAPWIDTH)//蛇头碰到上下边界，游戏结束
		    return false;
		}
		if(gothroth==1)
		{
			if(snake.x[0]==0)
			{
			snake.x[0]=MAPWIDTH-1;
			if(snake.x[0]==MAPWIDTH)
			snake.x[0]=1;
		}
	}
	int i;	//蛇头碰到蛇身，游戏结束
	for ( i = 1; i < snake.len; i++)
	{
		if (snake.x[i] == snake.x[0] && snake.y[i] == snake.y[0])
			return false;
	}
	return true;
}

void choose1()
{
	do{
			gotoxy(MAPWIDTH/4,MAPHEIGHT/2-1);
			do{
			printf("彩色贪吃蛇，输入1；正常贪吃蛇，输入2：");
			scanf("%d",&q);
		}while(q!=1&&q!=2);
			gotoxy(MAPWIDTH / 4, MAPHEIGHT / 2);
			printf("请选择贪吃蛇模式：娱乐模式，请输入1；挑战模式，请输入2\n");
	        gotoxy(MAPWIDTH / 4, MAPHEIGHT / 2+1);
	        scanf("%d",&m);
	        gotoxy(MAPWIDTH / 4, MAPHEIGHT / 2+2);
	        if(m!=1&&m!=2) 
			printf("wrong,请重新输入:");
	        else if(m==1) {
			printf("欢迎选择娱乐模式！\n");
			gotoxy(MAPWIDTH/4,MAPHEIGHT/2+3);
			printf("游戏规则：");
			gotoxy(MAPWIDTH/4,MAPHEIGHT/2+4);
			printf("加速请按1；减速请按相反方向键");
	        }
	        else if(m==2) printf("欢迎来到挑战模式！");
	        else if(m==2) printf("欢迎来到挑战模式！");
          }while(m!=1&&m!=2);
        gotoxy(MAPWIDTH/4,MAPHEIGHT/2+5);
        system("PAUSE");
	    system("cls");
 } 

void failure(int*sorce)
{
	gotoxy(MAPWIDTH / 3, MAPHEIGHT / 2);
	printf("Game Over!");
	gotoxy(MAPWIDTH / 3, MAPHEIGHT / 2 + 1);
	printf("本次游戏得分为：%d", *sorce);
	gotoxy(MAPWIDTH/3,MAPHEIGHT/2+2);
	printf("退出请输入0；重新挑战请输入1");
	gotoxy(MAPWIDTH/3,MAPHEIGHT/2+3);
	scanf("%d",&n);
	if(n==1){
		snake.len=3;
		snake.speed=200;
		*sorce=0;
	}
 } 

int main()
{
	int*t;//变换蛇身颜色 
	int*sorce;//记录玩家得分 
	t=(int*)malloc(sizeof(int));
	sorce=(int*)malloc(sizeof(int));
	*sorce=0;
	*t=1;
	do{
		system("cls");
		drawMap2();
		choose1();
	drawMap();
	while (1)
	{
		keyDown(m);
		move(t,q);
		if (!snakeStatus())
			break;
		createFood(sorce);
		Sleep(snake.speed);
	}
	color(15);
	drawMap2();
	failure(sorce);
	}while(n==1);
	free(t);
	free(sorce);
	gotoxy(MAPWIDTH/3,MAPHEIGHT/2+4);
	printf("您已结束游戏，欢迎下次挑战！\n");
	Sleep(2000);
	gotoxy(MAPWIDTH/3,MAPHEIGHT/2+5); 
	system("PAUSE");
	return 0;
}
