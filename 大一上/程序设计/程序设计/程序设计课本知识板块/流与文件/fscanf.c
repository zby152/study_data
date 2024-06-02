#include<stdio.h>
typedef FILE *stream;
int main()
{
	stream my_in;
	float x;
	my_in=fopen("hhh.txt","r");
	if(my_in==NULL){
		printf("File open error!\n");
		exit(0);
	}
	fscanf(my_in,"%g",&x);
	printf("%f",x);
}
