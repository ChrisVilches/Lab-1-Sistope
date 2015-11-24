#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header/const.h"
#include "header/enum.h"
#include "header/struct.h"
#include "header/lib.h"
#include "header/consola.h"

int main(int argc, char* argv []){

	int statusCode = OK;

	// Inicializar arreglo de matrices. Aca se almacenan todas las matrices. Solo pueden haber 26
	matriz* arregloMatrices = (matriz*) malloc(sizeof(matriz) * MAX_MATRICES);
	if(arregloMatrices == NULL){
		perror("No se pudo crear arreglo de matrices. ");
		exit(0);
	}

	int i;
	// Rellenar las dimensiones con 0 (significa que a la matriz no se le ha asignado memoria,
	// o se le ha borrado con CLEAR)
	for(i=0; i<MAX_MATRICES; i++){
        arregloMatrices[i].n = 0;
        arregloMatrices[i].m = 0;
	}


	// Almacenar la linea leida (comando)
	char comando[512];

	// La instruccion a ejecutar
	instruccion instr;

	// Loop infinito para pedir comandos, hasta que escriba "exit"
	while(1){

        printf("$ ");

		// Leer comando de la entrada estandar
		fgets(comando, sizeof comando, stdin);

		// Obtiene la instruccion a partir del comando
		leerComando(comando, &instr);

		// Ejecutar comando
		ejecutarInstruccion(&instr, arregloMatrices, &statusCode);

		// Si el comando arroja que el usuario quiere salirse, entonces salir
		if(statusCode == EXIT)
			break;

	}


	return 0;
}
