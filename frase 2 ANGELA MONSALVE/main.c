#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int longText(char *text);
int totalWords(char *text, int lT);
void fillMatrix(char matrix[][50], char text[], int tW, int lT);
void showMatrix(char matrix[][50], int tW);
void fillArrayLongWords(char *text, int longW[], int lT);
void showlongW(int longW[],int tW);
void showPalindromo(char matrix[][50], int tW, int arrayLongW[]);
void showRowMatrix(int nRow, int arrayLongW[], char matrix[][50]);
void fillmatrixWr(int i, char matrix[][50], char matrixWr[][50], int countT, int arraylongW[]);
void fillFirstRowMatrixWr(int comp, int tW, int matrixWr[tW][tW]);
void showRepeatedWords2(char matrix[][50], int tW, int matrixWr[tW][tW],  int arrayLongW[]);
void showRowMatrixWrNumbers(int nRow, int tW, int matrixWr[tW][tW]);
int count0(int nRow,int nCol, int tW, int matrixWr[tW][tW]);
void showMatrixint( int tW, int matrixWr[tW][tW]);
int myStrcmp3(char matrix[][50], int tW, int matrixCountPos[][tW], int posCurrent, int arraylongW[]);
int CalculateNVowels(char text[], int lT );
int CalculateNConsonants(char text[], int lT );
int totalSpaces(char *text, int lT);
void VowelMaxRepeat(int arrayCountv[], int countVa, int countVe, int countVi, int countVo, int countVu);
void CalculateNRepeatVowels(char text[], int lT );
int myStrcmpArrayPos(char matrix[][50], int tW, int arrayPos[], int posCurrent, int arraylongW[]);

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	
	setlocale(LC_ALL, "");
	
	char text[50];
	int nVowels;
	int nConsonants;
	int nSpaces;

	
	
	printf("Ingrese una frase, no puede superar los 50 caracteres: \n\n");
	
	gets(text);
	int lT= longText(text);
	
	printf("\nEsta frase tiene una longitud de %d \n", lT);
	
	if(lT>50)
	{
		printf("\nLa frase que ingresó no es valida debido a que supera los 50 caracteres\n");	
		printf("\nIngrese otra frase valida: \n");
		gets(text);
		int lT= longText(text);
		printf("\nEsta frase tiene una longitud de %d \n", lT);
		
	}
	
	
	int tW= totalWords(text, lT);
	//se muestra total de palabras en la frase
	printf("\nHay %d  palabras en esta frase\n", tW );
	
	int longW[tW];
	
	
	//se llena y se muestra la longitud de cada palabra en la frase
	fillArrayLongWords(text,longW,lT);
	
	//creamos la matriz 
	char matrix[tW][50];
	
	//creamos la matriz que guarda las palabras repetidas
	char matrixWr2[tW][50];
	int matrixWr[tW][tW];
	
	//llenamos la matriz y mostramos la matriz
	fillMatrix(matrix,text,tW,lT);
	showMatrix(matrix,tW);
	
	//aqui se imprimen las palabras que son palindromos
	printf("\nPalabras Palindromos: \n");
	
	showPalindromo(matrix, tW, longW);
	
	//aqui se imprimen las palabras repetidas
	printf("\nPalabras Repetidas: \n");
	showRepeatedWords2(matrix, tW, matrixWr, longW);
	
	//aqui se imprime la cantidad de vocales
	nVowels=CalculateNVowels(text, lT);
	printf("\n\nHay %d vocales en la frase ingresada. ", nVowels);
	
	//aqui se imprime la cantidad de consonantes
	nConsonants=CalculateNConsonants(text, lT);
	printf("\n\nHay %d consonantes en la frase ingresada. ", nConsonants);
	
	//aqui se imprime la cantidad de espacios en blanco
	nSpaces=totalSpaces(text, lT);
	printf("\n\nHay %d espacios en blanco en la frase ingresada. \n\n", nSpaces);
	
	//aqui se imprime la vocal mas usada
	CalculateNRepeatVowels(text, lT);
	
	
}

int longText(char *text)
{
	//dimensión de la cadena
	int n;
		
	n=0;
	
	//se recorre cada posición de la cadena
	while(text[n] != '\0')
	{
		n++;
	}
	
				
	return n;
}

int totalWords(char *text, int lT)
{
	int i;
	int count=0;
	
	for(i=0; i<lT; i++)
	{
		if(text[i] == ' ')
		{
			if(text[i-1]!= ' ')
			{
				count++;
			}
			
		}
		
	}
	
	
	if(text[i] == 0x00 )
	{
		if(text[i-1]!= ' ')
		{
			count++;
		}
	}
	
	return count;
	
}

int totalSpaces(char *text, int lT)
{
	int i;
	int count=0;
	for(i=0; i<lT; i++)
	{
		if(text[i]== ' ')
		{
			count++;
		}
	}
	
	return count;
	
}

void fillArrayLongWords(char *text, int longW[], int lT)
{
	int i;
	int count=0;
	int tw=0;
	for(i=0; i<lT; i++)
	{
		
		
		if(text[i]== ' ')
		{
			if(text[i-1]!=' ')
			{
				longW[tw]=count;
				tw++;
				count=0;
			}
		} 
		else
		{
			count++;
		}
		
		
		
	}
	
	longW[tw]=count;
	
		
}

void showlongW(int longW[],int tW)
{
	int i;
	for(i=0; i<tW; i++)
	{
		printf("%d, \n", longW[i]);
	}
}

void fillMatrix(char matrix[][50],char text[], int tW, int lT)
{
	int i=0;
	int n=0;
	int x=0;
	
	while(n<lT)
	{
		if(text[n]!=' ')
		{
			matrix[i][x]= text[n];
			x++;
				
		}
			
		else
		{
			if(n>0)
			{
				if(text[n-1]!= ' ')
				{
										
					matrix[i][x]= '\0';
					i++;
					x=0;
					
				}
				
			}
		}
			
		n++;
		if(n==lT)
		{
			matrix[i][x]= '\0';
		}	
	}
		
}
	

void showMatrix(char matrix[][50], int tW)
{
	int i;
	int n=0;
	
	for(i=0; i<tW; i++)
	{
		
		while(matrix[i][n]!='\0' )
		{
			printf("%c", matrix[i][n]);
			n++;
			
		}
		n=0;
		printf("\n");
	}
	
}

void showPalindromo(char matrix[][50], int tW, int arrayLongW[])
{
	int i=0;
	int n=0;
	int lW;
	int countP=0;
	int arrayPosPalindromo[tW];
	int existW;
	
	
	//se recorren las filas de la matriz
	while(i<tW)
	{
		existW=myStrcmpArrayPos(matrix, countP, arrayPosPalindromo, i, arrayLongW);
		
		
				
		if(existW==1)
		{
			n=arrayLongW[i]+1;
				
		}
		else
		{
			//aqui se revisa si la palabra es monosilaba para que no la tenga en cuenta
			if(arrayLongW[i]==1)
			{
				n=arrayLongW[i]+1;
			}
		}
		
		
		lW= arrayLongW[i]-1;
		
		//se recorren las columnas de la matriz
		while(n<arrayLongW[i])
		{
			//se compara letra por letra de la palabra en forma normal e invertida
			if(matrix[i][n]==matrix[i][lW])
			{
				lW--;
				n++;
			}
			else
			{
				n=0;		
				break;
			}
		}
		
		if(n==arrayLongW[i])
		{
			showRowMatrix(i, arrayLongW, matrix);
			arrayPosPalindromo[countP]=i;
			countP++;
			n=0;
			
		}
		
		if(n>arrayLongW[i])
		{
			n=0;
		}
		
		i++;
		
	
	}
	
	if(countP>0)
	{
			printf("Hay %d palabras palíndromo en total.\n", countP);
	}
	else
	{
		printf("No hay ninguna palabra palíndromo en la frase ingresada");
	}

	
}

void showRowMatrix(int nRow, int arrayLongW[], char matrix[][50])
{
	//esta función recorre una fila especifica de la matriz
	
	int n;
	
	printf(". ");
	
	for(n=0; n<arrayLongW[nRow]; n++)
	{
		printf("%c", matrix[nRow][n]);
	}
	
	printf("\n");
	
}

void showRepeatedWords2(char matrix[][50], int tW, int matrixWr[tW][tW],  int arrayLongW[])
{
	int i=0;
	int comp;
	int n=0;
	int x=i+1;
	int countZero;
	int base=0;
	int matrixcountPos[2][tW];
	matrixcountPos[0][0]='2';
	int countW=0;
	int ini;
	int existW;
	
	
	while(x<tW)
	
	{ 
		if(i>0)
		{
			if(x==i+1)
			{
				existW=myStrcmp3(matrix, tW, matrixcountPos, i, arrayLongW);
				
				if(existW==1)
				{
				
					n=arrayLongW[i];
				
				}
			}
			
			
		}
	
	
	
			while(n<arrayLongW[i])
			{
				
				
				if(arrayLongW[i]==arrayLongW[x])
				{
					if(matrix[i][n]!=matrix[x][n])
					{
						comp=1;
						n=arrayLongW[i]+1;
						break;
					}
				
					else
					{
						n++;
					}
					
					//se valida si ya se llegó al final de la palabra con todas las letras iguales
					if(n==arrayLongW[i])
					{
						comp=0;
						n=arrayLongW[i]+1;
						
					
				
					}
					
				}
				
				else
				{
					comp=1;
					n=arrayLongW[i]+1;
					break;
				
				}
				
				
			}
			
			
			
			if(n>arrayLongW[i])
			{
				matrixWr[i][x]=comp;
				
				if(x==tW-1)
				{
					x=tW;
				}
				else
				{
					x++;
				}
				
				
			}
			else 
			{
				
				i++;
				x=i+1;
			}
		
			n=0;
				
			
			
			//aqui se define si se aumenta o no la i, ademas se modifica el valor de la x
		    if(x==tW)
			{
			    ini=i+1;
			
				//debemos poner un contador de 0 o 1 en cada fila de la matrizwr
				countZero=count0(i,ini,tW,matrixWr)+1;
				
				if(countZero>1)
				{
					matrixcountPos[0][countW]=i;
				 	matrixcountPos[1][countW]=countZero;
				 	matrixcountPos[0][countW+1]='2';
					countW++;
					
					if(countZero==tW)
					{
						break;
					}
					
				}
				
				i++;
				x=i+1;
			
			}
			
			
	}
	

	if(countW>0)
	{
		int u=0; 
		int v;
		int posW;
		int countPos;
	
		for(v=0;v<countW; v++)
		{
		
			posW=matrixcountPos[u][v];
			printf("\nSe repite la palabra: \n");
			showRowMatrix(posW,arrayLongW,matrix);
			countPos=matrixcountPos[u+1][v];
			printf("%d veces. ", countPos);
		}
		
	}
	else
	{
		printf("No hay palabras repetidas");
	}
	
	
}


void fillmatrixWr(int i, char matrixWr[][50], char matrix[][50], int countT, int arraylongW[])
{
	int n;
	
	for(n=0; n<arraylongW[i]; n++)
	{
		matrixWr[countT][n]=matrix[i][n];
	}
	
	matrixWr[countT][n]='\0';
	
}

void fillFirstRowMatrixWr(int comp, int tW, int matrixWr[tW][tW])
{

	
	int i=0;
	int n;
	
	for(n=0; n<tW; n++)
	{
		matrixWr[i][n]=comp;
	}
	
	
}

int myStrcmp3(char matrix[][50], int tW, int matrixCountPos[][tW], int posCurrent, int arraylongW[]){
	
	int i=0;
 	int n=0;
 	int x=0;
 	int existW=0;
 	int posWr;
 	
	
	
		while (n<tW)
		{
			
			
			if(existW==1)
			{
				break;
			}
			
			posWr=matrixCountPos[i][n];
			
			if(posWr=='2')
			{
				break;
			}
			
			
			while(x<arraylongW[posCurrent])
			{
				if(arraylongW[posCurrent]==arraylongW[posWr])
				{
					if(matrix[posCurrent][n]==matrix[posWr][n])
					{
						x++;
					}
					else
					{
						n++;
						x=0;
						break;
					}
				
					
				}
				
				else
				{
					n++;
					x=0;
					break;
				}
				
				if(x==arraylongW[posCurrent])
				{
					existW++;
					n++;
					x=arraylongW[posCurrent];
				}
			}
			
				
		}
		
	return existW;
	
}

int myStrcmpArrayPos(char matrix[][50], int countP, int arrayPos[], int posCurrent, int arraylongW[]){
	
	int i=0;
 	int x=0;
 	int existW=0;
 	int pos;
 	
	
	
		while (i<countP)
		{
			
			
			if(existW==1)
			{
				break;
			}
			
			pos=arrayPos[i];
				
			while(x<arraylongW[posCurrent])
			{
				if(arraylongW[posCurrent]==arraylongW[pos])
				{
					if(matrix[posCurrent][x]==matrix[pos][x])
					{
						x++;
					}
					else
					{
						i++;
						x=0;
						break;
					}
				
					
				}
				
				else
				{
					i++;
					x=0;
					break;
				}
				
				if(x==arraylongW[posCurrent])
				{
					existW++;
					i++;
				}
			}
			
				
		}
		
	return existW;
	
}


void showRowMatrixWrNumbers(int nRow, int tW, int matrixWr[tW][tW])
{
	//esta función recorre una fila especifica de la matriz
	
	int n;
	
	printf(". ");
	
	for(n=0; n<tW; n++)
	{
			
		printf("%d", matrixWr[nRow][n]);
	}
	
	printf("\n");
}


int count0(int nRow, int nCol, int tW, int matrixWr[tW][tW])
{
	//esta función recorre una fila especifica de la matriz
	
	int n;
	int count0=0;
	
	for(n=nCol; n<tW; n++)
	{
		if(n==0)
		{
			n++;
		}
		
		if(matrixWr[nRow][n]==0)
		{
			count0++;
		}
		
		
	}
	
	return count0;
	
}

void showMatrixint( int tW, int matrixWr[tW][tW])
{
	int i;
	int n;
	
	for(i=0; i<tW; i++)
	{
		
		for(n=0; n<tW; n++)
		{
			printf("%d ", matrixWr[i][n]);
		}
		
		printf("\n");
		
	}
	
	
	
}

int CalculateNVowels(char text[], int lT )

{
	int i;
	int countV=0;
	
	for(i=0; i<lT; i++)
	{
		if(text[i]=='a' || text[i]=='e' || text[i]=='i' || text[i]=='o' || text[i]=='u' || text[i]=='A' || text[i]=='E' || text[i]=='I' || text[i]=='O' || text[i]=='U' )
		{
			countV++;
		}
	}
	
	return countV;
}

void CalculateNRepeatVowels(char text[], int lT )

{
	int i;
	int arrayCountv[5];
	int countVa=0;
	int countVe=0;
	int countVi=0;
	int countVo=0;
	int countVu=0;

	
	for(i=0; i<lT; i++)
	{
		if(text[i]=='a' || text[i]=='e' || text[i]=='i' || text[i]=='o' || text[i]=='u' || text[i]=='A' || text[i]=='E' || text[i]=='I' || text[i]=='O' || text[i]=='U' )
		{
			if(text[i]=='a' || text[i]=='A')
			{
				countVa++;
			
			}
		
			else
			{
				if(text[i]=='e' || text[i]=='E')
				{
					countVe++;
			
				}
			
				else
				{
					if(text[i]=='i' || text[i]=='I')
					{
						countVi++;
			
					}
					else
					{
						if(text[i]=='o' || text[i]=='O')
						{
							countVo++;
			
						}
						else
						{
							if(text[i]=='u' || text[i]=='U')
							{
								countVu++;
			
							}
						}
					}
				}
			}
		}
		
	}
	
	VowelMaxRepeat(arrayCountv, countVa, countVe, countVi, countVo, countVu);
	
}

void VowelMaxRepeat(int arrayCountv[], int countVa, int countVe, int countVi, int countVo, int countVu )
{
	arrayCountv[0]=countVa;
	arrayCountv[1]=countVe;
	arrayCountv[2]=countVi;
	arrayCountv[3]=countVo;
	arrayCountv[4]=countVu;
	int i=0;
	int n=i+1;
	int posVowelMayor;
	
	while(n<5)
	{
		if(arrayCountv[i]>arrayCountv[n])
		{
			posVowelMayor=i;
			n++;
		}
		else
		{
			posVowelMayor=n;
			i++;
			n=i+1;
		}
	}
	
		
	for(i=0; i<5; i++)
	
	{
		if(arrayCountv[posVowelMayor]==arrayCountv[i])
		{
			switch(i)
			{
				case 0:
			
				{
					printf("La vocal mas usada es: A\n" );
					break;
				}
				case 1:
			
				{
					printf("La vocal mas usada es: E\n" );
					break;
				}	
			
				case 2:
			
				{
					printf("La vocal mas usada es: I\n" );
					break;
				}
			
				case 3:
			
				{
					printf("La vocal mas usada es: O\n" );
					break;
				}		
		
				case 4:
			
				{
					printf("La vocal mas usada es: U\n" );
					break;
				}	
			
			}

		
		}
	}
	
	
}


int CalculateNConsonants(char text[], int lT )
{
	int i;
	int countC=0;
	
	for(i=0; i<lT; i++)
	{
		if(text[i]=='b' || text[i]=='c' || text[i]=='d' || text[i]=='f' || text[i]=='g' || text[i]=='g' || text[i]=='j' || text[i]=='k' || text[i]=='l' || text[i]=='m' || text[i]=='n' || text[i]=='ñ' || text[i]=='p' || text[i]=='q' || text[i]=='r' || text[i]=='s' || text[i]=='t' || text[i]=='v' || text[i]=='w' || text[i]=='x' || text[i]=='y' || text[i]=='z' || text[i]=='B' || text[i]=='C' || text[i]=='D' || text[i]=='F' || text[i]=='G' || text[i]=='H' || text[i]=='J' || text[i]=='K' || text[i]=='L' || text[i]=='M' || text[i]=='N' || text[i]=='Ñ' || text[i]=='P' || text[i]=='Q' || text[i]=='R' || text[i]=='S' || text[i]=='T' || text[i]=='V' || text[i]=='W' || text[i]=='X' || text[i]=='Y' || text[i]=='Z')
		{
			countC++;
		}
	}
	
	return countC;
}




