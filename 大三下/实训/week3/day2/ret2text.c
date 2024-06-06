#include <stdio.h>
#include <stdlib.h>

void shell()
{
    system("/bin/sh");
}

int main()
{
    char buf[100];
    read(0, buf, 200);
    return 0;
};
