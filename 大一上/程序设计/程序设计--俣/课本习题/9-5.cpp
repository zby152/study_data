#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	struct {
		int year;
		int month;
		int day;
	}data;
	int monthday[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	int days,years,i;
	printf("请输入年份与天数\n");
	scanf("%d %d",&years,&days);
	int flag;
	if(years%4==0&&years%100!=0||years%400!=0)
	flag=1;
	monthday[1]+=flag;
	data.year=years;
	for(i=0;i<11;i++)
	{
		if(days>monthday[i])
		    days=days-monthday[i];
		else
		break;
	}
	if(days>monthday[11])
	printf("天数超出");
	data.month=i+1;
	data.day=days;
	printf("日期是%d年，%d月,%d日\n",data.year,data.month,data.day);
	system("PAUSE");
	return 0;
}
