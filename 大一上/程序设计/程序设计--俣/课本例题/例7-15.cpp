#include<stdio.h>
#include<stdlib.h>
#define NTOWNS 5
void inputTimeTable(int time[][NTOWNS],char towns[][10],int ntown);
int selectCity(char towns[][10],int ntown);
int main()
{
	char towns[NTOWNS][10]={"�人","����","��ɳ","�ϲ�","�Ž�"};
	int timeTable[NTOWNS][NTOWNS];
	int row,col;
	int city1,city2,city3;
	int time;
	printf("\n�Լݳ��Σ������ۼƼ�ʻʱ��\n\n");
	printf("��������ʱ���:\n");
	inputTimeTable(timeTable,towns,NTOWNS);
	city1=selectCity(towns,NTOWNS);
	city2=selectCity(towns,NTOWNS);
	city3=selectCity(towns,NTOWNS);
	time=timeTable[city1][city2]+timeTable[city2][city3]+timeTable[city3][city1];
	printf("\n��%s��%s��%s֮�������ʱ�乲�ƣ�%d\n",towns[city1],towns[city2],towns[city3],time);
	system("PAUSE");
	return 0;
}
void inputTimeTable(int time[][NTOWNS],char towns[][10],int ntown)
{
	int row,col;
	for(row=0;row<ntown;row++)
	{
		time[row][row]=0;
		for(col=row+1;col<ntown;col++)
		{
			printf("������%s��%s������ʱ��:",towns[row],towns[col]);
			scanf("%d",&time[row][col]);
			time[col][row]=time[row][col];
		}
	}
	printf("\n");
}
int selectCity(char towns[][10],int ntown)
{
	int select,row;
	for(row=0;row<ntown;row++)
	printf("%d:%s\t",row,towns[row]);
	printf("\n");
	do{
		printf("���ڳ���0~4�У�ѡ����ε�һ�����б��:");
		scanf("%d",&select);
		if(select<0||select>=ntown)
		printf("Error:���б�ű�����0~%d��Χ��\n",ntown-1);
	}while(select<0||select>=ntown);
	printf("\n��ѡ��ĳ��γ�����%s\n\n",towns[select]);
	return select;
}
