#include<stdio.h>

enum DAY
{
  SUN,MON,TUE,WNE,THU,FRI,SAT
};

int main()
{
  unsigned int today;
  printf("please input the day:\n");
  scanf("%d",&today);
  enum DAY day=today%7;
  switch(day)
  {
    case MON:
    case TUE:
    case WNE:
    case THU:
    case FRI:
             printf("The day is a work day!\n");
             break;
    case SAT:
    case SUN:
             printf("The day is a free day!\n");
             break;
  };
  return 0;
}
