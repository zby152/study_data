#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char *letters[5];
	char q[50];
	int i,j,t,m=0;
	int n=0;
	int num[5];
	for(i=0;i<5;i++){
	letters[i]=(char *)malloc(50);}
	printf("ÇëÊäÈëÎå´®×ÖÄ¸£º\n");
	for(i=0;i<5;i++)//ÊäÈë×Ö·û´® 
	{
		gets(letters[i]);
	 } 
    for(i=0;i<5;i++)//Í³¼Æ×Ö·û´®×Ö·ûÊýÄ¿ 
    {
       while(*letters[i]!='\0')
       {
	   if(*letters[i]!=' ')	n++;
       	*letters[i]++;
       	m++;
	   }
	   letters[i]-=m;
	   num[i]=n;
	   n=0;
	   m=0;
    }
    for(i=0;i<5;i++)//Ã°ÅÝÅÅÐò 
     { 
	  for(j=0;j<5-i-1;j++)
       {
       	if(num[j]>num[j+1])
       	{
       		t=num[j];
       	    num[j]=num[j+1];
       		num[j+1]=t;
       		strcpy(q,letters[j]);
       		strcpy(letters[j],letters[j+1]);
       		strcpy(letters[j+1],q);
		   }
	   }
	} 
	for(i=0;i<5;i++){
	printf("%d\t",num[i]);
	puts(letters[i]);
	}
	for(i=0;i<5;i++){
	printf("%c",*(letters[i]+2));
}
	for(i=0;i<5;i++) {
	free(letters[i]);
	}
	return 0;
}
