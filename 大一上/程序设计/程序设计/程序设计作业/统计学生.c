#include<stdio.h>
#include<stdlib.h>
struct Student{
	long number;
	char name[16];
	float score[3],average;
};
int main()
{
	int n,i,q,p;
	long m;
	do{
	printf("请输入您要统计的学生数量：");
	scanf("%d",&n);}while(n<1);
	struct Student stu[n];
	for(i=0;i<n;i++){
	printf("\n请输入第%d个学生的姓名：",i+1);
	scanf("%s",stu[i].name);
	do{
	p=0;
	printf("请输入第%d个学生的学号：",i+1);
	scanf("%ld",&stu[i].number);
	if(i+1>1) {
	  for(q=0;q<i;q++){
	  	if(stu[q].number==stu[i].number){
		  printf("wrong!请重新输入：\n");
		  p=1;
		  }
	  }
	}
}while(p==1);
	printf("请输入第%d个学生的语文成绩：",i+1);
	scanf("%f",&stu[i].score[0]);
	printf("请输入第%d个学生的数学成绩：",i+1);
	scanf("%f",&stu[i].score[1]);
	printf("请输入第%d个学生的外语成绩：",i+1);
	scanf("%f",&stu[i].score[2]);
	stu[i].average=(stu[i].score[0]+stu[i].score[1]+stu[i].score[2])/3;
	}
	do{
    printf("\n请输入任意一个学号：");
	scanf("%ld",&m);
	for(i=0;i<n;i++){
		if(m==stu[i].number) {
		printf("姓名：%s\n学号：%ld\n语文成绩：%.2f\n数学成绩：%.2f\n外语成绩：%.2f\n平均成绩：%.2f",
		stu[i].name,stu[i].number,stu[i].score[0],stu[i].score[1],stu[i].score[2],stu[i].average);
        break;
         }
	}
	if(i==n) printf("wrong!请重新输入：\n"); 
}while(i==n);
	return 0;
 } 
