#include<stdlib.h>
#include<stdio.h>
#include<math.h>
int main(void)
{
	double s,t,x;
	int n;
	printf("please input s:");
	scanf("%lf",&x);
	t=x;
	n=1;
	s=x;
	do{
		n=n+2;
		t=t*(-x*x)/((float)(n)-1)/(float)(n);
		s=s+t;
		#ifdef DEBUG
		printf("这是测试数据：n=%d,t=%f,s=%f\n",n,t,s);
		#endif
	}while(fabs(t)>=1e-6);
	printf("sin(%f)=%f\n",x,s);
	system("PAUSE");
	return 0;
}
