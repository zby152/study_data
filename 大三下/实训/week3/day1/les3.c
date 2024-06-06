#include <stdio.h>

void win()
{
    printf("you win\n");
}

int main()
{
    char a[100];
    gets(a);
    printf("you lose\n");
    return 0;
};
