#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
	char*str;
	int capacity;
	int top;
}strack;

void init(strack*p,int m){
	p->capacity=m;
	p->top=-1;
	p->str=(char*)malloc(m*sizeof(char));
}

int isFull(strack*p){
	return (p->top)==(p->capacity-1);
}

int isEmpty(strack*p){
	return p->top==-1;
}

int push(strack*p,char ch){
	if(isFull(p)==1) return 1;
	else{
		p->top++;
		p->str[p->top]=ch;
        return 0;
	} 
}

int pop(strack*p,char*ch){
	if(isEmpty(p)==1) return 1;
	else{
		*ch=p->str[p->top];
		p->top--;
		return 0;
	}
}

int main()
{
	char Str[100],str[100],ch;
	int t,i,j=0;
	strack*p;
	p=(strack*)malloc(sizeof(strack));
	gets(Str);
	t=strlen(Str);
	for(i=0;i<t;i++){
		if(Str[i]!=' '){
			str[j]=Str[i];
			j++;
		}
	}
	init(p,strlen(str));
	if(strlen(str)%2!=0){
		printf("\n0");
		return 1;
	}
	else{
	i=0;
	while(i<strlen(str)){
		while(str[i]=='('||str[i]=='['||str[i]=='{'){
			push(p,str[i]);
			i++;
		}
		while(str[i]==')'){
			pop(p,&ch);
			if(ch=='(') i++;
			else{
				printf("\n0");
				return 1;
			}
		}
		while(str[i]=='}'){
			pop(p,&ch);
			if(ch=='{') i++;
			else{
				printf("\n0");
				return 1;
			}
		}
		while(str[i]==']'){
			pop(p,&ch);
			if(ch=='[') i++;
			else{
				printf("\n0");
				return 1;
			}
		}
	}
	if(p->top==-1&&i==p->capacity){
		printf("\n1");
		return 1;
	}
	else{
		printf("\n0");
		return 1;
	}
}
 } 
