#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void order(char* str, int n); 
 int main()
 {
 	int i;
        const char *str[] = { "a", "abc", "ab", "abcde", "abcd" };
        order(str,5);
        for (i = 0; i < 5; i++)
        {
            printf("%s\n", str[i]);
        }
    system("PAUSE");
    return 0;
}

 void order(char* str[], int n)
 {
 	int i,j;
     for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (strlen(str[i]) < strlen(str[j]))
            {
                  char * p = str[j];
                str[j] = str[i];
                str[i] = p;
            }
        }
    }
 }
