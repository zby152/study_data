#include<stdio.h>
typedef FILE *stream;
int main()
{
	stream my_out;
	char fname[20]="Wuhan University";
	int t=11;
	my_out=fopen("hhh.txt","w");
	if(my_out==NULL)
	{
		fputs("File can not open!\n",stderr);
		exit(0);
	}
	fprintf(my_out,"name:%s time:%d",fname,t);
	fclose(my_out);
}
