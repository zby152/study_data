#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	char c1,c2;
	int d1,d2;
	float f1,f2;
	double x1,x2;
	long int g1,g2;
	unsigned int u1,u2;
	
	c1='b';    c2='B';
	d1=-1;      d2=32767;
	f1=1.23;     f2=3.45;
	x1=5.67;      x2=6.78;
	g1=-32767;    g2=1024;
	u1=32768;      u2=65535;
	
	printf("c1:%c\t%d\nc2:%c\t%d\n",c1,c1,c2,c2);
	printf("d1:%06d\t%-6d\nd2:%06i\t%-6i\n",d1,d1,d2,d2);
	printf("f1:%ft%10.3f\nf2:%.4ec\t%.4g\n",f1,f1,f2,f2);
	printf("x1:%E\t%10.3E\nx2:%.4Gc\t%.4G\n",x1,x1,x2,x2);
	printf("g1:%lo\t%ld\ng2:%lx\t%ld\n",g1,g1,g2,g2);
	printf("u1:%u\t%x\nu2:%uc\t%x\n",f1,f1,f2,f2);
	system("PAUSE");
	return 0;
}
