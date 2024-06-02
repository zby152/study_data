#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
	char ch;
	struct node*next;
}node;

void InputString(char str1[],char str2[])
{
	printf("Input two strings\n");
	gets(str1);
	gets(str2);
}

node*FindSubStr(char str1[],char str2[])
{
	node*tail,*new,*head;
	head=tail=(node*)malloc(sizeof(node));
	head=NULL;
	int i,j,t,q,p;
	for(i=0;i<strlen(str1);i++){
		for(j=0;j<strlen(str2);j++){
			q=0;
			t=0;
			p=0;
			while((str1[i+q]!=' '&&str1[i+q]!='\0')&&(str2[j+q]!=' '&&str2[j+q]!='\0'))
			{
				if(str1[i+q]==str2[j+q])
				{
				t++;
				q++; 
			}
			else break;
			}
			if(t>2){
				while(p<t){
				new=(node*)malloc(sizeof(node));
				new->ch=str1[i+p];
				new->next=NULL;
				if(head==NULL) head=new;
				else tail->next=new;
				tail=new;
				p++;	
				}
				new=(node*)malloc(sizeof(node));
				new->ch=',';
				new->next=NULL;
				tail->next=new;
				tail=new;
				for(q=0;q<t;q++){
					str1[i+q]=' ';
					str2[j+q]=' ';
				}
			}
		}
	}
	return head;
}

PrintSubStr(node*head)
{
	while(head!=NULL){
		printf("%c",head->ch);
		head=head->next;
		if(head->next==NULL) break;
	}
}

int main()
{
	char str1[81],str2[81];
	InputString(str1,str2);
	node*t;
	t=FindSubStr(str1,str2);
	PrintSubStr(t);
	return 0;
}
