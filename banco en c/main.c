#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define messageInvalidEmail printf("\nEl correo ingresado es invalido.\n\n") //Definimos el mensaje de correo invalido
#define messageInvalidPass printf("\nLa contraseña ingresada no es valida.\n\n") //Definimos el mensaje de contraseña invalido
#define messageEmailNotExist printf("\nEl correo ingresado no existe.\n\n") //Definimos el mensaje de correo inexistente
#define messageIncorrectPassword printf("\nLa contraseña ingresada no es correcta.\n\n") //Definimos el mensaje de correo inexistente
#define messageAccountNotExist printf("\n\n¡¡La cuenta ingresada no existe!!\n\n") //Definimos el mensaje de cuenta inexistente
#define messageIdCardNotExist printf("\nEl N. de cédula ingresado no se ha registrado.\n\n") //Definimos el mensaje de idCard inexistente


//variables globales
int key;
char idUser[10];
char nameUser[20];
char emailUser[30];
char passUser[10];
int account;
int balance;
int state;

int countAskForAmount=0;
int amount1, amount2;
int withdrawAmount=0;
int transferAmount=0;
int destAccountNumber=0;


char emailAdmin[15];
char passAdmin[9];


struct User
{
    char idUser[10];
	char nameUser[20];
	char emailUser[30];
	char passUser[10];
	int account;
	int balance;
	int status;
};


struct User user[10];
int countUser=0;
int poss;
int possDestAccount;
char emailAdminInput[15];
char passAdminInput[9];

void showStarMenu();
void loadAdminData();
void createUser();
void loginUser();
void loginAdmin();
void messageInvalidKey();
void receiveOnlyNumbers(char receivedString[],int minDigits, int maxDigits);
void askForIdCard();
void askForName();
void askForEmail();
int validateEmailFormat();
void askForPass();
void requestNewUserData();
int myStrcmp(char *s1, char *s2);
int mystrInt(char* charNumbers);
int myStrlen(char *cadena);
void myStrncpy(char *dest, char *src);
int generateAccountNumber();
void saveUserData();
int searchEmail();
int validateUserPass();
void showUserMenu();
int askForAmount();
void validateAmount();
void validateAmount2(int amount);
void withdraw();
int validateBalance(int amount);
void gotoUserMenu();
void deposit();
void transfer();
void askForDestinationAccountNumber();
int searchAccount();
void subtractBalance(int amount);
void showUserDetails();
void askForPassAdmin();
void askEmailAdmin();
void messageLimitExceeded();
void showAdminMenu();
void listUsers();
void showAllUsers();
void showUserData();
void enableDisable();


int main() {
	
	setlocale(LC_ALL, "");
	loadAdminData();
	showStarMenu();
}

void messageInvalidKey()
{
	printf("El valor ingresado no corresponde a una opción valida\n\n");
	printf("\n\nOprima la tecla Enter para seleccionar una opción valida\n\n");
	while(key=getch())
	{
		if(key==13)
		{
			showStarMenu();
		}
	}
}

void showStarMenu()
{
	int option;
	int optionExit;
	
	system("cls");
	printf("SISTEMA BANCARIO - PANTALLA INICIAL\n\n");
	
	printf("1. CREAR USUARIO\n\n");
	printf("2. INGRESAR USUARIO\n\n");
	printf("3. INGRESAR ADMINISTRADOR\n\n");
	
	printf("Selecciona una de las opciones.\n\n");
	scanf("%d", &option);
	fflush( stdin );
	printf("\n");
		
	switch(option)
	{
		case 1:
			createUser();
			break;
		case 2:
			loginUser();
			break;
		case 3:
			loginAdmin();
			break;
		default:
			messageInvalidKey();
			showStarMenu();
			break;
	}
	
}


void loadAdminData()
{
	myStrncpy(emailAdmin, "admin@wposs.com");
	myStrncpy(passAdmin, "Admin123*");
	
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
	printf("N. de Identificación: ");
	receiveOnlyNumbers(idUser, 10, 10);
	
}



void askForName()
{
	printf("\n\nNombres: ");
	gets(nameUser);
	printf("\n");
	while(myStrlen(nameUser)<5)
	{
		printf("El nombre ingresado no es valido, por favor ingrese su nombre completo.");
		askForName();
	}
}

void askForEmail()
{
	printf("Ingresa Correo: ");
	gets(emailUser);
	
}

int validateEmailFormat()
{
	int i=0;
	int countAtSign=0;
	int countDot=0;
	int countCharAtSign=0;
	int countCharDot1=0;
	int countCharDot2=0;
	while(emailUser[i]!='\0')
	{
		//muestra mensaje cuando encuentra un espacio
		if(emailUser[i]==' ')
		{
			messageInvalidEmail;
			return 1;
		}
		
		
		if(emailUser[i]=='@')
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
		
		if(emailUser[i] == '.')
		{ 	
		
			//muestra mensaje si se escriben 2 puntos seguidos o si se escribe un @ antes de 1 punto
			if(emailUser[i-1] == '.' || emailUser[i-1] == '@')
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
		
	if(countDot==1)
	{
		if(countCharDot1<3)
		{
			messageInvalidEmail;
			return 1;
		}
	}
	else
	{
		if(countCharDot1<3 || countCharDot2<2)
		{
			messageInvalidEmail;
			return 1;
		}
	}
	
	return 0;
}

void askForPass()
{
	int i=0;
	char character;
	
	printf("\nClave(minimo de 8 caracteres alfanumericos - max. 10): ");
	
	while(character = getch())
	{
		if(character == 13)
		{
			if(i>=8)
			{
				passUser[i] = '\0';
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
					passUser[i] = character;
					i++;
				}
			}
		
	}
	
	
}



void requestNewUserData()
{
	askForIdCard();
	askForName();
	askForEmail();
	while(validateEmailFormat()== 1)
	{
		askForEmail();
	}
	askForPass();
	
}

int generateAccountNumber()
{
	int numberRandom;
	int start=time(NULL)*1000000;
	srand(time(NULL));
	numberRandom=rand()%1000000000+9999999999;
	while(numberRandom<0)
	{
		numberRandom=numberRandom+(numberRandom*2);
	}
	
	return numberRandom;
	
}

void saveUserData()
{
	
	myStrncpy(user[countUser].idUser, idUser);
	myStrncpy(user[countUser].nameUser, nameUser);
	myStrncpy(user[countUser].emailUser, emailUser);
	myStrncpy(user[countUser].passUser, passUser);
	user[countUser].account= account;
	user[countUser].balance= 1000000;
	user[countUser].status= 1;//1. HABILITADO  0. INHABILITADO
	countUser++;
	
}

void createUser()
{
	system("cls");
	printf("SISTEMA BANCARIO - CREAR USUARIO\n\n");
	requestNewUserData();
	account= generateAccountNumber();
	saveUserData();
	printf("\n\n¡¡REGISTRO EXITOSO!!\n\n");
	printf("su número de cuenta es: %d.\n\n", account);
	printf("Recuerde que cuenta con un monto inicial de $1.000.000\n\n");
	printf("\n\nOprima la tecla enter para ingresar con sus nuevas credenciales.\n\n");
		
	while(key=getch())
	{
		if(key==13)
		{
			showStarMenu();
		}
	}

	
}

int searchEmail()
{
	int i=0;
	int result;
	int countFound=0;
	if(countUser==0)
	{
		messageEmailNotExist;
		return 1;
	}
	
	while(i<countUser)
	{
		result= myStrcmp(user[i].emailUser, emailUser);
		if(result==0)
		{
			poss=i;
			countFound++;
			break;
		}
		else
		{
			i++;
		}
	}
	
	
	
	if(countFound==0)
	{
		messageEmailNotExist;
		return 1;
	}
	
	return 0;

}

int validateUserPass()
{
	if(myStrcmp(user[poss].passUser, passUser)!=0)
	{
		messageIncorrectPassword;
		return 1;
	}
	
	return 0;
}



void loginUser()
{
	system("cls");
	printf("SISTEMA BANCARIO - INGRESAR USUARIO\n\n");
	
	askForEmail();
	while(validateEmailFormat()== 1)
	{
		askForEmail();
	}
	
	if(searchEmail()==0)
	{
		if(user[poss].status==1)
		{
			askForPass();
		}
		else
		{
			printf("¡¡El usuario no esta habilitado, comuniquese con el admnistrador!!");
			showStarMenu();
		}
	}
	else
	{
		printf("\n\nOprima la tecla enter para crear un nuevo usuario\n\n");
		while(key=getch())
		{
			if(key==13)
			{
				createUser();
			}
		}
		
	}
	
	while(validateUserPass()!=0)
	{
		askForPass();
	}
	
	showUserMenu();
	
	
	
	
	
}

void showUserMenu()
{
	int option;
	int optionExit;
	
	system("cls");
	printf("SISTEMA BANCARIO - MENÚ DE USUARIO\n\n");
	
	showUserDetails();
	
	printf("1. RETIRAR\n\n");
	printf("2. DEPOSITAR\n\n");
	printf("3. TRANSFERIR\n\n");
	printf("4. SALIR\n\n");
	
	printf("Selecciona una de las opciones.\n\n");
	scanf("%d", &option);
	fflush( stdin );
	printf("\n");
		
	switch(option)
	{
		case 1:
			if(user[poss].balance==0)
			{
				printf("No puede acceder a esta opción, debido a que no cuenta con saldo, debe realizar un deposito\n\n");
				sleep(5);
				showUserMenu();
			}
			else
			{
				withdraw();
			}
			
			break;
		case 2:
			deposit();
			break;
		case 3:
			if(user[poss].balance==0)
			{
				printf("No puede acceder a esta opción, debido a que no cuenta con saldo, debe realizar un deposito\n\n");
				sleep(5);
				showUserMenu();
			}
			else
			{
				transfer();
			}
			break;
		case 4:
			printf("Seguro que desea salir? \n\n");
			printf("1. Si\n");
			printf("2. No\n\n");
			scanf("%d", &optionExit);
			fflush( stdin );
			printf("\n");
				
			switch(optionExit)
			{
				case 1: 
					showStarMenu();
					break;
				case 2: 
					showUserMenu();
					break;
				default:
					messageInvalidKey();
					showUserMenu();
					break;
							
			}
			break;
			
		default:
			messageInvalidKey();
			showUserMenu();
			break;
	}
}

void showUserDetails()
{

	printf("Hola %s\n\n", user[poss].nameUser);
	printf("Su número de cuenta es: %d\n\n", user[poss].account);
	printf("Saldo actual: %d\n\n", user[poss].balance);
	
}

void askForDestinationAccountNumber()
{
	char charDestAccountNumber[10];
	
	printf("\n\nIngresa el número de cuenta (10 digitos): \n\n");
	receiveOnlyNumbers(charDestAccountNumber,10, 10);
	destAccountNumber=mystrInt(charDestAccountNumber);
	
}

int searchAccount()
{
	int i=0;
	int result;
	int countFound=0;
	
	while(i<countUser)
	{
		if(user[i].account==destAccountNumber)
		{
			possDestAccount=i;
			countFound++;
			break;
		}
		
		i++;
	}
	
	if(countFound==0)
	{
		messageAccountNotExist;
		return 1;
	}
	
	return 0;
}

void transfer()
{
	system("cls");
	printf("SISTEMA BANCARIO - TRANSFERENCIAS\n\n");
	
	validateAmount();
	transferAmount=amount1;
	if(validateBalance(transferAmount)==0)
	{
		askForDestinationAccountNumber();
		while(searchAccount()!=0)
		{
			printf("\nPor favor ingrese un número de cuenta existente.");
			askForDestinationAccountNumber();
		}
		
		subtractBalance(transferAmount);
		balance= user[possDestAccount].balance+transferAmount;
		user[possDestAccount].balance= balance;
		printf("\n\n¡¡Transferencia por valor de %d realizada con exito a la cuenta #%d.!!\n\n", transferAmount,destAccountNumber);
		printf("Su saldo actual es de: $%d.", user[poss].balance);
		gotoUserMenu();
		
	}
	else
	{
		printf("\n\nLo sentimos, No cuenta con saldo suficiente para realizar este pago.\n\n");
		printf("Su saldo actual es: $%d\n\n", user[poss].balance);
		gotoUserMenu();
		
		
	}
	
}

void deposit()
{
	system("cls");
	printf("SISTEMA BANCARIO - DEPÓSITOS\n\n");
	
	validateAmount();
	balance= user[poss].balance+amount1;
	user[poss].balance= balance;
	printf("\n\n¡¡Depósito exitoso.\n\n!!");
	printf("Su saldo actual es de: $%d.", user[poss].balance);
	gotoUserMenu();
}

int askForAmount()
{
	int amount=0;
	
	char charAmount[8];
	
	if(countAskForAmount==0)
	{
		printf("\n\nIngresa el monto, recuerda que se acepta desde $1000 en adelante: \n\n");
	}
	else
	{
		printf("\n\nEscribe nuevamente el monto para confirmar: \n\n");
	}
	
	receiveOnlyNumbers(charAmount,4, 8);
	
	amount=mystrInt(charAmount);
	return amount;
	
}


void validateAmount()
{	
	
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
				break;
			}
		}
	}	
	
	countAskForAmount=0;
	
	
}

void validateAmount2(int amount)
{
	while(amount<1000)
	{
		
		printf("\n\nNo se aceptan montos menores a $1000");
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

int validateBalance(int amount)
{
	if(user[poss].balance<amount)
	{
		return 1;
	}
	
	return 0;
	
}

void subtractBalance(int amount)
{
	user[poss].balance=user[poss].balance-amount;
}

void gotoUserMenu()
{
	printf("\n\nOprima la tecla enter para ir al menú de usuario\n\n");
	while(key=getch())
	{
		if(key==13)
		{
			showUserMenu();
						
		}
	}
}


void withdraw()
{
	system("cls");
	printf("SISTEMA BANCARIO - RETIROS\n\n");
	
	validateAmount();
	withdrawAmount=amount1;
	if(validateBalance(withdrawAmount)==0)
	{
		subtractBalance(withdrawAmount);
		printf("\n\n¡¡RETIRO REALIZADO CON EXITO!!\n\n");
		printf("Su saldo actual es de: $%d.", user[poss].balance);
		gotoUserMenu();
		
	}
	else
	{
		printf("\n\nLo sentimos, No cuenta con saldo suficiente para realizar este pago.\n\n");
		printf("Su saldo actual es: $%d\n\n", user[poss].balance);
		gotoUserMenu();
		
		
	}
	
}

void askEmailAdmin()
{
	printf("Ingresa Correo de Administrador: ");
	gets(emailAdminInput);
}

void askForPassAdmin()
{
	int i=0;
	char character;
	
	printf("\nClave de Admin: ");
	
	while(character = getch())
	{
		if(character == 13)
		{
			if(i>=9)
			{
				passAdminInput[i] = '\0';
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
				if(i<9)
				{
					printf("*");
					passAdminInput[i] = character;
					i++;
				}
			}
		
	}
	
	
}

void messageLimitExceeded()
{
	printf("\nHa excedido el limite de intentos para ingresar como usuario administrador\n\n");
	printf("Vuelva a intentarlo despues, por ahora lo enviaremos de nuevo al menú de inicio\n\n");
	sleep(6);
	showStarMenu();
}

void showAllUsers()
{
	
	int s=0;
	int aux;
	char charStatus[12];
	
	while(s<countUser)
	{
		aux = s;
		if(user[s].status==1)
		{
			myStrncpy(charStatus, "habilitado");
		
		}
		else
		{
			myStrncpy(charStatus, "inhabilitado");
		}
		s = aux;
		printf("%d.  %s      %s      %d      %d      %s\n\n",s+1, user[s].nameUser, user[s].emailUser, user[s].account, user[s].balance, charStatus );
	
		s++;
	}
}

void listUsers()
{
	
	system("cls");
	printf("SISTEMA BANCARIO - LISTA DE USUARIOS\n\n");
	
	if(countUser==0)
	{
		printf("No hay usuarios creados todavia.");
		sleep(5);
		showAdminMenu();
	}
	else
	{
		printf("     USUARIO           CORREO               # DE CUENTA       SALDO      ESTADO\n\n");
		showAllUsers();
		printf("Para habilitar o deshabilitar un usuario, debe escribir su número de cuenta.\n\n");
		askForDestinationAccountNumber();
		while(searchAccount()!=0)
		{
			askForDestinationAccountNumber();
		}
		enableDisable();
	}
	
}


void showUserData()
{
	printf("Usuario: %s\n\n",user[possDestAccount].nameUser);
	printf("Correo: %s\n\n",user[possDestAccount].emailUser);
	printf("N. de Cuenta: %d\n\n",user[possDestAccount].account);
	printf("Saldo: %d\n\n",user[possDestAccount].balance);
	
}

void enableDisable()
{
	system("cls");
	printf("SISTEMA BANCARIO - CAMBIAR ESTADO DE USUARIO\n\n");
	showUserData();
	
	if(user[possDestAccount].status==0)
	{
		printf("Este usuario esta inhabilitado, oprima la 'e' para habilitar.");
		while(key=getch())
		{
			if(key==101)
			{
				user[possDestAccount].status=1;
				printf("\n\nEl usuario ha sido habilitado.\n\n");
				break;
			}
		}
	}
	else
	{
		printf("Este usuario esta habilitado, oprima la 'd' para inhabilitar.\n\n");
		while(key=getch())
		{
			if(key==100)
			{
				user[possDestAccount].status=0;
				printf("\n\nEl usuario ha sido inhabilitado.\n\n");
				break;
			}
		}
	}
	
	printf("Oprima la tecla enter para volver al menú de administrador.\n\n");
		while(key=getch())
		{
			if(key==13)
			{
				showAdminMenu();
			}
		}
	
	
	
}

void showAdminMenu()
{
	
	int option;
	int optionExit;
	
	system("cls");
	printf("SISTEMA BANCARIO - MENÚ DE USUARIO ADMINISTRADOR\n\n");
	
	printf("1.LISTAR USUARIOS\n\n");
	printf("2. SALIR\n\n");
	
	printf("Selecciona una de las opciones.\n\n");
	scanf("%d", &option);
	fflush( stdin );
	printf("\n");
		
	switch(option)
	{
		case 1:
			listUsers();
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
					showStarMenu();
					break;
				case 2: 
					showAdminMenu();
					break;
				default:
					messageInvalidKey();
					showAdminMenu();
					break;
							
			}
			break;
		default:
			messageInvalidKey();
			showAdminMenu();
			break;
	}
	
	
}

void loginAdmin()
{	
	system("cls");
	printf("SISTEMA BANCARIO - INGRESO DE ADMINISTRADOR\n\n");
	
	askEmailAdmin();
	int i=0;
	
	while(myStrcmp(emailAdmin,emailAdminInput)!=0)
	{
		printf("\n\nEl correo ingresado no corresponde al usuario Administrador\n\n");
		askEmailAdmin();
		if(i==1)
		{
			messageLimitExceeded();
			break;
			
		}
		
		i++;
		
	}
	
	askForPassAdmin();
	while(myStrcmp(passAdmin, passAdminInput)!=0)
	{
		printf("\n\nLa contraseña ingresada no es valida para el usuario Administrador\n\n");
		askForPassAdmin();
		
		if(i==1)
		{
			messageLimitExceeded();
			break;
			
		}
		i++;
	}
	
	showAdminMenu();
	
	
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
		case 7: 
			countbase= 1000000;
			break;
		case 8: 
			countbase= 10000000;
			break;
		case 9: 
			countbase= 100000000;
			break;
		case 10: 
			countbase= 1000000000;
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

