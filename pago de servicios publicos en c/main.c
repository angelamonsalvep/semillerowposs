#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include<windows.h>
#include <time.h>
#include <pthread.h>

#define messageIdCardNotExist printf("\nEl N. de cédula ingresado no se ha registrado.\n\n") //Definimos el mensaje de idCard inexistente
#define messageIncorrectPassword printf("\nLa contraseña ingresada no es correcta.\n\n") //Definimos el mensaje de contraseña incorrecta




//variables globales
char idCard[12];
char nameUser[15];
char pass[10];
int countAskForAmount;
int amount1, amount2;
int key;
int balance=0;
int typeInvoice;
char invoiceNumber[10];
int payAmount=0;

struct User
{
    char idCard[12];
	char nameUser[15];
	char pass[10];
	int balance;
};

struct User user[10];
int countUser;
int poss;
int isRegister=0;
int isMainInterface=0;

pthread_t hilo2;
pthread_t hilo1;
// VARIABLE DE TIPO CURSOR
POINT cursor;


//declaración de métodos
void validateUser();
void receiveOnlyNumbers(char receivedString[],int minDigits, int maxDigits);
void askForIdCard();
void askForName();
void registerUser();
void askForPass();
void myStrncpy(char *dest, char *src);
int mystrInt(char* charNumbers);
int myStrcmp(char *s1, char *s2);
int myStrlen(char *cadena);
void saveUserData();
void validateAmount();
void validateAmount2(int amount);
void ShowRegisterConfirmation();
void deposit();
int searchIdCard();
void saveUserBalance();
int validateUserPass();
void validateUserPassLoop();
void messageInvalidKey();
void *showMainInterface(void *args);
void showDateAndHour();
void gotoxy(int x, int y);
void *updateDateAndHour(void *args);
void executeThread();
void showArrayChar(char *arrayChar);
void showUserData();
void pay();
void showInvoiceMenu();
void askForInvoiceNumber();
int validateBalance();
void deductPaymentFromBalance();
void cancelPayment();
char *identifyTypeOfInvoice();
void showPaymentDetails();
void finalizePayment();



int main() {
	
	setlocale(LC_ALL, "");
	validateUser();

	
}

void gotoxy(int x,int y)
{  
    HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);  
 } 

void *updateDateAndHour(void *args)
{

	while(isMainInterface==1)
	{
		gotoxy(0, 4);
		showDateAndHour();
		gotoxy(0, 16);
		sleep(1);
	}
	
	if(isMainInterface==0)
	{
		pthread_exit(NULL);
	}
}

void showDateAndHour()
{
	int hour;
	int hourFormated;
	char daytripChar[2];
	time_t t;
  	struct tm *tm;
  	char fechayhora[100];

  	t=time(NULL);
  	tm=localtime(&t);
  	hour= tm->tm_hour;
  	if(hour>12)
  	{
  		hour=hour-12;
  		daytripChar[0]='P';
  		daytripChar[1]='M';
  		daytripChar[2]='\0';
	}
	else
	{
		daytripChar[0]='A';
  		daytripChar[1]='M';
  		daytripChar[2]='\0';
	}
  	printf ("Fecha: %02d/%02d/%d Hora: %02d:%02d %s\n", tm->tm_mday, 1+tm->tm_mon, 1900+tm->tm_year, hour, tm->tm_min, daytripChar);
  	fflush(stdout);
}

int validateUserPass()
{
	if(myStrcmp(user[poss].pass, pass)!=0)
	{
		messageIncorrectPassword;
		return 1;
	}
	
	return 0;
}

void validateUserPassLoop()
{
	askForPass();
	while(validateUserPass()!=0)
	{
		validateUserPassLoop();
	}
}



void messageInvalidKey()
{
	printf("El valor ingresado no corresponde a una opción valida\n\n");
	printf("\n\nOprima la tecla Enter para seleccionar una opción valida\n\n");
	while(key=getch())
	{
		if(key==13)
		{
			executeThread();
		}
	}
}


void validateUser()
{
	system("cls");
	printf("Inicio de Sesión\n\n");
	askForIdCard();
	if(searchIdCard()==0)
	{
		askForPass();
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
	
	
	executeThread();
	
	
}

void receiveOnlyNumbers(char receivedString[],int minDigits, int maxDigits)
{
	int i=0;
	char digit;
	
	while(digit = getch())
	{
		if(digit == 13)
		{
			if(i>=minDigits)
			{
				receivedString[i] = '\0';
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
				if(i<maxDigits)
				{
					printf("%c", digit);
					receivedString[i] = digit;
					i++;
				}
				
			}
	}
	
}

void askForIdCard()
{
	printf("N. de Cédula: ");
	receiveOnlyNumbers(idCard, 10, 12);
	
	
}

void askForName()
{
	printf("\n\nNombres: ");
	gets(nameUser);
	while(myStrlen(nameUser)<5)
	{
		printf("El nombre ingresado no es valido, por favor ingrese su nombre completo.");
		askForName();
	}
}

void askForPass()
{
	int i=0;
	char character;
	
	printf("\n\nClave(minimo de 8 caracteres alfanumericos - max. 10): ");
	
	while(character = getch())
	{
		if(character == 13)
		{
			if(i>=8)
			{
				pass[i] = '\0';
				break;
			}
			
			
		} else if(character == 8)
		{
			if(i>0)
			{
				i--;
				printf("\b \b");
			}
			
		} else
			{
				if(i<10)
				{
					printf("*");
					pass[i] = character;
					i++;
				}
			}
		
	}
	
	
}

int searchIdCard()
{
	int i=0;
	int result;
	
	while(i<countUser)
	{
		result= myStrcmp(user[i].idCard, idCard);
		if(result==0)
		{
			poss=i;
		}
		else
		{
			messageIdCardNotExist;
			return 1;
		}
		
		
		i++;
	}
	
	if(i==0)
	{
		messageIdCardNotExist;
		return 1;
	}
	
	return 0;

}

void saveUserData()
{
	
	myStrncpy(user[countUser].idCard, idCard);
	myStrncpy(user[countUser].nameUser, nameUser);
	myStrncpy(user[countUser].pass, pass);
	countUser++;
	
}

void registerUser()
{
	system("cls");
	printf("REGISTRO DE USUARIO\n\n");
	
	askForIdCard();
	askForName();
	askForPass();
	isRegister=1;
	
	printf("\n\nPara completar el registro debes realizar un deposito de minimo $1000");
	
	printf("\n\nOprima la tecla enter para realizar el depósito.\n\n");
		
	while(key=getch())
	{
		if(key==13)
		{
			deposit();
		}
	}
	
	
}

int askForAmount()
{
	int amount=0;
	
	char charAmount[6];
	
	if(countAskForAmount==0)
	{
		printf("\n\nIngresa el monto, recuerda que se acepta desde $1000 en adelante: \n\n");
	}
	else
	{
		printf("\n\nEscribe nuevamente el monto para confirmar: \n\n");
	}
	
	receiveOnlyNumbers(charAmount,4, 6);
	
	amount=mystrInt(charAmount);
	return amount;
	
}


void validateAmount()
{	
	
	system("cls");
	printf("INGRESAR MONTO");
	
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
		printf("\n\nOprima la tecla enter para volver a ingresar el monto\n\n");
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

void ShowRegisterConfirmation()
{
	saveUserData();
	printf("Registro exitoso");
	
	printf("\n\nOprima la tecla enter para ir al menú principal\n\n");
		while(key=getch())
		{
			if(key==13)
			{
				isRegister=0;
				executeThread();
			}
		}
	
}

void saveUserBalance()
{
	user[poss].balance= balance;
}

void deposit()
{
	validateAmount();
	balance= user[poss].balance+amount1;
	saveUserBalance();
	printf("El monto se ha sumado a tu saldo con exito.\n\n");
	
	if(isRegister==1)
	{
		ShowRegisterConfirmation();
	}
	
	
	
	sleep(3);
	
	
	
	
}

void executeThread()
{
	pthread_create(&hilo2, NULL,showMainInterface,NULL);
	
	pthread_create(&hilo1, NULL,updateDateAndHour,NULL);
	
	pthread_join(hilo2, NULL);
	pthread_join(hilo1, NULL);
	
	
}

void showArrayChar(char *arrayChar)
{
	//esta función recorre un array de caracteres
	
	int longArray=myStrlen(arrayChar);
	
	int n;
	
	
	for(n=0; n<longArray; n++)
	{
		printf("%c", arrayChar[n]);
	}
	
	
}

void showUserData()
{
	
	printf("Usuario: %s      Saldo: %d\n\n", user[poss].nameUser, user[poss].balance);
	
}

void *showMainInterface(void *args)
{
	int option;
	int optionExit;
	isMainInterface=1;
	system("cls");
	
	printf("BIENVENIDO AL SISTEMA DE PAGOS DE SERVICIOS PUBLICOS\n\n");
	printf("MENU PRINCIPAL\n\n\n\n");
	showUserData();
	printf("1. DEPOSITAR\n\n");
	printf("2. PAGAR\n\n");
	printf("3. SALIR\n\n");
	
	printf("Selecciona una de las opciones.\n\n");
	
	
	while(isMainInterface==1)
	{
		gotoxy(0,16);
		scanf("%d", &option);
		fflush( stdin );
	
		printf("\n");
		
		switch(option)
	{
		case 1:
				isMainInterface=0; 
				deposit();
				executeThread();
				break;
				
		case 2:
				if(user[poss].balance==0)
				{
					isMainInterface=0;
					printf("No puede acceder a la ventana de pagos , debido a que no cuenta con saldo, debe realizar un deposito\n\n");
					sleep(5);
					executeThread();
				}
				else
				{
					isMainInterface=0;
					pay();
				
				}
				break;
				
			
		case 3: 
			
				isMainInterface=0;
				gotoxy(0,18);
				printf("Seguro que desea salir? \n\n");
				printf("1. Si\n");
				printf("2. No\n\n");
				scanf("%d", &optionExit);
				fflush( stdin );
				printf("\n");
				
				switch(optionExit)
				{
					case 1: 
						validateUser();
						break;
					case 2: 
						executeThread();
						break;
					default:
						messageInvalidKey();
						break;
						
						
				}
				break;
				
		
		default:
			messageInvalidKey();
			break;
	}
	}
	
	
	
}

void showInvoiceMenu()
{
	int option;
	system("cls");
	
	printf("BIENVENIDO AL SISTEMA DE PAGOS DE SERVICIOS PUBLICOS\n\n");
	printf("VENTANA DE PAGOS\n\n");
	printf("1. CENS\n\n");
	printf("2. AGUAS KAPITAL\n\n");
	printf("3. VEOLIA\n\n");
	printf("4. DIRECTV\n\n");
	printf("5. CANAL EXITO\n\n");
	
	printf("Seleccione el tipo de factura que desea pagar.\n\n");
	
	scanf("%d", &option);
	fflush( stdin );
	printf("\n");
		
	switch(option)
	{
		case 1:
				typeInvoice=1;
				break;
				
		case 2:
				typeInvoice=2;
				break;
		case 3:
				typeInvoice=3;
				break;
		case 4:
				typeInvoice=4;
				break;
		case 5:
				typeInvoice=5;
				break;
	}
	
	
}

void askForInvoiceNumber()
{
	printf("N. de Factura(10 digitos): ");
	receiveOnlyNumbers(invoiceNumber,10,10);
}

int validateBalance()
{
	if(user[poss].balance<payAmount)
	{
		return 1;
	}
	
	return 0;
	
}

void deductPaymentFromBalance()
{
	user[poss].balance=user[poss].balance-payAmount;
}

void showPaymentDetails()
{
	system("cls");
	
	printf("SISTEMA DE PAGOS DE SERVICIOS PUBLICOS\n\n");
	printf("DETALLES DEL PAGO\n\n");
	showDateAndHour();
	printf("\n\nTipo de Factura: %s.\n\n", identifyTypeOfInvoice());
	printf("Número de Factura: %s.\n\n", invoiceNumber);
	printf("Valor pagado: $%d.\n\n", payAmount);
	printf("Saldo actual: $%d.\n\n", user[poss].balance);
	
}

void finalizePayment()
{
	deductPaymentFromBalance();
				
	printf("\n\nPAGO REALIZADO CON EXITO\n\n");
	printf("\n\nOprima la tecla enter para ver los detalles del pago\n\n");
	while(key=getch())
	{
		if(key==13)
		{
			showPaymentDetails();
			printf("\n\nOprima la tecla enter para ir al menú principal\n\n");
			while(key=getch())
			{
				if(key==13)
				{
					executeThread();
						
				}
			}
						
		}
	}
}

void pay()
{
	showInvoiceMenu();
	askForInvoiceNumber();
	printf("\n\nOprima la tecla enter para ingresar el valor a pagar.\n\n");
	while(key=getch())
	{
		if(key==13)
		{
			validateAmount();
			payAmount=payAmount+amount1;
			if(validateBalance()==0)
			{
				finalizePayment();
		
			}
			else
			{
				printf("Lo sentimos, No cuenta con saldo suficiente para realizar este pago.\n\n");
				printf("Su saldo actual es: $%d\n\n", user[poss].balance);
				sleep(8);
				cancelPayment();
			}
		}
	}
	
	
}

char *identifyTypeOfInvoice()
{
	char *typeInvoiceString;

	switch(typeInvoice)
	{
		case 1: 
			typeInvoiceString="CENS";
			break;
			
		case 2:
			
			typeInvoiceString="AGUAS KAPITAL";
			break;
			
		case 3:
			
			typeInvoiceString="VEOLIA";
			break;
		case 4:
			
			typeInvoiceString="DIRECTV";
			break;
		
		case 5:
			
			typeInvoiceString="CANAL EXITO";
			break;
	}
	
	return typeInvoiceString;
}

void cancelPayment()
{
	int option;
	int optionExit;
	system("cls");
	
	printf("SISTEMA DE PAGOS DE SERVICIOS PUBLICOS\n\n");
	printf("AQUI PUEDES REALIZAR UN DEPOSITO O CANCELAR EL PAGO.\n\n");
	printf("1. DEPOSITAR\n\n");
	printf("2. CANCELAR PAGO\n\n");
	
	printf("Seleccione la opción que desee.\n\n");
	
	scanf("%d", &option);
	fflush( stdin );
	printf("\n");
		
	switch(option)
	{
		case 1:
				deposit();
					
				if(validateBalance()==0)
				{
					
					printf("Su saldo actual es: $%d. \n\n", user[poss].balance);
					printf("Ahora puede continuar con el pago. \n\n");
					printf("\n\nOprima la tecla enter para continuar con el pago de la factura N. %s de %s\n\n", invoiceNumber, identifyTypeOfInvoice() );
					while(key=getch())
					{
						if(key==13)
						{
							finalizePayment();
						}
					}
				}
				else
				{
					printf("Lo sentimos, Aun no cuenta con saldo suficiente para realizar el pago de la factura N. %s de %s por valor de $%d.\n\n", invoiceNumber, identifyTypeOfInvoice(), payAmount);
					printf("Su saldo actual es: $%d\n\n", user[poss].balance);
					sleep(9);
					cancelPayment();
				}
			
				break;
				
		case 2:
				printf("Seguro que desea cancelar el pago de la factura N. %s de %s\n\n", invoiceNumber, identifyTypeOfInvoice() );
				printf("1. Si\n");
				printf("2. No\n\n");
				scanf("%d", &optionExit);
				fflush( stdin );
				printf("\n");
				
				switch(optionExit)
				{
					case 1: 
						printf("!!PAGO CANCELADO¡¡, Lo enviaremos al menú principal.");
						payAmount=0;
						sleep(5);
						executeThread();
						break;
					case 2: 
						cancelPayment();
						break;
					default:
						messageInvalidKey();
						
						
				}
				break;
		default:
				messageInvalidKey();
		
	}
}

void myStrncpy(char *dest, char *src)
{
	
	int n=0;	
	
	while(src[n]!='\0')	
	{
		
		dest[n]=src[n];
		n++;
	}				
	
	dest[n]='\0';		
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




