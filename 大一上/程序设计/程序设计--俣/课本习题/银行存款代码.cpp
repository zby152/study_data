#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	float n1=0.0204,n1_=0.0368,n2=0.0197,n2_=0.0312,n3=0.0206,n3_=0.0354,n4=0.0175,n4_=0.0275;
	int a,n,n_,c;
	float money,x1,x2;
	printf("请输入银行编号与存款金额\n");
	scanf("%d,%f",&a,&money);
	switch(a)
	{
	case 1:n=n1,n_=n1_; break;
	case 2:n=n2,n_=n2_; break;
	case 3:n=n3,n_=n3_; break;
	case 4:n=n4,n_=n4_;
    }   
	x1=money*(1+n)*(1+n)*(1+n);
	x2=money*(1+n_);
	c=(x1>x2)?1:0;
	if(c==1)
	printf("存一年三次多\n");
	else
	printf("存一次三年多\n");
	system("PAUSE");
	return 0;
}

