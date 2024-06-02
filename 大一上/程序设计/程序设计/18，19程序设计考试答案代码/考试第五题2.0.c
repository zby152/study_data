#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void InputString();
struct node{
	char str;
	struct node*next;
};
struct node *FindSubStr(char str1[],char str2[])
{
	struct node*head,*tail,*new;
	int i,j,p,q,t=0,k;
	head=tail=(struct node*)malloc(sizeof(struct node));
	head=NULL;
	p=strlen(str1);
	q=strlen(str2);
	for(i=0;i<p;i++){
		for(j=0;j<q;j++){
			if(str1[i]==str2[j]&&str1[i+1]==str2[j+1]&&str1[i+2]==str2[j+2]&&((str1[i]>='a'&&str1[i]<='z')||(str1[i]>='A'&&str1[i]<='Z'))&&((str1[i+1]>='a'&&str1[i+1]<='z')||(str1[i+1]>='A'&&str1[i+1]<='Z'))&&((str1[i+2]>='a'&&str1[i+2]<='z')||(str1[i+2]>='A'&&str1[i+2]<='Z'))) 
		    {
		    	while(str1[i+t]==str2[j+t]&&((str1[i+t]>='a'&&str1[i+t]<='z')||(str1[i+t]>='A'&&str1[i+t]<='Z'))){
		    		new=(struct node*)malloc(sizeof(struct node));
		    		new->str=str1[i+t];
		    		new->next=NULL;
		    		if(head==NULL) head=new;
		    		else
		    		tail->next=new;
		    		tail=new;
		    		t++;
		    		if(t>2){
		    			for(k=0;k<t;k++){ 
		    			str1[i+k]=' ';
		    			str2[j+k]=' ';
						}
					}
				}
				if(t!=0){
					t=0;
					new=(struct node*)malloc(sizeof(struct node));
		    		new->str=',';
		    		new->next=NULL;
		    		tail->next=new;
		    		tail=new;
				}
			}
		}
	}
	return head;
}
void PrintSubStr(struct node*answer)
{
	while(answer!=NULL){
		printf("%c",answer->str);
		answer=answer->next;
		if(answer->next==NULL) break;
	}
}
int main()
{
	char str1[81],str2[81];
	struct node*answer;
	gets(str1);
	gets(str2);
	answer=FindSubStr(str1,str2);
	PrintSubStr(answer);
	return 0;
}
