#include <stdio.h>
#include <stdlib.h>
#include "myString.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	myStrting mystring;
	
	char* string1;
	
	printf("\nEscribe la primera cadena. \n");
				
	scanf("%s", &string1);
	
	int charLong= myString.myStrlen(string1);
	
	printf("La cadena que ingresaste tiende una longitud de : %i\n",charLong);
	
	
	
	
	
	return 0;
	
	
}


