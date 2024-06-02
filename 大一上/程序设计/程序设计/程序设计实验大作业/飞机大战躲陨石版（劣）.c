#include<stdio.h>
#include<stdlib.h> 
#include<windows.h>
#include<conio.h>
#include<stdbool.h>
#define HIGH 31 //����߽�
#define WIDTH 53
#define BULLET_NUM 10//�ӵ��� 
#define ENEMY_NUM 5//�л���
#define BIGENEMY_NUM 5//��ʯ�� 

DWORD t1,t2,t3,t4;//���ӵ����л�����ʱ��� 
	int n;//�û�����1���¿�ʼ��Ϸ
	 
void modeset(int w,int h) //����̨�����С���� 
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD size = {w, h};
	SetConsoleScreenBufferSize(hOut,size);
	SMALL_RECT rc = {1,1, w, h};
	SetConsoleWindowInfo(hOut ,true ,&rc);
	system("cls");
}
void gotoxy(int x,int y)  			//����ƶ���(x,y)λ��
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
} 
void HideCursor() // �������ع��
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  // �ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

struct Plane                         //�ɻ����л����ӵ����� 
{
	int x;
	int y;
	bool flag;
	int score;
	int hp; 
} Player,Enemy[ENEMY_NUM],Bullet[BULLET_NUM],Bigenemy[BIGENEMY_NUM];

void startup()						//���ݳ�ʼ�� 
{
	int i;

	srand(GetTickCount());//�������rand���������� 
	t1=t2=t3=t4=GetTickCount();//��ȡϵͳ��������ǰ������������ 	
    //��ʼ����ҷɻ�����	
	Player.x=HIGH-3;				
	Player.y=WIDTH/2;
	Player.flag=true;
	Player.hp=3;
	Player.score=0;

	for(i=0;i<BULLET_NUM;i++)//��ʼ���ӵ����� 
		Bullet[i].flag=false;
	
	for(i=0;i<ENEMY_NUM;i++)//��ʼ���л����� 
		Enemy[i].flag=false;
	
	for(i=0;i<BIGENEMY_NUM;i++)
		Bigenemy[i].flag=false;
        		
	HideCursor();// �������ع��
}
void Endgame()
{
	int i;
	
	for(i=0;i<BULLET_NUM;i++)//��ʼ���ӵ����� 
		Bullet[i].flag=true;
	
	for(i=0;i<ENEMY_NUM;i++)//��ʼ���л����� 
		Enemy[i].flag=true;
	
	for(i=0;i<BIGENEMY_NUM;i++)
		Bigenemy[i].flag=true;
 } 

void show()    //������ʾ 
{
	int i,j;
	for(i=0;i<HIGH;i++)
	{
		for(j=0;j<WIDTH;j++)
		{
			if(Player.flag==false)
				break;
				
			else if((i==Player.x)&&(j==Player.y))		//�ɻ����� 
					printf("*");
				
			else if((i==Enemy[0].x)&&(j==Enemy[0].y)&&Enemy[0].flag==true)				//�л����� 
				printf("@");
	        else if((i==Enemy[1].x)&&(j==Enemy[1].y)&&Enemy[1].flag==true)				//�л����� 
				printf("@");
			else if((i==Enemy[2].x)&&(j==Enemy[2].y)&&Enemy[2].flag==true)				//�л����� 
				printf("@");
			else if((i==Enemy[3].x)&&(j==Enemy[3].y)&&Enemy[3].flag==true)				//�л����� 
				printf("@");
			else if((i==Enemy[4].x)&&(j==Enemy[4].y)&&Enemy[4].flag==true)				//�л����� 
				printf("@");
				
			else if((i==Bigenemy[0].x)&&(j==Bigenemy[0].y)&&Bigenemy[0].flag==true)				//��ʯ���� 
				printf("&");				
			else if((i==Bigenemy[1].x)&&(j==Bigenemy[1].y)&&Bigenemy[1].flag==true)				//��ʯ���� 
				printf("&");
			else if((i==Bigenemy[2].x)&&(j==Bigenemy[2].y)&&Bigenemy[2].flag==true)				//��ʯ���� 
				printf("&");
			else if((i==Bigenemy[3].x)&&(j==Bigenemy[3].y)&&Bigenemy[3].flag==true)				//��ʯ���� 
				printf("&");
			else if((i==Bigenemy[4].x)&&(j==Bigenemy[4].y)&&Bigenemy[4].flag==true)				//��ʯ���� 
				printf("&");								
				
			else if((i==Bullet[0].x)&&(j==Bullet[0].y)&&Bullet[0].flag==true)			//�ӵ����� 
					printf("|");
			else if((i==Bullet[1].x)&&(j==Bullet[1].y)&&Bullet[1].flag==true)			//�ӵ����� 
					printf("|");
			else if((i==Bullet[2].x)&&(j==Bullet[2].y)&&Bullet[2].flag==true)			//�ӵ����� 
					printf("|");
			else if((i==Bullet[3].x)&&(j==Bullet[3].y)&&Bullet[3].flag==true)			//�ӵ����� 
					printf("|");
			else if((i==Bullet[4].x)&&(j==Bullet[4].y)&&Bullet[4].flag==true)			//�ӵ����� 
					printf("|");
			else if((i==Bullet[5].x)&&(j==Bullet[5].y)&&Bullet[5].flag==true)			//�ӵ����� 
					printf("|");
			else if((i==Bullet[6].x)&&(j==Bullet[6].y)&&Bullet[6].flag==true)			//�ӵ����� 
					printf("|");
			else if((i==Bullet[7].x)&&(j==Bullet[7].y)&&Bullet[7].flag==true)			//�ӵ����� 
					printf("|");
			else if((i==Bullet[8].x)&&(j==Bullet[8].y)&&Bullet[8].flag==true)			//�ӵ����� 
					printf("|");
			else if((i==Bullet[9].x)&&(j==Bullet[9].y)&&Bullet[9].flag==true)			//�ӵ����� 
					printf("|");
											
			else if ((i==HIGH-1)||(i==0))				//��ӡ�߽� 
				printf("#");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("��������Ʒɻ��ƶ����ո����ӵ�\n"); 
	printf("@����л���������&������ʯ���޷����𣬽��ܶ��\n");
	printf("���ɻ���ֹʱ��л�����ʯӭ����ײ��ֱ������\n\n") ;
	printf("�÷�Ϊ��%d\n",Player.score);
	if(Player.hp>0)
	printf("Ѫ����%d\n",Player.hp);
	else	
	printf("Ѫ����0 \n");

	for(i=0;i<ENEMY_NUM;i++)//�жϷɻ��Ƿ�ײ�� ��Ϸ����
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
		Player.flag=false;							      //�ɻ�ײ�٣���Ϸ���� 
		printf("��Ϸ����!!!\n");
	}

}

void Creatbullet()//�����ӵ� 
{
	int i;
	for(i=0;i<BULLET_NUM;i++)
	{
		if(Bullet[i].flag==false)//�ж��ӵ��Ƿ���� 
		{
			Bullet[i].flag=true;
			Bullet[i].x=Player.x;
			Bullet[i].y=Player.y;
			break;
		}		
	}
}
void Bulletmove()//�ӵ�����Ч�� 
{
	int i;
	for(i=0;i<BULLET_NUM;i++)
	{
		if(Bullet[i].flag==true)
		{					
		   Bullet[i].x--; 
		   
		   if(Bullet[i].x<=-1)   //����ӵ������߽磬�򷵻��������
		   {
		   	Bullet[i].flag=false;
		   }
	    }
	}
}

void Createnemy()  //�����л�
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
void Enemymove()//�л��ƶ� 
{
	int i,j;
	static int speed=0;
	
	if(speed<7)//���Ƶл��ƶ��ٶ� 
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
		if(Enemy[i].x>=HIGH) //����л������߽磬�򷵻�������� 
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

void Shootenemy()//�ӵ����зɻ� 
{
	int i,j;	
	for(i=0;i<BULLET_NUM;i++)
	 for(j=0;j<ENEMY_NUM;j++)
	 {
       if((Bullet[i].x==Enemy[j].x)&&(Bullet[i].y==Enemy[j].y)&&Bullet[i].flag == true && Enemy[j].flag == true)	  //�ж��ӵ��Ƿ����ел� 	 
	    {
		  Player.score++;	  
          //�ӵ����к��ӵ���л�����λ�� 
	      Bullet[i].x=-2;	            
		  Enemy[j].x=-1;
		  Enemy[j].y=2+rand()%(WIDTH-3);
		}
	 }	 	 
}

void Playercontrol()      //��ҿ��Ʒɻ��ƶ� 
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
	if(GetAsyncKeyState(VK_SPACE)&&t2-t1>100)// t1,t2ʱ�������ӵ�����ʱ��� 
	{
        Creatbullet();
        t1=t2;
	}
	    t2=GetTickCount();
	    
	if(t4-t3>rand()%500+1200)// t3,t4ʱ�����Ƶл�����ʱ���
	{
		Createnemy();
		t3=t4;
	}
    t4=GetTickCount();    
		Enemymove();
        Bulletmove();      
}
void Regame()          //���¿�ʼ��Ϸ 
{
	printf("��Ҫ���¿�ʼ������1��");
	scanf("%d",&n);
}

int main()
{	
  do{ 
    n=0;
  	system("cls");
	modeset(60,40);      //���ڿ���̨���ڴ�С 
	system("color 03");   //���ڱ�����ǰ����ɫ 
	startup();            //ϵͳ��ʼ�� 
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

