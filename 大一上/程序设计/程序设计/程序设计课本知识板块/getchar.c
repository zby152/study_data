#include <stdio.h>
#define SPACE ' '               // SPACE��ʾһ���ո��ַ�

int main()
{
    char ch;

    ch = getchar();             // ��ȡһ���ַ�
    while(ch != '\n')           // ����ȡ������һ���ַ����ǻ��з�ʱ����һ��δ����ʱ��
    {
        if(ch == SPACE)         // ���¿ո�
            putchar(ch);
        else
            putchar(ch + 1);    // �ı������ַ�
        ch = getchar();         // ��ȡ��һ���ַ�
    }
    putchar(ch);                // ѭ����������ȡ�����һ���ַ���'\n',��ӡ���з�
    
    return 0;
}
