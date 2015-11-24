#ifndef ENUM_H_INCLUDED
#define ENUM_H_INCLUDED

// Enumeracion para estado de ejecucion
enum statusCode{
    // Ejecucion correcta
	OK,
	// Archivo no existe
	ERR_ARCHIVO_NO_EXISTE,
	// Error generico al leer archivo
	ERR_LECTURA_ARCHIVO,
	// La matriz seleccionada para cierta operacion no es correcta (por ejemplo, es vacia)
    MATRIZ_INCORRECTA,
    // Matriz vacia
    MATRIZ_VACIA,
    // El usuario desea salir del programa
	EXIT,
	// Instruccion desconocida (usuario ingreso comando incorrecto)
	INSTRUCCION_DESCONOCIDA,
	// La operacion no se pudo realizar (por ejemplo sumar dos matrices de distintas dimensiones)
	OPERACION_MATRIZ_SIN_EXITO
};


// Enumeracion para opcode de la instruccion
enum opcodeEnum{
    NOP,
	LOAD,
	SAVE,
	PRINT,
	CLEAR,
	IGUAL,
	EXIT_INSTR,
	SUMA,
	RESTA,
	MULT,
	TRANS,
	MULTCONST
};

// Enumeracion para booleanos
enum boolean{
    FALSE,
    TRUE
};


// Enumeracion o diccionario para identificar las matrices dentro del arreglo. Se hace de esta forma para evitar problemas de compatibilidad con distintas codificaciones
char matrizEnum[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};


#endif // ENUM_H_INCLUDED
