#include<stdlib.h>
#include<stdio.h>
#define SIZE 5
struct stu{
	int num;
	char name[15];
	char sex;
	float score;
};
struct stu* readstud(struct stu boy[SIZE])
{

	int i,j;
	for(i=0;i<SIZE;i++)
	{
	    printf("请输入第%d名学生学号，性别，得分,姓名",i+1);
	    scanf("%d",&boy[i].num);
		scanf(" %c",&boy[i].sex);
		scanf(" %f",&boy[i].score);
		gets(boy[i].name);
    }
    return boy;
}
int average(struct stu boy[SIZE])
{
	int sum=0,k,a;
	for(k=0;k<5;k++)
	{
		sum=sum+boy[k].score;
	}
	a=sum/5;
	return a;
}
int count(struct stu boy[SIZE])
{
	int l;
	int n=0;
	for(l=0;l<SIZE;l++)
	{
		if(boy[l].score<60)
		n++;
	}
	return n;
}
int main()
{
	int ave;
	int num=0;
	struct stu boys[SIZE];
	readstud(boys);
    ave=average(boys);
    num=count(boys);
	printf("average=%d\n",ave);
	printf("不及格人数是%d\n",num);
	system("pause");
	return 0;
}

