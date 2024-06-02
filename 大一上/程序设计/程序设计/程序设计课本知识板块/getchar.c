#include <stdio.h>
#define SPACE ' '               // SPACE表示一个空格字符

int main()
{
    char ch;

    ch = getchar();             // 读取一个字符
    while(ch != '\n')           // 当读取到的下一个字符不是换行符时（即一行未结束时）
    {
        if(ch == SPACE)         // 留下空格
            putchar(ch);
        else
            putchar(ch + 1);    // 改变其他字符
        ch = getchar();         // 获取下一个字符
    }
    putchar(ch);                // 循环结束，读取的最后一个字符是'\n',打印换行符
    
    return 0;
}
