#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	
	int number;
	printf("Ingrese un numero: ");
	
	scanf("%d", &number);
	
	int cont=0;

    
	int numbers[number];
	
	int i;
	int n;
	
	for(i=number; i>0; i--)
	{
		numbers[cont]= i;
		
		
		for(n=0; n<=cont; n++)
		{
			printf("%d", numbers[n]);
		}
		
		printf("\n");
		cont++;
	}
	
}
