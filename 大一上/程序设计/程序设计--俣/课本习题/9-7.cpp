#include<stdio.h>
#include<stdlib.h>
int main()
{   
     typedef struct student{
		char name;
		long int id;
		int score[3];
	}STU;
    STU stu[10];
	int i,num;
	for(i=0;i<10;i++)
	{
	printf("�������%dλѧ������Ϣ(���� ѧ�� ���ųɼ�)\n",i+1);
	scanf("%s %ld %d %d %d",&stu[i].name,&stu[i].id,&stu[i].score[0],&stu[i].score[1],&stu[i].score[2]);
    }
	int average[10];
	for(i=0;i<10;i++)
	{
		average[i]=(stu[i].score[0]+stu[i].score[1]+stu[i].score[2])/3;
		if(average[i]>85)
		num++;
	}
	printf("��%d��",num);
	system("PAUSE");
	return 0;
}
