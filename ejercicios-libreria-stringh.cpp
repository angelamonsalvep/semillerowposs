
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <iostream>
#include <stdlib.h>
#define fgets_(str) fgets(str, sizeof str, stdin)

char string1[50];
char string2[50];
int numberChar;
char fraseIntro[] = "Aqui vamos a trabajar con la función: ";


int myStrlen(char *cadena);
void optionMenu();
void validateOption(int x, char txtStrlen[], char txtStrcat[], char txtStrcpy[], char txtStrncat[], char txtStrncpy[], char txtStrcmp[], char txtStrncmp[] );
char* myStrcat(char* s1, char* s2);
char *myStrcpy(char *dest, char *src);
char *myStrncat(char *dest, char *src, int numberChar);
char *myStrncpy(char *dest, char *src, int numberChar);
int myStrcmp(char *s1, char *s2);
int myStrncmp(char *s1, char *s2, int n);
int mayor (int x, int y);
    

main()

{
	optionMenu();	
	 
	
}

void optionMenu()
{
	setlocale(LC_ALL, "");
	
	char txtStrlen[]= "Strlen: función que permite saber la longitud de una cadena. \n" ;
	char txtStrcat[] = "Strcat: concatena dos cadenas. \n" ;
	char txtStrcpy[] = "Strcpy: copia una cadena en otra. \n";
	char txtStrncat[] = "Strncat: concatena un numero de caracteres en otra cadena. \n";
	char txtStrncpy[] = "Strncpy: copia un numero de caracteres en otra cadena. \n";
	char txtStrcmp[] = "Strcmp: compara dos cadenas, retorna 0 si son exactamente iguales. Retorna -1 si la cadena 1 es menor que la cadena 2, retorna 1 si la cadena 1 es mayor que la cadena 2. \n";
	char txtStrncmp[] = "Strncmp: compara un numero de caracteres de ambas cadenas, retorna 0 si son exactamente iguales, retorna -1 si la cadena 1 es menor que la cadena 2, retorna 1 si la cadena1 es mayor que la cadena 2. \n";
	
	char option1[5] = "1. ";
	char option2[5] = "2. ";
	char option3[5] = "3. ";
	char option4[5] = "4. ";
	char option5[5] = "5. ";
	char option6[5] = "6. ";
	char option7[5] = "7. ";   
	
		
	int optionId;

	
	printf ("\n\nVamos a usar la libreria string.h  \n\n");
	printf("Escribe el numero de la opcion que deseas probar. \n\n" );
	printf (myStrcat(option1, txtStrlen));
	printf (myStrcat(option2, txtStrcat));
	printf (myStrcat(option3, txtStrcpy));
	printf (myStrcat(option4, txtStrncat));
	printf (myStrcat(option5, txtStrncpy));
	printf (myStrcat(option6, txtStrcmp));
	printf (myStrcat(option7, txtStrncmp));
	
	scanf("%d", &optionId);
	fflush( stdin );
		
	validateOption(optionId, txtStrlen, txtStrcat, txtStrcpy, txtStrncat, txtStrncpy, txtStrcmp, txtStrncmp);
	
	
}


void validateOption(int x, char txtStrlen[], char txtStrcat[], char txtStrcpy[], char txtStrncat[], char txtStrncpy[], char txtStrcmp[], char txtStrncmp[] )
{
	
	switch (x) {
		
		case 1:
			
			{
				char cadena[50];
				
				printf(" %s %s ",fraseIntro,txtStrlen);
				printf("Para probar esta función escriba a continuación una cadena de caracteres. ");
				
				fgets_(cadena);
				fflush( stdin );

			    char longitud[5];
			    
			    int longitudCadena=myStrlen(cadena);
			
				sprintf(longitud,"%d",longitudCadena);
				
				char fraseRespuesta[] = "\n La cadena de caracteres que ingresaste tiene una longitud de: ";
				printf(myStrcat(fraseRespuesta,longitud));
				
				optionMenu();
				
				
			}
			
			break;
			
		case 2:
			
			{
				printf(" %s %s ",fraseIntro,txtStrcat);
				printf("Para probar esta función necesitaremos dos cadenas de caracteres. ");
				
				printf("\nEscribe la primera cadena. \n");
				
				gets(string1);
				
				printf("\nEscribe la segunda cadena. \n");
				
				gets(string2);
				
				printf("\n Este es el resultado de las cadenas concatenadas: \n");
							
				printf(" %s ", myStrcat(string1, string2));
				
				optionMenu();
				
				
			}
			
			break;	
			
			
			case 3:
			
			{
				
				printf(" %s %s ",fraseIntro,txtStrcpy);
				printf("Para probar esta función debes escribir a continuación dos cadena de caracteres. ");
				
				printf("\nEscribe la primera cadena. \n");
								
				gets(string1);

				printf("\nEscribe la segunda cadena. \n");
				
				gets(string2);
				
				printf("\n Aquí se muestra la nueva cadena con el valor copiado que se ingresó por teclado. "); 
				printf(myStrcpy(string1,string2));
				
				optionMenu();
				
				
			}
			
			break;	
			
			case 4:
			
			{
				
				printf(" %s %s ",fraseIntro,txtStrncat);
				printf("Para probar esta función necesitaremos dos cadenas de caracteres y un entero que indique la cantidad de caracteres que se van a tener en cuenta para la concatenación. ");
				
				printf("\nEscribe la primera cadena. \n");
				
				gets(string1);
				
				printf("\nEscribe la segunda cadena. \n");
				
				gets(string2);
				
				printf("\nEscribe la cantidad de caracteres que se tedran en cuenta para la concatenación de las cadenas. \n");
				
				scanf("%d", &numberChar);
				fflush( stdin );
				
				printf(myStrncat(string1,string2,numberChar));
				
				optionMenu();
				
				
			}
			
			break;	
			
			case 5:
			
			{
				printf(" %s %s ",fraseIntro,txtStrncpy);
				printf("Para probar esta función necesitaremos dos cadena de caracteres y un entero que indique la cantidad de caracteres que se van a copíar en otra cadena. ");
				
				printf("\nEscribe la primera cadena. \n");
				
				gets(string1);
				
				printf("\nEscribe la segunda cadena. \n");
				
				gets(string2);
				
				printf("\nEscribe la cantidad de caracteres que se copiaran. \n");
				
				scanf("%d", &numberChar);
				fflush( stdin );
							
				printf(myStrncpy(string1,string2,numberChar));
				
				optionMenu();
				
				
			}
			
			break;	
			
			case 6:
			
			{
				printf(" %s %s ",fraseIntro,txtStrcmp);
				printf("Para probar esta función necesitaremos 2 cadena de caracteres");
				
			    printf("\nEscribe la primera cadena. \n");
				
				gets(string1);
				
				printf("\nEscribe la segunda cadena. \n");
				
				gets(string2);
				
				char cResultop6[5];
				int result=myStrcmp(string1,string2);
				
			    sprintf(cResultop6,"%d",result);
				
				char fraseRespuestaOp6[30]= "El resultado es: ";
			    
			    printf(myStrcat(fraseRespuestaOp6, cResultop6));
				
				optionMenu();
				
				
			}
			
			break;	
			
			case 7:
			
			{
				printf(" %s %s ",fraseIntro,txtStrncmp);
				printf("Para probar esta función necesitaremos 2 cadena de caracteres y un entero que indique la cantidad de caracteres que se van a tener en cuenta en la comparación de las cadenas");
				
			    printf("\nEscribe la primera cadena. \n");
				
				gets(string1);
				
				printf("\nEscribe la segunda cadena. \n");
				
				gets(string2);
				
			    printf("\nEscribe cuantos caracteres se tendran en cuenta para la comparación de cadenas. \n");
				
				scanf("%d", &numberChar);
				fflush( stdin );
				
				char cResult[5];
				int result=myStrncmp(string1,string2, numberChar);
				
			    sprintf(cResult,"%d",result);
			    
			    char fraseRespuestaOp7[30]= "El resultado es: ";
			    
			    printf(myStrcat(fraseRespuestaOp7, cResult));
				
				
				optionMenu();
				
				
			}
			
			break;	
    }
	
}



int myStrlen(char *cadena){
	
	//dimensión de la cadena
	int n;
		
	n=0;
	
	//se recorre cada posición de la cadena
	while(cadena[n] != '\0')
	{
		n++;
	}
	
				
	return n;
	
	
}

char* myStrcat(char* dest, char* src){
	
	//guardamos las longitudes de las cadenas
	int longDest= myStrlen(dest);
	int longSrc= myStrlen(src);
								
				
	for(int n=0;n<longSrc;n++) {
					
			dest[longDest]=src[n];
			longDest++;
					
			}
			
	dest[longDest]='\0';		

	return (dest); 
		
}

char *myStrcpy(char *dest, char *src){
	

//guardamos la longitude de la cadena origen
	int longSrc= myStrlen(src);
	
	int n;						
				
	for(n=0;n<longSrc;n++) {
					
			dest[n]=src[n];
					
			}
			
	dest[n]='\0';		

	return (dest); 

		
}

char *myStrncat(char *dest, char *src, int numberChar){
	
	int longDest= myStrlen(dest);
	
	for(int n=0;n<numberChar;n++) {
					
			dest[longDest]=src[n];
			longDest++;
					
			}
			
	dest[longDest]='\0';		

	return (dest); 
 
		
}

char *myStrncpy(char *dest, char *src, int numberChar){
	
	int n;						
				
	for(n=0;n<numberChar;n++) {
					
			dest[n]=src[n];
					
			}
			
	dest[n]='\0';		

	return (dest); 



		
}

int myStrcmp(char *s1, char *s2){
	
	//guardamos las longitudes de las cadenas
	int longS1= myStrlen(s1);
	int longS2= myStrlen(s2);
	int longMax= mayor(longS1, longS2);
	
	
	for(int n=0;n<longMax;n++) {
					
			if(s1[n]!=s2[n])
			{
					if(s1[n]>s2[n])
					{
						return 1;
					}
					
					else
					
					return -1;
			}
			
			
					
			}
			
		return 0;
	
		
}

int mayor (int x, int y)
{
	if(x>y)
	{
		return x;
	}
	 return y;
	
}

int myStrncmp(char *s1, char *s2, int numberChar){
	
	for(int n=0;n<numberChar;n++) {
					
			if(s1[n]!=s2[n])
			{
					if(s1[n]>s2[n])
					{
						return 1;
					}
					
					else
					
					return -1;
			}
			
			
					
			}
			
		return 0;
		
}

