#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
//将不确定位数的正整数三分位节后输出 
char *separate(long int);
char *exchange(long int);
int main(void)
{
	char *p;
	long int num;
	printf("请输入整数\n");
	scanf("%ld",&num);
	p=separate(num);
    printf("结果是%s\n",p);
    system("PAUSE");
    return 0;
}
char *separate(long int num)
{
    char *p1,*p2=exchange(num),*p3,*pt;
    p1=p2;
    int count=1;
    while(*(p2++)!='\0');
    p3=p2-1;
    p2=p2-2;
    while(p2>p1)
    {
    	if(count==3)
    	{   	
		    pt=p3++;
    		while(pt>=p2)
    		{
    		    *(pt+1)=*pt;
    		    pt--;
    	    }
    	    *p2=',';
    	    count=1;
    	    p2--;
		}
		p2--;
		count++;
	}
	return p1;
}
char *exchange(long int num)
{
	char *p,*p1,*p2;
	char temp;
	p=p1=p2=(char*)malloc(30*sizeof(char));
	while(num)
	{
		*p2=num%10+'0';
		p2++;
		num=num/10;
	}
	*p2='\0';
	p2--;
	while(p1<p2)
	{
		temp=*p2;
		*p2=*p1;
		*p1=temp;
		p1++;
		p2--;
	}
	return p;
}


