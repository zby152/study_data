#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int n;
	float frac=1.0;
	
	for( n=1 ; n<=42; n++)
	     frac=frac/10 ;
	     
    for( n=43; n<=47;n++){
    	frac=frac/10 ;
		printf("n=%d, frac= %.8g\n", n, frac); 
	}
	
	system("PAUSE");
	return 0;
}
