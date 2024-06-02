#include <stdio.h>
#include <windows.h>
int color(int num)
{
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),num);
 return 0;
}
int main()
{
 printf("WELCOME\n");
 int i;
 for(i=0;i<16;i++)
 {
  color(i);
  printf("¡ö");
 }
 return 0;
} 
