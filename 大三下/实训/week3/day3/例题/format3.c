#include<stdio.h>
int main()
{
    char buf[0x100];
    read(0,buf,0x100);
    printf(buf);		/*此处为格式化字符串漏洞点*/
    return 0;
}
