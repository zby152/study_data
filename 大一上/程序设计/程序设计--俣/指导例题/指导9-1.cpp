#include<stdio.h>
#include<stdlib.h>
int main()
{
	struct stu{
		int num;
		char *name;
		char sex;
		float score;
	}boy1,boy2;
	printf("Please input ID and name\n");
	scanf("%d %s",&boy1.num,&boy1.name);
	printf("input sex and score\n");
	scanf(" %c  %f",&boy1.sex,&boy1.score);
	boy2=boy1;
	printf("Number=%d\nName=%d\n",boy2.num,boy2.name);
	printf("Sex=%c\nScore=%f\n",boy2.sex,boy2.score);
	system("pause");
	return 0;
}
