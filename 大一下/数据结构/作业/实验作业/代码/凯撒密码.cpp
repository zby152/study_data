#include<stdio.h>
#include<stdlib.h>
#define MAX 20
int main()
{
    int n=0;
    int i;
    char a[MAX],letter;
    printf("请输入偏移量（允许负数）\n");
    scanf("%d",&n);
    printf("偏移量为%d\n", n);
    printf("请输入想要转换的字符(允许大写字母、小写字母、数字、‘，’、‘。’\n");
    scanf(" %s", &a);
    printf("你输入的字符是:\n");
    printf("%s",a);
    int j = 0;
    while(a[j]!='\0')
    {
        letter = a[j];
        if(letter>='a'&&letter<='z'&&(letter+n)<='z')
            letter = letter + n;
        else if(letter>='a'&&letter<='z'&&(letter+n)>'z')
            letter = letter + n - 26;
        else if(letter>='A'&&letter<='Z'&&(letter+n)<='Z')
            letter = letter + n;
        else if(letter>='A'&&letter<='Z'&&(letter+n)>'Z')
            letter = letter + n - 26;
        else if(letter>='0'&&letter<='9'&&(letter+n)<'9')
            letter = letter + n;
        else if(letter>='0'&&letter<='9'&&(letter+n)>'9')
            letter = letter + n - 10;
        a[j] = letter;
        j++;
    }
    printf("\n偏移后的字符串为:\n");
    printf("%s", a);

    return 0;

}