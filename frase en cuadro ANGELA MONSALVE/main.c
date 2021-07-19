#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	
	
	char frase[50];
	printf("Ingrese una frase: ");
	gets(frase);
	
	printf("%s \n", frase);
	
	//guardo la longitud de la frase
	int longFrase= strlen(frase);
	
	//declaro una matriz	
	char cuadro[longFrase][longFrase];
	
	//declaro contadores
	int i;
	int n;
	
	int inc=1;
	int dec=longFrase-2;
		
		
		
	for(i=0;i<longFrase;i++) {
		
		if(i==0)
		{
			for(n=0;n<longFrase;n++){
					
					cuadro[i][n]=frase[n];
					printf("%c", cuadro[i][n]);
					
				}
		}
		
		if(i==longFrase-1)
		{
			int x=longFrase-1;
			for(n=0;n<longFrase;n++){
					
				cuadro[i][n]=frase[x];
				printf("%c", cuadro[i][n]);
				x--;
			}
		}
		
		if (i>0 & i<longFrase-1)
		{
			
			
			for(n=0;n<longFrase;n++){
				
				if(n==0)
				{
					cuadro[i][n]=frase[inc];
					inc++;
					printf("%c", cuadro[i][n]);
				}
				
				
				
				if(n==longFrase-1)
				{
					cuadro[i][n]=frase[dec];
					dec--;
					printf("%c", cuadro[i][n]);
				}
				
				if(n>0 & n<longFrase-1)
				{
					printf(" ");
				}
				
				
				
			}
			
				
	
		}
		
		printf("\n");
		
	
	
    }
    
    
    
    getchar();
    getchar();

	
	
}
