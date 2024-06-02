#include<stdio.h>
#include<stdlib.h> 
#include<windows.h>
#include<conio.h>
#include<stdbool.h>
#define HIGH 31 //定义边界
#define WIDTH 53
#define BULLET_NUM 10//子弹数 
#define ENEMY_NUM 5//敌机数
#define BIGENEMY_NUM 5//陨石数 

DWORD t1,t2,t3,t4;//给子弹、敌机发射时间差 
	int n;//用户输入1重新开始游戏
	 
void modeset(int w,int h) //控制台界面大小设置 
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD size = {w, h};
	SetConsoleScreenBufferSize(hOut,size);
	SMALL_RECT rc = {1,1, w, h};
	SetConsoleWindowInfo(hOut ,true ,&rc);
	system("cls");
}
void gotoxy(int x,int y)  			//光标移动到(x,y)位置
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
} 
void HideCursor() // 用于隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  // 第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

struct Plane                         //飞机、敌机、子弹属性 
{
	int x;
	int y;
	bool flag;
	int score;
	int hp; 
} Player,Enemy[ENEMY_NUM],Bullet[BULLET_NUM],Bigenemy[BIGENEMY_NUM];

void startup()						//数据初始化 
{
	int i;

	srand(GetTickCount());//给随机数rand（）埋种子 
	t1=t2=t3=t4=GetTickCount();//获取系统开机到当前所经过毫秒数 	
    //初始化玩家飞机数据	
	Player.x=HIGH-3;				
	Player.y=WIDTH/2;
	Player.flag=true;
	Player.hp=3;
	Player.score=0;

	for(i=0;i<BULLET_NUM;i++)//初始化子弹数据 
		Bullet[i].flag=false;
	
	for(i=0;i<ENEMY_NUM;i++)//初始化敌机数据 
		Enemy[i].flag=false;
	
	for(i=0;i<BIGENEMY_NUM;i++)
		Bigenemy[i].flag=false;
        		
	HideCursor();// 用于隐藏光标
}
void Endgame()
{
	int i;
	
	for(i=0;i<BULLET_NUM;i++)//初始化子弹数据 
		Bullet[i].flag=true;
	
	for(i=0;i<ENEMY_NUM;i++)//初始化敌机数据 
		Enemy[i].flag=true;
	
	for(i=0;i<BIGENEMY_NUM;i++)
		Bigenemy[i].flag=true;
 } 

void show()    //界面显示 
{
	int i,j;
	for(i=0;i<HIGH;i++)
	{
		for(j=0;j<WIDTH;j++)
		{
			if(Player.flag==false)
				break;
				
			else if((i==Player.x)&&(j==Player.y))		//飞机坐标 
					printf("*");
				
			else if((i==Enemy[0].x)&&(j==Enemy[0].y)&&Enemy[0].flag==true)				//敌机坐标 
				printf("@");
	        else if((i==Enemy[1].x)&&(j==Enemy[1].y)&&Enemy[1].flag==true)				//敌机坐标 
				printf("@");
			else if((i==Enemy[2].x)&&(j==Enemy[2].y)&&Enemy[2].flag==true)				//敌机坐标 
				printf("@");
			else if((i==Enemy[3].x)&&(j==Enemy[3].y)&&Enemy[3].flag==true)				//敌机坐标 
				printf("@");
			else if((i==Enemy[4].x)&&(j==Enemy[4].y)&&Enemy[4].flag==true)				//敌机坐标 
				printf("@");
				
			else if((i==Bigenemy[0].x)&&(j==Bigenemy[0].y)&&Bigenemy[0].flag==true)				//陨石坐标 
				printf("&");				
			else if((i==Bigenemy[1].x)&&(j==Bigenemy[1].y)&&Bigenemy[1].flag==true)				//陨石坐标 
				printf("&");
			else if((i==Bigenemy[2].x)&&(j==Bigenemy[2].y)&&Bigenemy[2].flag==true)				//陨石坐标 
				printf("&");
			else if((i==Bigenemy[3].x)&&(j==Bigenemy[3].y)&&Bigenemy[3].flag==true)				//陨石坐标 
				printf("&");
			else if((i==Bigenemy[4].x)&&(j==Bigenemy[4].y)&&Bigenemy[4].flag==true)				//陨石坐标 
				printf("&");								
				
			else if((i==Bullet[0].x)&&(j==Bullet[0].y)&&Bullet[0].flag==true)			//子弹坐标 
					printf("|");
			else if((i==Bullet[1].x)&&(j==Bullet[1].y)&&Bullet[1].flag==true)			//子弹坐标 
					printf("|");
			else if((i==Bullet[2].x)&&(j==Bullet[2].y)&&Bullet[2].flag==true)			//子弹坐标 
					printf("|");
			else if((i==Bullet[3].x)&&(j==Bullet[3].y)&&Bullet[3].flag==true)			//子弹坐标 
					printf("|");
			else if((i==Bullet[4].x)&&(j==Bullet[4].y)&&Bullet[4].flag==true)			//子弹坐标 
					printf("|");
			else if((i==Bullet[5].x)&&(j==Bullet[5].y)&&Bullet[5].flag==true)			//子弹坐标 
					printf("|");
			else if((i==Bullet[6].x)&&(j==Bullet[6].y)&&Bullet[6].flag==true)			//子弹坐标 
					printf("|");
			else if((i==Bullet[7].x)&&(j==Bullet[7].y)&&Bullet[7].flag==true)			//子弹坐标 
					printf("|");
			else if((i==Bullet[8].x)&&(j==Bullet[8].y)&&Bullet[8].flag==true)			//子弹坐标 
					printf("|");
			else if((i==Bullet[9].x)&&(j==Bullet[9].y)&&Bullet[9].flag==true)			//子弹坐标 
					printf("|");
											
			else if ((i==HIGH-1)||(i==0))				//打印边界 
				printf("#");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("方向键控制飞机移动，空格发射子弹\n"); 
	printf("@代表敌机，可消灭；&代表陨石，无法消灭，仅能躲避\n");
	printf("若飞机静止时与敌机或陨石迎面相撞则直接死亡\n\n") ;
	printf("得分为：%d\n",Player.score);
	if(Player.hp>0)
	printf("血量：%d\n",Player.hp);
	else	
	printf("血量：0 \n");

	for(i=0;i<ENEMY_NUM;i++)//判断飞机是否撞毁 游戏结束
	{
	   if((Player.x==Enemy[i].x)&&(Player.y==Enemy[i].y))
	   Player.hp--;
	}
    for(j=0;j<BIGENEMY_NUM;j++)
    {
    	if((Player.x==Bigenemy[j].x)&&(Player.y==Bigenemy[j].y))
    	Player.hp--;
	} 
	
	if(Player.hp<1)
	{
		Player.flag=false;							      //飞机撞毁，游戏结束 
		printf("游戏结束!!!\n");
	}

}

void Creatbullet()//创建子弹 
{
	int i;
	for(i=0;i<BULLET_NUM;i++)
	{
		if(Bullet[i].flag==false)//判断子弹是否存在 
		{
			Bullet[i].flag=true;
			Bullet[i].x=Player.x;
			Bullet[i].y=Player.y;
			break;
		}		
	}
}
void Bulletmove()//子弹上升效果 
{
	int i;
	for(i=0;i<BULLET_NUM;i++)
	{
		if(Bullet[i].flag==true)
		{					
		   Bullet[i].x--; 
		   
		   if(Bullet[i].x<=-1)   //如果子弹超出边界，则返回重新输出
		   {
		   	Bullet[i].flag=false;
		   }
	    }
	}
}

void Createnemy()  //创建敌机
{
	int i;
	for(i=0;i<ENEMY_NUM;i++)
	{
		if(Enemy[i].flag==false)
		{
			Enemy[i].y=2+rand()%(WIDTH-3);
			Enemy[i].x=-1;
            Enemy[i].flag = true;
            break;		
		}
	}
	
	for(i=0;i<BIGENEMY_NUM;i++)
	{
		if(Bigenemy[i].flag==false)
		{
		    Bigenemy[i].y=2+rand()%(WIDTH-3);
			Bigenemy[i].x=-1;
			Bigenemy[i].flag = true;
			break;	
		}
	}	
}
void Enemymove()//敌机移动 
{
	int i,j;
	static int speed=0;
	
	if(speed<7)//控制敌机移动速度 
	  speed++;
	if(speed==7)
 {
	for(i=0;i<ENEMY_NUM;i++)
	 {
		if(Enemy[i].flag==true)
		  {					
		    if(Enemy[i].x<HIGH)
		   	   {
		   		Enemy[i].x++;
		   	   }
			    speed=0;
		   }		   
		if(Enemy[i].x>=HIGH) //如果敌机超出边界，则返回重新输出 
		  Enemy[i].flag=false; 
	 }
	 
	 for(j=0;j<BIGENEMY_NUM;j++)
	 {
	 	if(Bigenemy[j].flag==true)
	 	{
	 	   if(Bigenemy[j].x<HIGH)
				Bigenemy[j].x++;
				
			speed=0;	
		}
		if(Bigenemy[j].x>=HIGH)
		 Bigenemy[j].flag=false;
	 }	    
 }
}

void Shootenemy()//子弹命中飞机 
{
	int i,j;	
	for(i=0;i<BULLET_NUM;i++)
	 for(j=0;j<ENEMY_NUM;j++)
	 {
       if((Bullet[i].x==Enemy[j].x)&&(Bullet[i].y==Enemy[j].y)&&Bullet[i].flag == true && Enemy[j].flag == true)	  //判断子弹是否命中敌机 	 
	    {
		  Player.score++;	  
          //子弹命中后，子弹与敌机重置位置 
	      Bullet[i].x=-2;	            
		  Enemy[j].x=-1;
		  Enemy[j].y=2+rand()%(WIDTH-3);
		}
	 }	 	 
}

void Playercontrol()      //玩家控制飞机移动 
{
	if(GetAsyncKeyState(VK_UP)&&Player.x>1)
	{
		Player.x--;
	}	
	if(GetAsyncKeyState(VK_DOWN)&&Player.x<HIGH-2)
	{
		Player.x++;
	}
	if(GetAsyncKeyState(VK_LEFT)&&Player.y>1)
	{
		Player.y--;
	}	
	if(GetAsyncKeyState(VK_RIGHT)&&Player.y<WIDTH-2)
	{
		Player.y++;
	}
	if(GetAsyncKeyState(VK_SPACE)&&t2-t1>100)// t1,t2时间差控制子弹发射时间差 
	{
        Creatbullet();
        t1=t2;
	}
	    t2=GetTickCount();
	    
	if(t4-t3>rand()%500+1200)// t3,t4时间差控制敌机出现时间差
	{
		Createnemy();
		t3=t4;
	}
    t4=GetTickCount();    
		Enemymove();
        Bulletmove();      
}
void Regame()          //重新开始游戏 
{
	printf("若要重新开始请输入1：");
	scanf("%d",&n);
}

int main()
{	
  do{ 
    n=0;
  	system("cls");
	modeset(60,40);      //调节控制台窗口大小 
	system("color 03");   //调节背景、前景颜色 
	startup();            //系统初始化 
	while(1)
	{
		gotoxy(0,0);
		show();
		if(Player.flag==false)
		break;
		Shootenemy();
		Playercontrol();			
	}
	Regame();
	Endgame();
   }while(n==1);
 
	return 0;
}

