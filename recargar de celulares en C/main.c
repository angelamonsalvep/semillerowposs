#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include<windows.h>

#define messageInvalidEmail printf("\nEl correo ingresado es invalido.\n\n") //Definimos el mensaje de correo invalido
#define messageInvalidPass printf("\nLa contraseña ingresada no es valida.\n\n") //Definimos el mensaje de contraseña invalido
#define messageEmailNotExist printf("\nEl correo ingresado no existe.\n\n") //Definimos el mensaje de correo inexistente
#define messageIncorrectPassword printf("\nLa contraseña ingresada no es correcta.\n\n") //Definimos el mensaje de correo inexistente

char email[30];
char pass[15];
int key;
int countAskForCellNumber=0;
int countAskForAmount=0;
int amount1, amount2;


struct LogIn
{
    char email[30];
    char pass[15];
};

struct LogIn logInuser[10];
int countLogInUser=0;
int poss;


void validateLogin();
void askForEmail();
int validateEmailFormat();
void registerUser();
void askForPass();
int validatePassFormat();
void saveLogInData();
void showRegistrationConfirmationMessage();
char *myStrncpy(char *dest, char *src);
int myStrcmp(char *s1, char *s2);
int searchEmail();
int myStrlen(char *cadena);
void askForPassLoop();
void authorizeAccessSystem();
void validateUserPassLoop();
void rechargeCellPhone();
void messageInvalidKey();
char* askForCellPhoneNumber(char cellPhoneNumber[]);
void validateNumberFormat(char cellNumber1[], char cellNumber2[]);
void validateAmount2(int amount);
int askForAmount();
void validateAmount();
void ShowRechargeConfirmation();
int mystrInt(char* charNumbers);


int main() {
	
	setlocale(LC_ALL, "");
	
	validateLogin();

}

void askForEmail()
{
	printf("Ingresa Correo: ");
	gets(email);
}

int validateEmailFormat()
{
	int i=0;
	int countAtSign=0;
	int countDot=0;
	int countCharAtSign=0;
	int countCharDot1=0;
	int countCharDot2=0;
	while(email[i]!='\0')
	{
		//muestra mensaje cuando encuentra un espacio
		if(email[i]==' ')
		{
			messageInvalidEmail;
			return 1;
		}
		
		
		if(email[i]=='@')
		{
			//muestra mensaje cuando encuentra un @ antes del quinto caracter
			if(i<5 )
			{
			messageInvalidEmail;
			return 1;

			}
			else
			{
				countAtSign++;
				
				//muestra mensaje cuando encuentra mas de un 1 @
				if(countAtSign>1)
				{
					messageInvalidEmail;
					return 1;
				
				}	
			}
			
		}
		
		if(countAtSign==1)
		{
			//muestra mensaje si despues de escribir el @ encuentra mas de 2 puntos(.)
			if(countDot>2)
			{
				messageInvalidEmail;
				return 1;
			}
		}
		
		if(email[i] == '.')
		{ 	
		
			//muestra mensaje si se escriben 2 puntos seguidos o si se escribe un @ antes de 1 punto
			if(email[i-1] == '.' || email[i-1] == '@')
			{
				messageInvalidEmail;
				return 1;
			}
			else
			{
				if(countAtSign>0)
				{
					countDot++;
				}
				
			}
		}
		
		i++;
		if(countAtSign>0)
		{
			if(countDot<1)
			{
				countCharAtSign++;
			}
			
		}
		
		if(countDot>0)
		{
			if(countDot==1)
			{
				countCharDot1++;
			}
			else
			{
				countCharDot2++;
			}
			
		}
		
	}
	
	//muestra mensaje cuando:
	//hay mas de 3 caracteres desde el primer punto hasta llegar al siguiente punto si lo hay o hasta el final del email
	//hay mas de 2 caracteres desde el segundo punto hasta el final
	//no hay ningun @
	// no hay ningun punto
	//hay menos de 5 caracteres desde el arroba hasta el primer punto
	if(countCharDot1>4 || countCharDot2>3 || countAtSign==0 || countDot==0 || countCharAtSign<5)
		{
			messageInvalidEmail;
			return 1;
		}
	
	return 0;
}


int searchEmail()
{
	int i=0;
	int result;
	
	while(i<countLogInUser)
	{
		result= myStrcmp(logInuser[i].email, email);
		if(result==0)
		{
			poss=i;
		}
		else
		{
			messageEmailNotExist;
			return 1;
		}
		
		
		i++;
	}
	
	if(i==0)
	{
		messageEmailNotExist;
		return 1;
	}
	
	return 0;

}

void askForPass()
{
	int i=0;
	char character;
	
	printf("Ingresa Contraseña: ");
	
	while(character = getch())
	{
		if(character == 13)
		{
			pass[i] = '\0';
			break;
			
		} else if(character == 8)
		{
			if(i>0)
			{
				i--;
				printf("\b \b");
			}
			
		} else
			{
				if(i<15)
				{
					printf("*");
					pass[i] = character;
					i++;
				}
			}
		
	}
	
	
}

void askForPassLoop()
{
	askForPass();
	while(validatePassFormat()!=0)
		{
			askForPass();
			
		}
		
}

int validatePassFormat()
{
	int i=0;
	
	while(pass[i]!='\0')
	{
		if(pass[i]==' ')
		{
			messageInvalidPass;
			return 1;
		}
		
		i++;
		
		
	}
	
	//se muestra mensaje si la contraseña tiene menos de 8 caracteres
	if(i<8)
	{
		messageInvalidPass;
		return 1;
	}
	
	return 0;
	
}


int validateUserPass()
{
	if(myStrcmp(logInuser[poss].pass, pass)!=0)
	{
		messageIncorrectPassword;
		return 1;
	}
	
	return 0;
}

void validateUserPassLoop()
{
	askForPassLoop();
	while(validateUserPass()!=0)
	{
		validateUserPassLoop();
	}
}

void showLoginSuccessfulMessage()
{
	
}

void showMainMenu()
{
	int option;
	int optionExit;
	
	
	system("cls");
	
	printf("BIENVENIDO AL SISTEMA DE RECARGAS\n\n");
	printf("MENU PRINCIPAL\n\n");
	
	printf("1. RECARGAS\n\n");
	printf("2. SALIR\n\n");
	
	printf("Selecciona una de las opciones.\n\n");
	
	scanf("%d", &option);
	fflush( stdin );
	
	printf("\n");
	
	switch(option)
	{
		case 1:
				rechargeCellPhone();
				break;
			
		case 2: 
			
				printf("Seguro que desea salir? \n\n");
				printf("1. Si\n");
				printf("2. No\n\n");
				scanf("%d", &optionExit);
				fflush( stdin );
				printf("\n");
				
				switch(optionExit)
				{
					case 1: 
						validateLogin();
						break;
					case 2: 
						showMainMenu();
						break;
					default:
						messageInvalidKey();
						
						
				}
		
		default:
			messageInvalidKey();
	}
	
	
	
	
}

void messageInvalidKey()
{
	printf("El valor ingresado no es valido, digite un valor entre 1 y 2");
	printf("\n\nOprima la tecla Enter para seleccionar una opción valida\n\n");
	while(key=getch())
	{
		if(key==13)
		{
			showMainMenu();	
		}
	}
}

void saveLogInData()
{
	
	myStrncpy(logInuser[countLogInUser].email, email);
	myStrncpy(logInuser[countLogInUser].pass, pass);
	countLogInUser++;
	
}

void showRegistrationConfirmationMessage()
{
	printf("\n\n¡¡REGISTRO EXITOSO!! \n\n");
}

char* askForCellPhoneNumber(char cellPhoneNumber[])
{
	
	int i=0;
	char digit;
	
	if(countAskForCellNumber==0)
	{
		printf("\n\nIngresa el número de celular a recargar, recuerda que debe tener 10 digitos: \n\n");
	}
	else
	{
		printf("\n\nEscribe nuevamente el número de celular para confirmar: \n\n");
	}
	
	
	while(digit = getch())
	{
		if(digit == 13)
		{
			if(i>=9)
			{
				cellPhoneNumber[i] = '\0';
				countAskForCellNumber++;
				break;
			}
			 
			
		} else if(digit == 8)
		{
			if(i>0)
			{
				i--;
				printf("\b \b");
			}
			
		} else if(digit >= 48 && digit <= 57)
			{
				if(i<10)
				{
					printf("%c", digit);
					cellPhoneNumber[i] = digit;
					i++;
				}
				
			}
	}
	
	return cellPhoneNumber;
	
}


void validateNumberFormat(char cellNumber1[], char cellNumber2[])
{
	system("cls");
	
	printf("RECARGAS - INGRESAR NÚMERO DE CELULAR A RECARGAR");
	
	int cell1equalcell2= myStrcmp(askForCellPhoneNumber(cellNumber1), askForCellPhoneNumber(cellNumber2));
	while(cell1equalcell2!=0)
	{
		printf("\n\nLos numeros ingresados no coinciden.\n\n");
		printf("\n\nOprima la tecla enter para volver a ingresar el número de celular a recargar\n\n");
		countAskForCellNumber=0;
		while(key=getch())
		{
			if(key==13)
			{
				rechargeCellPhone();
			}
		}
		
		
	}
	
	if(cell1equalcell2==0)
	{
		countAskForCellNumber=0;
		printf("\n\nSe ha validado correctamente el número de celular.\n\n");
		printf("\n\nOprima la tecla enter para ingresar el monto a recargar.\n\n");
		
		while(key=getch())
		{
			if(key==13)
			{
				validateAmount();
			}
		}
		
	}
}


int askForAmount()
{
	int amount=0;
	int i=0;
	char digit;
	char charAmount[6];
	
	if(countAskForAmount==0)
	{
		printf("\n\nIngresa el monto a recargar, recuerda que se acepta desde $1000 en adelante: \n\n");
	}
	else
	{
		printf("\n\nEscribe nuevamente el monto para confirmar: \n\n");
	}
	
	while(digit = getch())
	{
		if(digit == 13)
		{
			if(i>=4)
			{
				charAmount[i] = '\0';
				break;
			}
			 
			
		} else if(digit == 8)
		{
			if(i>0)
			{
				i--;
				printf("\b \b");
			}
			
		} else if(digit >= 48 && digit <= 57)
			{
				if(i<10)
				{
					printf("%c", digit);
					charAmount[i] = digit;
					i++;
				}
				
			}
	}
	
	amount=mystrInt(charAmount);
	return amount;
	
}

void validateAmount()
{	
	system("cls");
	printf("RECARGAS - INGRESAR MONTO");
	
	while(countAskForAmount==0)
	{
		amount1= askForAmount();
		validateAmount2(amount1);
	}
	while(countAskForAmount==1)
	{
		amount2= askForAmount();
		validateAmount2(amount2);
		
	}
	
	while(amount1!=amount2)
	{
		printf("\n\nLos montos ingresados no coinciden.\n\n");
		printf("\n\nOprima la tecla enter para volver a ingresar el monto a recargar\n\n");
		countAskForAmount=0;
		while(key=getch())
		{
			if(key==13)
			{
				
				validateAmount();
			}
		}
	}	
	
	countAskForAmount=0;
	printf("\n\nSe ha validado correctamente el monto.\n\n");
	ShowRechargeConfirmation();
	
}

void validateAmount2(int amount)
{
	while(amount<1000)
	{
		
		printf("No se aceptan montos menores a $1000");
		printf("\n\nOprima la tecla enter para ingresar un monto valido.\n\n");
		
		while(key=getch())
		{
			if(key==13)
			{
				validateAmount();
			}
		}
	}
	
	if(amount>=1000)
	{
		countAskForAmount++;
	}
}


void ShowRechargeConfirmation()
{
	printf("Proceso finalizado con exito");
	
	printf("\n\nOprima la tecla enter para volver al menú principal\n\n");
		while(key=getch())
		{
			if(key==13)
			{
				showMainMenu();
			}
		}
	
}

void validateLogin()
{
	system("cls");
	
	printf("INICIO DE SESIÓN\n\n");
	
	askForEmail();
	while(validateEmailFormat()== 1)
	{
		askForEmail();
	}
	if(searchEmail()==0)
	{
		askForPassLoop();
	}
	else
	{
		printf("\n\nOprima la tecla enter para registrar un nuevo usuario\n\n");
		while(key=getch())
		{
			if(key==13)
			{
				registerUser();
			}
		}
		
	}
	
	while(validateUserPass()!=0)
	{
		validateUserPassLoop();
	}
	
	authorizeAccessSystem();
	
	
}


void authorizeAccessSystem()
{
	
	showMainMenu();
}

void registerUser()
{
	system("cls");
	printf("REGISTRO DE USUARIO\n\n");
	
	askForEmail();
	while(validateEmailFormat()== 1)
	{
		askForEmail();
	}
	
	askForPassLoop();
	
	saveLogInData();
	showRegistrationConfirmationMessage();
	printf("\n\nOprima la tecla enter para Iniciar Sesión\n\n");
		while(key=getch())
		{
			if(key==13)
			{
				validateLogin();
			}
		}
	
	
	
}

void rechargeCellPhone()
{
	
	char cellNumber1[10];
	char cellNumber2[10];
	validateNumberFormat(cellNumber1, cellNumber2);
	validateAmount();
	
	
	
}

char *myStrncpy(char *dest, char *src)
{
	
	int n=0;	
	
	while(src[n]!='\0')	
	{
		
		dest[n]=src[n];
		n++;
	}				
	
	dest[n]='\0';		

	return (dest); 		
}

int mystrInt(char* charNumbers)
{
	int i=0;
	int result=0;
	int countbase;
	int longChar= myStrlen(charNumbers);
	switch(longChar)
	{
		case 1: 
			countbase= 1;
			break;
		case 2: 
			countbase= 10;
			break;
		case 3: 
			countbase= 100;
			break;	
		case 4: 
			countbase= 1000;
			break;
		case 5: 
			countbase= 10000;
			break;
		case 6: 
			countbase= 100000;
			break;	
			
	}
	
	while(i<longChar)
	{
		
    	int digit = charNumbers[i] - '0';
		result= result+(digit * countbase);
		countbase= countbase / 10;
		i++;
	}
	
	return result;
	
}

int myStrcmp(char *s1, char *s2)
{
	
	
	if(myStrlen(s1)==myStrlen(s2))
	
	{
		int n;
		
		for(n=0;s1[n]!='\0';n++) 
		{			
			if(s1[n]!=s2[n])
			{
				if(s1[n]>s2[n])
				{
					return 1;
				}
					
				else
				{
					return -1;
				}
			}
		
		}		
	}
	else
	{
		return 1;
	}
			
	return 0;
}

int myStrlen(char *cadena)
{
	int n=0;
	
	//se recorre cada posición de la cadena
	while(cadena[n] != '\0')
	{
		n++;
	}
				
	return n;
}


