#include<stdio.h>
#include<stdlib.h>
union uip{
	unsigned int x;
	unsigned char IP[4];
};
int main()
{
	int a=12;
	union uip myIP;
	myIP.x== 37778122;
	printf("%s\n",myIP.IP);
	printf("%d\n%d.%d.%d.%d\n",a, myIP.IP[0], myIP.IP[1], myIP.IP[2], myIP.IP[3]);
	return 1;
}
