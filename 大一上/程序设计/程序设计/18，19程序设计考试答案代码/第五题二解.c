#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
	char ch;
	struct node* next;
};

void InputString(char *str1,char *str2)
{
	printf("ÇëÊäÈëÁ½Ìõ×Ö·û´®£º\n");
	gets(str1);
	gets(str2);
}
struct node* FindSubStr(char *str1,char *str2)
{
	int len1=strlen(str1),len2=strlen(str2);
	int i,j,m,q=0,p=0;
	struct node*head,*tail,*new;
	head=tail=(struct node*)malloc(sizeof(struct node));
	head=NULL;
	for(i=0;i<len1;i++){
		for(j=0;j<len2;j++){
			q=0;
			for(m=0;m<3;m++){
				if(str1[i+m]==str2[j+m]&&str1[i+m]!=' ') q++;
				else break;
			}
			if(q==3){
				p=0;
				while(str1[i+p]==str2[j+p]&&str1[i+p]!=' '){
					new=(struct node*)malloc(sizeof(struct node));
					new->ch=str1[i+p];
					new->next=NULL;
					if(head==NULL) head=new;
					else tail->next=new;
					tail=new;
					str1[i+p]=' ';
					str2[j+p]=' ';
					p++;
					
				}
				new=(struct node*)malloc(sizeof(struct node));
				new->ch=',';
				new->next=NULL;
				tail->next=new;
				tail=new;
			}
		}
	}
	return head;
}

void PrintSubStr(struct node*t)
{
	while(t!=NULL){
		printf("%c",t->ch);
		t=t->next;
		if(t->next==NULL) break;
	}
}
int main()
{
	char str1[81],str2[81];
	InputString(str1,str2);
	struct node*t;
	t=FindSubStr(str1,str2);
	PrintSubStr(t);
	return 0;
}
