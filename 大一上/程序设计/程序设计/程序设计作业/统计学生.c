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
	printf("��������Ҫͳ�Ƶ�ѧ��������");
	scanf("%d",&n);}while(n<1);
	struct Student stu[n];
	for(i=0;i<n;i++){
	printf("\n�������%d��ѧ����������",i+1);
	scanf("%s",stu[i].name);
	do{
	p=0;
	printf("�������%d��ѧ����ѧ�ţ�",i+1);
	scanf("%ld",&stu[i].number);
	if(i+1>1) {
	  for(q=0;q<i;q++){
	  	if(stu[q].number==stu[i].number){
		  printf("wrong!���������룺\n");
		  p=1;
		  }
	  }
	}
}while(p==1);
	printf("�������%d��ѧ�������ĳɼ���",i+1);
	scanf("%f",&stu[i].score[0]);
	printf("�������%d��ѧ������ѧ�ɼ���",i+1);
	scanf("%f",&stu[i].score[1]);
	printf("�������%d��ѧ��������ɼ���",i+1);
	scanf("%f",&stu[i].score[2]);
	stu[i].average=(stu[i].score[0]+stu[i].score[1]+stu[i].score[2])/3;
	}
	do{
    printf("\n����������һ��ѧ�ţ�");
	scanf("%ld",&m);
	for(i=0;i<n;i++){
		if(m==stu[i].number) {
		printf("������%s\nѧ�ţ�%ld\n���ĳɼ���%.2f\n��ѧ�ɼ���%.2f\n����ɼ���%.2f\nƽ���ɼ���%.2f",
		stu[i].name,stu[i].number,stu[i].score[0],stu[i].score[1],stu[i].score[2],stu[i].average);
        break;
         }
	}
	if(i==n) printf("wrong!���������룺\n"); 
}while(i==n);
	return 0;
 } 
