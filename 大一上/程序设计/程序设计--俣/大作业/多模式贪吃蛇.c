#include<stdio.h>
#include<stdlib.h>
#include <Windows.h>//windows���ͷ�ļ�
#include <time.h>
#include <conio.h>//����̨�������ͷ�ļ�
#include<stdbool.h> 
#define SNAKESIZE 100//�ߵ�����������
#define MAPWIDTH 118 //���
#define MAPHEIGHT 29//�߶�
int changeFlag,key=72,hard;
struct {           //ʳ�������
	    int x;
	    int y;
    }food; 
struct {//�ߵ��������
	    int speed;//���ƶ����ٶ�
	    int len;//�ߵĳ���
	    int x[SNAKESIZE];//��������ÿһ��С������x������
	    int y[SNAKESIZE];//��������ÿһ��С������y������
    }snake;
void gotoxy(int x, int y)     //������̨����Ƶ���x,y����
    {
	    COORD coord;
	    coord.X = x;
	    coord.Y = y;
	    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
void creatfood(int *score)
{
	//��һ��ʳ��Ĵ�����drawmap֮��//
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
		        printf("�I");
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
	//72��Ӧ�ϣ�80��Ӧ�£�75��Ӧ����77��Ӧ�� 
	int pre_key ;
	pre_key= key;//��¼ǰһ�������ķ���
	if (_kbhit())//����û������˼����е�ĳ����
	{
		fflush(stdin);//��ջ��������ַ�
		//getch()��ȡ�������ʱ�򣬻᷵�����Σ���һ�ε��÷���0����224���ڶ��ε��÷��صĲ���ʵ��ֵ
		key = _getch();//��һ�ε��÷��صĲ���ʵ��ֵ
		if(key==0||key==224) key = _getch();//�ڶ��ε��÷���ʵ��ֵ
	}
    if(key!=72&&key!=80&&key!=75&&key!=77){//��ֹ��Ұ������������Ϸ�쳣 
    	key=pre_key;
	}
	//�����ǰ�ƶ������ǰһ�η����෴�Ļ����ѵ�ǰ�ƶ��ķ����Ϊǰһ�εķ���
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
	//if(snake.speed>=230) snake.speed=230;
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
	//*t=((*t)++)%15+1;//�任������ɫ��ͬʱ��ֹ������ɫ�ͱ�����ɫ��ͬ 
	gotoxy(snake.x[0], snake.y[0]);//��ӡ����ͷ
	printf("��"); 
	gotoxy(MAPWIDTH - 2, 0);
	changeFlag = 0;//����Ŀǰû�гԵ�ʳ�changFlagֵΪ0
	return;
 }     
bool die()//����ֵΪfalse��Ϸ���� 
    {	
	    int i;
    	if (snake.y[0] == 0 || snake.y[0] == MAPHEIGHT)//��ͷ�������±߽磬��Ϸ����
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
	    for ( i = 1; i < snake.len; i++)//��ͷҧ��β����Ϸ���� 
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
	    printf("������Ϸ�÷�Ϊ��%d\n", *score);
	    gotoxy(MAPWIDTH/2,(MAPHEIGHT-1)/2+4);
	    printf("����������¿�ʼ��Ϸ����ESC������Ϸ��");
	    char a;
	    a=getch();
	    if(a!=0x1b)
		{
		system("cls");
		main();
		}
	} 
void drawmap()//�����ͼ���� 
    {
    	//��ͼһ���б߿� ��ͼ��Ҳ���б߿򵫻���١� 
        int i;
	    if(hard==0||hard==1)
	    {
	        for(i=0;i<=MAPWIDTH;i=i+2)
	        {
		        gotoxy(i, 0);
		        printf("��");
		        gotoxy(i, MAPHEIGHT);
		        printf("��");
	        }
	        for(i=1;i<MAPHEIGHT;i++)
	        {
	            gotoxy(0, i);
	            printf("��");
	            gotoxy(MAPWIDTH, i);
	            printf("��");
	        }
	    }
        else if(hard==2)//��ͼ���ɴ�ǽ��ͼ 
        {
            for(i=0;i<=MAPWIDTH;i=i+2)
	        {
		        gotoxy(i, 0);
		        printf("��");
		        gotoxy(i, MAPHEIGHT);
		        printf("��");
	        }
	    }  
	while (1)//������ɳ���ʳ��
	{
		srand((unsigned int)time(NULL));
		food.x = rand() % (MAPWIDTH - 4) + 2;
		food.y = rand() % (MAPHEIGHT - 2) + 1;
		if (food.x % 2 == 0)
			break;
	}
	gotoxy(food.x, food.y);//������Ƶ�ʳ������괦��ӡʳ��
	printf("�I");
	snake.len = 3;//��ʼ���ߵĳ������ٶ� 
	snake.speed = 200;
	//����Ļ�м�������ͷ
	snake.x[0] = MAPWIDTH / 2 + 1;
	snake.y[0] = MAPHEIGHT / 2;
	gotoxy(snake.x[0], snake.y[0]);//��ӡ��ͷ
	printf("��");
	for (i = 1; i < snake.len; i++)//���ɳ��Ե�����
	{//����Ĵ�ӡ�������겻�䣬������Ϊ��һ�����������ֵ+2
		snake.x[i] = snake.x[i - 1] + 2;
		snake.y[i] = snake.y[i - 1];
		gotoxy(snake.x[i], snake.y[i]);
		printf("��");
	}
	gotoxy(MAPWIDTH - 2, 0);
    }
int menu()
{
	char *option[]={"��ͨģʽ","����ģʽ","��ǽģʽ"};
	char key = 0,a=0;
	int i, select = 0,j=0,k=0,p=0;
	HANDLE ohandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X=58;
	coord.Y=14;
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(ConsoleHandle, coord);
	SetConsoleTextAttribute(ohandle,FOREGROUND_GREEN|FOREGROUND_BLUE);
	printf("��ӭ������Ϸ��̰���ߡ���");
	key=getch();
	if(key!=' ');
	system("cls");
	while(true){
		for(i=0;i<3;i++){         //��3��ѡ��
		    coord.X=58;
			coord.Y=14+i+1; 
			HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
         //���ù��λ��
         SetConsoleCursorPosition(ConsoleHandle, coord);
			if(i==select)//���ý������
				SetConsoleTextAttribute(ohandle,BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
			else if(i==select+1)//�ָ�����
				SetConsoleTextAttribute(ohandle,FOREGROUND_GREEN|FOREGROUND_BLUE );
			puts(option[i]);
		}
		SetConsoleTextAttribute(ohandle,FOREGROUND_GREEN|FOREGROUND_BLUE );//�ָ�����
		key=getch();
		if(key==0x1b)  //ESC ��
			return 0;
		if(key==0xd)  //Enter ��
			break;
		if(key<0){  //��ascii���2���ֽ�
			key=getch();
			switch(MapVirtualKey(key,1)){
			case VK_UP:
				select = (select+2)%3,k++;//�������ƣ���һ������ѡ�񣬹�3��ѡ��
				break;
			case VK_DOWN:
				select = (select+1)%3,p++;//�������ƣ���һ
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
	printf("��ѡ��: %s\n",option[select]);
	a=getch();
	if(a!=0x1b)
	{
	system("cls");
	coord.X=28;
	coord.Y=15; 
    SetConsoleCursorPosition(ConsoleHandle, coord);
	switch(j)
	{
		case 0:printf("��ͨģʽ���ߵ��ƶ��ٶȽ���");break;
		case 1:printf("����ģʽ���ߵ��ƶ��ٶȽϿ�");break;
		case 2:printf("��ǽģʽ���߿������⴩�����ҷ����ǽ�壬����ͷ��������ǽ�������ʱ����Ϸ����");
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
