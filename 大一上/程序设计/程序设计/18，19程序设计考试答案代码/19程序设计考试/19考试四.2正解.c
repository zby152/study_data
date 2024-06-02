#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
typedef struct{
	char *data;
	int V;
	int top;
}stack;

void init(stack *p,int V){
	p->V=V;
	p->data=(char*)malloc(V*sizeof(char));
	p->top=-1;
}

int isFull(stack*p){
	return p->top==(p->V-1);
}

int isEmpty(stack*p){
	return p->top==-1;
}

int push(stack*p,char ch){
	if(isFull(p)) return 0;
	else{
		p->top++;
		p->data[p->top]=ch;
		return 1;
	}
}

int pop(stack*p,char*ch){
	if(isEmpty(p)) return 0;
	else{
		*ch=p->data[p->top];
		p->top--;
		return 1;
	}
}

void destroy(stack *p){
	free(p->data);
}

int main()
{
	char Str[100];
	char str[100],ch;
	char str1[]="true",str2[]="false";
	gets(Str);
	stack*p;
	p=(stack*)malloc(sizeof(stack));
	int t=strlen(Str),i,j=0;
	for(i=0;i<t;i++){
		if(Str[i]!=' '){
			str[j]=Str[i];
			j++;
		}
	}
	init(p,strlen(str));
	i=0;
	if(strlen(str)%2!=0){
		puts(str2);
		return 1;
	}
	else{
		while(i<strlen(str)){
			while(str[i]=='('||str[i]=='['||str[i]=='{'){
				push(p,str[i]);
				i++;
			}
			while(str[i]==')'){
				pop(p,&ch);
				if(ch=='('){
					i++;
				}
				else{
					puts(str2);
					return 1;
				}
			}
			
			while(str[i]=='}'){
				pop(p,&ch);
				if(ch=='{'){
					i++;
				}
				else{
					puts(str2);
					return 1;
				}
			}
			
			while(str[i]==']'){
				pop(p,&ch);
				if(ch=='['){
					i++;
				}
				else{
					puts(str2);
					return 1;
				}
			}
		}
		if(i==strlen(str)&&p->top==-1){
			puts(str1);
			return 0;
		}
		else{
			puts(str2);
			return 0;
		}
	}
	destroy(p);
	return 0;
}
