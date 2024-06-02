#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	int x[4][13],a[13],b[13],c[13],d[13],y[4][13]={0};
	int i,j,k;
	for(i=0;i<4;i++)
	{
		k=1;
		for(j=0;j<13;j++)
		{
			x[i][j]=k;
			k++;
		}
		k=1;
	}
    srand((unsigned int) time(0));
	int n1,n2,ii;
	for(ii=0;ii<52;ii++)
	{
		do{
		n1=rand()%4;
		n2=rand()%13;
	    }while(y[n1][n2]!=0); 
	y[n1][n2]=ii;
	}
	for(ii=0;ii<56;ii++)
	{
		if(ii==13||ii==26||ii==39)
		{
			printf("\n");
		}
		for(n1=0;n1<4;n1++)
		{
			for(n2=0;n2<13;n2++)
			{
				if(y[n1][n2]==ii)
				{
					switch(n1)
					{
						case 0:printf("ºìÌÒ%d\n",n2);break;
						case 1:printf("·½¿é%d\n",n2);break;
						case 2:printf("²Ý»¨%d\n",n2);break;
						case 3:printf("ºÚÌÒ%d\n",n2);
					}
				}
			}
		}
	}
	system("PAUSE");
	return 0;
}
