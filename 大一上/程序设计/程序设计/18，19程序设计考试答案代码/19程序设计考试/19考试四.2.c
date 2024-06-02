#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char data[100];
    int top;
    int bottom;
}stack;
    //** 创建  */
    stack * StackCreate(void){
    stack * p = (stack*)malloc(sizeof(stack));
    if(p){
        p->bottom = p->top = 0;
        return p;
    }
    else
        printf("Create stack p failed！\n");
    }
    //** 入栈  */
    void StackInput(stack * p, char ch){
        p->data[p->top] = ch;
        p->top++;
        //return p;

    }
    //** 出栈  */
    char StackOutput(stack* p){
    if(p->bottom != p->top){
        char ch = p->data[p->top - 1];
        p->top--;
        return ch;
    }
    else
        printf("The stack is empty!\n");

    }
    //** 释放指针p  */
    void StackFree(stack* p){
    free(p);
    //printf("Bye!\n");
    }

    //** 测试用的  */
    int main(void)
    {
    char temp1;
    int i = 0;
    char *str1 = "false";
    char * str2 = "ture";
    char s[100];
    gets(s);
    if (strlen(s) == 0)
    {
        puts(str2);
        return 1;
    }
    stack * p = StackCreate();
    if(strlen(s)%2 == 0){
        while(i < strlen(s)){
        while(s[i] == '(' || s[i] == '[' || s[i] == '{')
            {
              StackInput(p, s[i]);
              i++;
              printf("i = %d\n", i-1);
            }
        while(s[i] == ')'){
                temp1 = StackOutput(p);
                if(temp1 == '(')
                    i++;
                else {
                        puts(str1);
                        return 0;
                }

            }
        while(s[i] == '}'){
                temp1 = StackOutput(p);
                if(temp1 == '{')
                    i++;
                else {
                        puts(str1);
                        return 0;
                }
            }
        while(s[i] == ']'){
                temp1 = StackOutput(p);
                if(temp1 == '[')
                    i++;
                else {
                        puts(str1);
                        return 0;
                }
            }
            continue;
        }
        if(i == strlen(s) && 0 == p->top){
            puts(str2);
            return 1;
        }
        else {
            puts(str1);
            return 0;
        }
    }
    else {
    puts(str1);
    return 0;
    }
    StackFree(p);
    }



