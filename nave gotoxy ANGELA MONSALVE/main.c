#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include <conio.h>
#include <unistd.h>
#include <pthread.h>



/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int x=15;
int y=11;
int xb,yb;
int xlb, ylb;
int n;


void nave(int x, int y);
void balas(int x, int y);
void limpiarbala(int x, int y);
void limpiarnave(int x, int y);

void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 } 
 
 
int main() {
	
	pthread_t hilo;
	
	
    // instrucciones que tanto el padre como el hijo harán

    nave(x,y);
		
	
	char into[1];
	int t=0;
	int salir=0;
	
	
	
	do
	{
		
		t=getch(); /* Leemos la entrada del teclado */
		
		limpiarnave(x,y);
		
		switch (t)
		{
			

			case 72: /* arriba */
			    
				y--; 
				break;
			case 75:
				
				x--; 
				break; /* izquierda */
			
				
			case 77:
				
				x++; 
				break; /* derecha */
			
			case 80:
				
				y++; 
				break; /* abajo */
				
		    case 32: 
		    
		        nave(x,y);
		    
		    	xb=x+5;
		     	yb=y+1;
		    	ylb=yb;
		    	n=0;
		    	int finbala=xb+30;		    	 	
				while(n<finbala)
				{
					limpiarbala(xlb,ylb);
		    		
		    		balas(xb,yb);
		    		xb=xb+3; 
		    		xlb=xb-3;
		    		n++;
		    		Sleep(3);
				}
				
				limpiarbala(xlb,ylb);
					  			
				xb=xb-4;
		    	yb=yb--;
		    			    	
		    
		    	break;
				
			case 13:
				salir=1;
				
		    	
			 
		}
		
		
		nave(x,y);
		
		
		
	
		
		
	}
	while(salir!=1); /* Mientras no se pulse ESC */
	
	
	
}

void nave(int x, int y)
{
	gotoxy(x,y);  
    printf("CC\n"); 
   	gotoxy(x,y+1);
	printf("IIIII\n"); 
	gotoxy(x,y+2);
	printf("CC\n");   
}

void limpiarnave(int x, int y)
{
	gotoxy(x,y);  
    printf("  \n"); 
   	gotoxy(x,y+1);
	printf("     \n"); 
	gotoxy(x,y+2);
	printf("  \n");  
}

void balas(int x, int y)
{
	gotoxy(x,y);  
    printf("=> "); 
   	
}

void limpiarbala(int x, int y)
{
	gotoxy(x,y);  
    printf("    "); 
}




