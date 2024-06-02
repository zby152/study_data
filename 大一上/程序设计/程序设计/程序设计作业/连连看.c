#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h> 
struct dot{
	int u;
	int v;
};
void random_number(int LLK[][12],int row,int line)
{
	int a, num;
	int i, j;
	int game[10];
	for(i = 0; i < 10; i++) game[i] = 0;
	srand((unsigned)time(NULL));
	for(i = 1; i < row - 1; i++)
		for(j = 1; j < line - 1; j++){
			a = rand();
			num = a % 10;
			if(game[num] < 8){
				LLK[i][j] = num;
				game[num]++;
			}
			else {
				while(game[num] >= 8) {
					num++;
					num = num % 10;
				}
				LLK[i][j] = num;
				game[num]++;
			}
		}
}
void put_pic(int LLK[][12], int row, int line)
{
	int Status, i, j;
	printf("   ");
	for(i = 1; i < line - 1; i++) printf(" %d ", i);
	printf("\n\n");
	for(i = 1; i < row - 1; i++){
		printf(" %d ", i);
		for(j = 1; j < line - 1; j++){
			Status = LLK[i][j];
			switch(Status){
			case -1: printf("   "); break;
            case 0: printf(" A "); break;
			case 1: printf(" M "); break;
			case 2: printf(" T "); break;
			case 3: printf(" O "); break;
			case 4: printf(" E "); break;
			case 5: printf(" S "); break;
			case 6: printf(" G "); break;
			case 7: printf(" H "); break;
			case 8: printf(" K "); break;
			case 9: printf(" J "); break;
			default: printf("wrong\n"); break;
			}
		}
		printf("\n\n");
	}
}
bool judge_one_line(int LLK[][12], int u1, int v1, int u2, int v2)
{
	int i, min, max;
	if(u1 == u2){
			if(v1 >= v2){
				max = v1;
				min = v2;
			}
			else{
				max = v2;
				min = v1;
			}
			for(i = 1; i + min < max; i++){
				if(LLK[u1][i+min] != -1) break;
			}
			if(i + min == max) return true;
			else return false;
		}
	else if(v1 == v2){
		if(u1 >= u2){
			max = u1;
			min = u2;
		}
		else{
			max = u2;
			min = u1;
		}
		for(i = 1; i + min < max; i++){
			if(LLK[u1][i+min] != -1) break;
		}
		if(i + min == max) return true;
		else return false;
	}
	else return false;
}
bool judge_two_line(int LLK[][12], int u1, int v1, int u2, int v2)
{
	bool flag1 = false, flag2 = false;
	if(LLK[u1][v2] == -1){
		flag1 = judge_one_line(LLK, u1, v1, u1, v2);
		flag2 = judge_one_line(LLK, u1, v2, u2, v2);
	}
	else if(LLK[u2][v1] == -1){
		flag1 = judge_one_line(LLK, u1, v1, u2, v1);
		flag2 = judge_one_line(LLK, u2, v1, u2, v2);
	}
	if(flag1 && flag2) return true;
	else return false;
}
int judge_three_line1(int LLK[][12], dot LLK1[20], int u, int v)
{
	int i, num = 0;
	for(i = v - 1; i >= 0; i--){
		if(LLK[u][i] != -1) break;
		if(LLK[u][i] == -1){
			LLK1[num].u = u;
			LLK1[num].v = i;
			num++;
		}
	}
	for(i = v + 1; i < 12; i++){
		if(LLK[u][i] != -1) break;
		if(LLK[u][i] == -1){
			LLK1[num].u = u;
			LLK1[num].v = i;
			num++;
		}
	}
	for(i = u - 1; i >= 0; i--){
		if(LLK[i][v] != -1) break;
		if(LLK[i][v] == -1){
			LLK1[num].u = i;
			LLK1[num].v = v;
			num++;
		}
	}
	for(i = u + 1; i < 10; i++){
		if(LLK[i][v] != -1) break;
		if(LLK[i][v] == -1){
			LLK1[num].u = i;
			LLK1[num].v = v;
			num++;
		}
	}
	return num;
}
bool judge_three_line2(int LLK[][12], int u1, int v1, int u2, int v2)
{
	dot LLK1[20], LLK2[20];
	int n, m, i, j;
	bool flag;
	n = judge_three_line1(LLK, LLK1, u1, v1);
	m = judge_three_line1(LLK, LLK2, u2, v2);
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++){
			flag = judge_one_line(LLK, LLK1[i].u, LLK1[i].v, LLK2[j].u, LLK2[j].v);
			if(flag) break;
		}
		if(flag) break;
	}
	if(i == n && j == m) return false;
	else return true;
}
bool judge(int LLK[][12],int u1, int v1, int u2, int v2)
{
	bool flag1, flag2, flag3;
	if(LLK[u1][v1] == LLK[u2][v2]){
		flag1 = judge_one_line(LLK, u1, v1, u2, v2);
		if(flag1) return true;
		flag2 = judge_two_line(LLK, u1, v1, u2, v2);
		if(flag2) return true;
		flag3 = judge_three_line2(LLK, u1, v1, u2, v2);
		if(flag3) return true;
		else return false;
	}
	else {
		return false;
	}
}
void mode(int LLK[][12], int time)
{
	printf("\n\n******����%d����******\n", time);
	int u1, v1, u2, v2;
	int score = 0;
	bool flag;
	clock_t start, end;
	int duration;
	start = clock();
	while(1){
		put_pic(LLK, 10,12);
		printf("�������һ������С������꣺");
		scanf("%d %d", &u1, &v1);
		printf("������ڶ�������С������꣺");
		scanf("%d %d", &u2, &v2);
		flag = judge(LLK, u1, v1, u2, v2);
		if(flag) {
			score = score + 10;
			printf("\n�����ɹ�!   Ŀǰ�÷�:%d\n", score);
			if(score == 400){
				printf("\n*****��ϲ������������ĸ!*****\n");
				break;
			}
			LLK[u1][v1] = -1;
			LLK[u2][v2] = -1;
		}
		else printf("\n����ʧ��!   Ŀǰ�÷�:%d\n", score);
		end = clock();
	    duration = (int)(end - start)/CLK_TCK;
		if(duration > time * 60) {
			printf("*********��ʣ��ʱ�䣬��Ϸ����*********");
			break;
		}
		else{
			printf("Ŀǰ��ʱ��%02d:%02d", duration / 60, duration % 60);
			printf("   ʣ��ʱ�䣺%02d:%02d\n", (time * 60 - duration) / 60, (time * 60 - duration) % 60);
			printf("\n");
		}
	}
}
int main()
{
	int LLK[10][12];
	int i,j,sel,op;
	int u1, v1, u2, v2;
	int score = 0, time;
	bool flag;
	clock_t start, end;
	int duration;
	for(i = 0; i < 12; i++) LLK[0][i] = -1;
	for(i = 0; i < 12; i++) LLK[9][i] = -1;
	for(i = 0; i < 10; i++) LLK[i][0] = -1;
	for(i = 0; i < 10; i++) LLK[i][11] = -1;
	printf("��ӭʹ��������С��Ϸ����\n");
	printf("**************************\n");
	random_number(LLK,10,12);
	printf("�˵���1:����Ϸ 2:��Ϸ���� 0:�˳� :");
	scanf("%d", &sel);
	switch(sel){
		case 1:{
			printf("��ѡ����Ϸģʽ: 1������ģʽ(5min) 2���ؿ�ģʽ 3������ģʽ(����ʱ)");
			scanf("%d", &op);
			switch(op){
			case 1:{
				mode(LLK, 5);
				break;
				   }
			case 2:{
				printf("�����ģʽ�£������Ϊ�Լ��޶�ʱ�䣬��������Ҫ�õ�ʱ�䣺");
				scanf("%d", &time);
				mode(LLK, time);
				break;
				   }
			case 3:{
				start = clock();
				while(1){
					put_pic(LLK, 10,12);
					printf("�������һ������С������꣺");
					scanf("%d %d", &u1, &v1);
					printf("������ڶ�������С������꣺");
					scanf("%d %d", &u2, &v2);
					flag = judge(LLK, u1, v1, u2, v2);
					if(flag) {
						score = score + 10;
						printf("\n�����ɹ�!   Ŀǰ�÷�:%d\n", score);
						if(score == 400){
							printf("\n*****��ϲ������������ĸ!*****\n");
							break;
						}
						LLK[u1][v1] = -1;
					    LLK[u2][v2] = -1;
					}
					else printf("\n����ʧ��!   Ŀǰ�÷�:%d\n", score);
					printf("\n");
				}
				end = clock();
				duration = (int)(end - start)/CLK_TCK;
				printf("����ʱ��Ϊ%02d:%02d", duration/60, duration % 60);
				break;
				   }
			default:printf("�������!");
		}
			break;
		case 2:{
			printf("\n\n**************��Ϸ����*************");
			printf("\n1.ֻ��������ͬ����ĸ���������Ŀ���");
			printf("\n2.ÿ��ֻ������������ĸ������ʱ��Ҫ����������ĸ������");
			printf("\n3.������ĸ����ʱ��������·��������·�������ܳ��������յ�");
			printf("\n4.����·�������ĵ�Ԫ������������ĸ�����Ѿ�����");
			printf("\nע��:�С��������ÿո��������������밴�س���");
			   }
			break;
		case 0: {
			break;
				}
		default: printf("�������!");
			   }
	}
	printf("\n\n**********��лʹ��������С����!*********\n\n");
	return 1;
}

