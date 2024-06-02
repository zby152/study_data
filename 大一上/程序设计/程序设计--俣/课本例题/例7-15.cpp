#include<stdio.h>
#include<stdlib.h>
#define NTOWNS 5
void inputTimeTable(int time[][NTOWNS],char towns[][10],int ntown);
int selectCity(char towns[][10],int ntown);
int main()
{
	char towns[NTOWNS][10]={"武汉","岳阳","长沙","南昌","九江"};
	int timeTable[NTOWNS][NTOWNS];
	int row,col;
	int city1,city2,city3;
	int time;
	printf("\n自驾出游，计算累计驾驶时间\n\n");
	printf("输入旅行时间表:\n");
	inputTimeTable(timeTable,towns,NTOWNS);
	city1=selectCity(towns,NTOWNS);
	city2=selectCity(towns,NTOWNS);
	city3=selectCity(towns,NTOWNS);
	time=timeTable[city1][city2]+timeTable[city2][city3]+timeTable[city3][city1];
	printf("\n从%s、%s到%s之间的旅行时间共计：%d\n",towns[city1],towns[city2],towns[city3],time);
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
			printf("请输入%s到%s的旅行时间:",towns[row],towns[col]);
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
		printf("请在城市0~4中，选择出游的一个城市编号:");
		scanf("%d",&select);
		if(select<0||select>=ntown)
		printf("Error:城市编号必须在0~%d范围内\n",ntown-1);
	}while(select<0||select>=ntown);
	printf("\n你选择的出游城市是%s\n\n",towns[select]);
	return select;
}
