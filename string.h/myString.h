#ifndef MYSTRING_H
#define MYSTRING_H

class myString
{
	int myStrlen(char* cadena);
	
	
	public int myStrlen(char* cadena){
		
		//dimensi�n de la cadena
		int n;
		
		//definici�n de caracter final
		const char* final="\0";
		
		n=0;
		
		//se recorre cada posici�n de la cadena
		while(cadena[n] != final) 
		{
			n++;
		}
		
		return n;
		
		
	}
};

#endif
