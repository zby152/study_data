#include "stdio.h"
#include "stdlib.h"
#define LENGTH 15

void show()
{
    system("cls");
    int i, j;
    for (i = 0; i < LENGTH; i++)
    { 
        for (j = 0; j < LENGTH; j++)
        {
            printf("* ");
        }
        printf("\n");
    }
}
void main()
{
    while (1)
    {
        show();
    }
}
