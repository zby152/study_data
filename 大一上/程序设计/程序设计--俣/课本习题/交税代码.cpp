#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	float result=0,money=0;
	float n1=36000*3/100,n2=(144000-36000)/10,n3=(300000-144000)/5,n4=(420000-3000000)/4,n5=(660000-420000)*30/100,n6=(960000-660000)*35/100;
	printf("请输入工资数\n");
	scanf("%f",&money);
	if(money<=36000)
	     result=money*3/100;
    else if(money<=144000)
        result=n1+(money-36000)/10;
    else if(money<=300000)
        result=n1+n2+(money-144000)/5;
    else if(money<=420000)
        result=n1+n2+n3+(money-300000)/4;
    else if(money<=660000)
        result=n1+n2+n3+n4+(money-420000)*30/100;
    else if(money<=960000)
        result=n1+n2+n3+n4+n5+(money-660000)*35/100;
    else if(money>960000)
        result=n1+n2+n3+n4+n5+n6+(money-960000)*45/100;
printf("要交%f的税\n",result);
system("PAUSE");
return 0;
}
