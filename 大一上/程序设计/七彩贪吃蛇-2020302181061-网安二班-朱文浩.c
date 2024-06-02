#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>//windows���ͷ�ļ�
#include <time.h>
#include <conio.h>//����̨�������ͷ�ļ�
#include<stdbool.h> 
#define SNAKESIZE 100//�ߵ�����������
#define MAPWIDTH 118 //���
#define MAPHEIGHT 29//�߶�
struct {//ʳ�������
	int x;
	int y;
}food; 
struct {//�ߵ��������
	int speed;//���ƶ����ٶ�
	int len;//�ߵĳ���
	int x[SNAKESIZE];//��������ÿһ��С������x������
	int y[SNAKESIZE];//��������ÿһ��С������y������
}snake;
void drawMap();//������Ϸ�߿�
void drawMap2();
void createFood();//�������ʳ��
void keyDown(int m);//��������
void move(int*t,int q);//̰�����ƶ� 
bool snakeStatus();//�ߵ�״̬
void gotoxy(int x, int y);//�ӿ���̨�ƶ����
void choose1();//��Ϸ��ʼѡ����� 
void failure(int*sorce);//��Ϸ�������� 
int color(int num)//��ɫ 
{
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),num);
 return 0;
}

int key = 72;//��ʾ���ƶ��ķ���72Ϊ���¡����������������
int changeFlag = 0;//�����ж����Ƿ�Ե���ʳ���һ������Ҫ���漰���Ƿ���������ƶ���Ч���Լ�����������Ч�� 
int q;//���ѡ��̰�����Ƿ��ɫ 
int m;//���ѡ����Ϸģʽ������ģʽor��սģʽ 
int n;//�ж�����Ƿ�������ս 
int pre_key;//��¼��һ�ΰ����ķ��� 
void gotoxy(int x, int y)//������̨����Ƶ���x,y����
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawMap()
{
	int i;//��ӡ���±߿�
	for ( i = 0; i <= MAPWIDTH; i += 2)//i+=2����Ϊ����ռ�õ�������λ��
	{
		gotoxy(i, 0);//������ƶ����ε�(i,0)����ӡ�ϱ߿�
		printf("��");
		gotoxy(i, MAPHEIGHT);//������ƶ����ε�(i,MAPHEIGHT)����ӡ�±߿�
		printf("��");
	}
	for ( i = 1; i < MAPHEIGHT; i++)//��ӡ���ұ߿�
	{
		gotoxy(0, i);//������ƶ����ε�(0,i)����ӡ��߿�
		printf("��");
		gotoxy(MAPWIDTH, i);//������ƶ����ε�(MAPWIDTH, i)����ӡ��߿�
		printf("��");
	}
	while (1)//������ɳ���ʳ��
	{
		srand((unsigned int)time(NULL));
		food.x = rand() % (MAPWIDTH - 4) + 2;
		food.y = rand() % (MAPHEIGHT - 2) + 1;
		//���ɵ�ʳ����������ż����ͳ���ʱ��ͷ�����������żһ�£���Ϊһ���ַ�ռ�����ֽ�λ�ã�����һ��
		//�ᵼ�³�ʳ���ʱ��ֻ�Ե�һ��
		if (food.x % 2 == 0)
			break;
	}
	gotoxy(food.x, food.y);//������Ƶ�ʳ������괦��ӡʳ��
	printf("��");
	snake.len = 3;//��ʼ���ߵ�����
	snake.speed = 200;
	//����Ļ�м�������ͷ
	snake.x[0] = MAPWIDTH / 2 + 1;//x����Ϊż��
	snake.y[0] = MAPHEIGHT / 2;
	gotoxy(snake.x[0], snake.y[0]);//��ӡ��ͷ
	printf("��");
	for (i = 1; i < snake.len; i++)//���ɳ��Ե�����
	{//����Ĵ�ӡ�������겻�䣬������Ϊ��һ�����������ֵ+2
		snake.x[i] = snake.x[i - 1] + 2;
		snake.y[i] = snake.y[i - 1];
		gotoxy(snake.x[i], snake.y[i]);
		printf("��");
	}//��ӡ������󽫹���Ƶ���Ļ���Ϸ���������������һֱ��˸
	gotoxy(MAPWIDTH - 2, 0);
	return;
}

void drawMap2(){
	int i;
	for(i=27;i<=MAPWIDTH-34;i+=2)
	{
		gotoxy(i, 12);
		printf("��");
		gotoxy(i, MAPHEIGHT-7);
		printf("��");
	}
		for ( i = 12; i < MAPHEIGHT-6; i++)
	{
		gotoxy(25, i);
		printf("��");
		gotoxy(MAPWIDTH-33, i);
		printf("��");
	}
}

void keyDown(int m)
{
	int pre_key ;
	pre_key= key;//��¼ǰһ�������ķ���
	if (_kbhit())//����û������˼����е�ĳ����
	{
		fflush(stdin);//��ջ��������ַ�
		//getch()��ȡ�������ʱ�򣬻᷵�����Σ���һ�ε��÷���0����224���ڶ��ε��÷��صĲ���ʵ��ֵ
		key = _getch();//��һ�ε��÷��صĲ���ʵ��ֵ
		if(key==0||key==224) key = _getch();//�ڶ��ε��÷���ʵ��ֵ
	}
		if(m==1){
	    if(key==49){
		key=pre_key;
		snake.speed-=5;
	    }
    }
    if(key!=72&&key!=80&&key!=75&&key!=77){//��ֹ��Ұ������������Ϸ�쳣 
    	key=pre_key;
	}
	//�����ǰ�ƶ������ǰһ�η����෴�Ļ����ѵ�ǰ�ƶ��ķ����Ϊǰһ�εķ���
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
	*���ƶ�ʱ���Ȳ�ȥ��β��һ��
	*changeFlagΪ0������ʱû�гԵ�ʳ����ÿ��һ����Ҫ��������β���Դ�Ӫ��һ���ƶ���Ч��
	*Ϊ1�����Ե���ʳ��Ͳ���Ҫ������β���Դ�Ӫ��һ������������Ч��
	*/
	if (changeFlag == 0)
	{
		gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
		printf("  ");//����β������ո񼴲�ȥ��β
	}
    int i;
	for ( i = snake.len - 1; i > 0; i--)//���ߵ�ÿһ��������ǰ�ƶ�һ�ڣ���ͷ���⣩
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}

	if(snake.speed>=230) snake.speed=230;
	switch (key)
	{
	case 75:
		snake.x[0] -= 2;//����
		break;
	case 77:
		snake.x[0] += 2;//����
		break;
	case 72:
		snake.y[0]--;//����
		break;
	case 80:
		snake.y[0]++;//����
		break;
	}
	*t=((*t)++)%15+1;//�任������ɫ��ͬʱ��ֹ������ɫ�ͱ�����ɫ��ͬ 
	gotoxy(snake.x[0], snake.y[0]);//��ӡ����ͷ
	if(q==1) color(*t);
	printf("��"); 
	gotoxy(MAPWIDTH - 2, 0);
	changeFlag = 0;//����Ŀǰû�гԵ�ʳ�changFlagֵΪ0
	return;
 } 

void createFood(int*sorce)
{
	if (snake.x[0] == food.x && snake.y[0] == food.y)//��ͷ����ʳ��
	{
		while (1)//��ͷ����ʳ�ＴΪҪ�Ե����ʳ���ˣ������Ҫ�ٴ�����һ��ʳ��
		{
			int flag = 1;
			srand((unsigned int)time(NULL));
			food.x = rand() % (MAPWIDTH - 4) + 2;
			food.y = rand() % (MAPHEIGHT - 2) + 1;
            int i;
			for (i = 0; i < snake.len; i++)	//������ɵ�ʳ�ﲻ�����ߵ�������
			{
				if (snake.x[i] == food.x && snake.y[i] == food.y)
				{
					flag = 0;
					break;
				}
			}
			if (flag && food.x % 2 == 0)//������ɵ�ʳ�ﲻ�ܺ�����Ϊ������Ҳ����������������������
				break;
		}
		gotoxy(food.x, food.y);//����ʳ��
		printf("��");
		snake.len++;//�Ե�ʳ������ȼ�1
		*sorce += 10;//ÿ��ʳ���10��
		snake.speed -= 5;//���ųԵ�ʳ��Խ��Խ�࣬�ٶȻ�Խ��Խ��
		changeFlag = 1;//����Ҫ����Ϊ�Ե���ʳ��Ͳ����ٲ�����β����һ�ڣ��Դ������������������Ч��
	}
	return;
}

bool snakeStatus()
{
	int gothroth=1;
	if (snake.y[0] == 0 || snake.y[0] == MAPHEIGHT)//��ͷ�������±߽磬��Ϸ����
		return false;
       if(gothroth==0)
        {
        	if (snake.x[0] == 0 || snake.x[0] == MAPWIDTH)//��ͷ�������±߽磬��Ϸ����
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
	int i;	//��ͷ����������Ϸ����
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
			printf("��ɫ̰���ߣ�����1������̰���ߣ�����2��");
			scanf("%d",&q);
		}while(q!=1&&q!=2);
			gotoxy(MAPWIDTH / 4, MAPHEIGHT / 2);
			printf("��ѡ��̰����ģʽ������ģʽ��������1����սģʽ��������2\n");
	        gotoxy(MAPWIDTH / 4, MAPHEIGHT / 2+1);
	        scanf("%d",&m);
	        gotoxy(MAPWIDTH / 4, MAPHEIGHT / 2+2);
	        if(m!=1&&m!=2) 
			printf("wrong,����������:");
	        else if(m==1) {
			printf("��ӭѡ������ģʽ��\n");
			gotoxy(MAPWIDTH/4,MAPHEIGHT/2+3);
			printf("��Ϸ����");
			gotoxy(MAPWIDTH/4,MAPHEIGHT/2+4);
			printf("�����밴1�������밴�෴�����");
	        }
	        else if(m==2) printf("��ӭ������սģʽ��");
	        else if(m==2) printf("��ӭ������սģʽ��");
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
	printf("������Ϸ�÷�Ϊ��%d", *sorce);
	gotoxy(MAPWIDTH/3,MAPHEIGHT/2+2);
	printf("�˳�������0��������ս������1");
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
	int*t;//�任������ɫ 
	int*sorce;//��¼��ҵ÷� 
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
	printf("���ѽ�����Ϸ����ӭ�´���ս��\n");
	Sleep(2000);
	gotoxy(MAPWIDTH/3,MAPHEIGHT/2+5); 
	system("PAUSE");
	return 0;
}
