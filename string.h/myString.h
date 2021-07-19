#ifndef MYSTRING_H
#define MYSTRING_H

class myString
{
	int myStrlen(char* cadena);
	
	
	public int myStrlen(char* cadena){
		
		//dimensión de la cadena
		int n;
		
		//definición de caracter final
		const char* final="\0";
		
		n=0;
		
		//se recorre cada posición de la cadena
		while(cadena[n] != final) 
		{
			n++;
		}
		
		return n;
		
		
	}
};

#endif
