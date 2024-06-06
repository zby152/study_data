#include <stdio.h>
int func_B(int a, int b)
{
    puts("This is func_B");
    return a + b;
}

int func_A(int a, int b)
{
    puts("This is func_A");
    func_B(a, b);
}
int main()
{
    int sum = func_A(3, 4);
    return 0;
};
