#include <stdio.h>

void vulFunc()
{
    char buf[128];
    printf("%p\n",buf);
    read(0, buf, 256);
}
int main()
{
    vulFunc();
    puts("hello world");
    return 0;
};
