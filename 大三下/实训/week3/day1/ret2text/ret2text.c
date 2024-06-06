#include <stdio.h>
#include <stdlib.h>

void shell()
{
    system("/bin/sh");
}

void input()
{

    char buf[100];

    printf("hello world\n");
    read(0, buf, 200);
}

int main()
{
    input();
    return 0;
}
