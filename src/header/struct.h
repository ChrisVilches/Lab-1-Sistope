#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED


// Estructura para almacenar una matriz y sus dimensiones
typedef struct{
	unsigned int n;			// Dimension vertical
	unsigned int m;			// Dimension horizontal
	int** matriz;	// Puntero a la matriz
}matriz;




// Estructura para una instruccion, la cual sera leida por la maquina virtual
typedef struct{
	int opcode;		// Codigo de la instruccion
	int arg0;		// Argumento 0 de la instruccion (destino)
	int arg1;		// Argumento 1 de la instruccion (primer operando)
	int arg2;		// Argumento 2 de la instruccion (segundo operando)
	char str[512];  // Cadena de caracteres, en caso que la instruccion tenga una como argumento
}instruccion;


// Para los flags del compilador
typedef int flag_t;



#endif // STRUCT_H_INCLUDED
