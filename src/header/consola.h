#ifndef CONSOLA_H_INCLUDED
#define CONSOLA_H_INCLUDED

#include <regex.h>
#include "cmd_no_exec.h"
#include "pipes.h"



/*
*
*   Incluye las funciones de la consola, incluyendo parser de comando
*   pseudo-compilador de instrucciones, y pseudo-procesador de instrucciones.
*   Utiliza un modelo similar a una maquina virtual, los comandos se compilan
*   a un formato de instruccion (struct), y luego son ejecutadas.
*   Utiliza Regex para el parser del comando.
*/



// Descripcion: arroja el error dependiendo del codigo de error
void errorCode(int codigo){
    printf("Error (%#06x): ", codigo);

    switch(codigo){
        default: printf("Error desconocido."); break;
        case ERR_ARCHIVO_NO_EXISTE: printf("El archivo no existe. En linux, los nombres de archivos son case-sensitive."); break;
        case ERR_LECTURA_ARCHIVO: printf("Error al leer el archivo. Asegurarse que el archivo tenga el formato de matriz correcto."); break;
        case MATRIZ_INCORRECTA: printf("Se ha seleccionado una matriz incorrecta."); break;
        case MATRIZ_VACIA: printf("No se puede trabajar con la matriz porque esta vacia (dimensiones 0x0)."); break;
        case INSTRUCCION_DESCONOCIDA: printf("Instruccion desconocida o error de sintaxis."); break;
        case OPERACION_MATRIZ_SIN_EXITO: printf("La operacion con matrices ha arrojado una matriz vacia. En el caso de multiplicacion de dos matrices de dimensiones AxB y NxM, debe cumplirse que B=N. Las sumas y restas deben tener operandos (matrices) de igual dimension."); break;
    }
    printf("\n");
}


// Descripcion: Procedimiento que toma una string con un comando, y retorna la instruccion deseada
// Argumentos:
//				string con el comando
//				instruccion (salida por referencia)
void leerComando(char* comando, instruccion* out){

    char comandoLimpio[512];

	// Limpiar el comando
	limpiarTextoComando(comandoLimpio, comando);

    regex_t regex;                  // Crear regex
    size_t     nmatch = 4;          // Cantidad de grupos que se quieren capturar (substrings)
    regmatch_t pmatch[nmatch];      // Crear el arreglo de estructuras para las capturas
    char* patron;                   // Patron regex para buscar

    int i = 0;                      // Comprueba el regex con todos los opcodes

    flag_t salir_flag = FALSE;           // Un flag que determina cuando salir del ciclo while
    flag_t valorNumerico_flag = FALSE;   // Un flag que indica si el argumento es un valor numerico (1=numerico, 0=matriz)

    // Aca se almacenan todas las cosas leidas temporalmente
    char letraMatriz0;
    char letraMatriz1;
    char letraMatriz2;
    int numerico;
    char str[512] = "";

    // Parser
    while(1){

        switch(i){
            default:
                salir_flag = TRUE;      // Salir en caso de no haber encontrado ninguna instruccion compatible
            break;

            // Para cada caso, ejecutar el Regex, y descomponer los resultados para asignarselos
            // a los argumentos y otros campos de la instruccion
            case NOP:
                patron = "^\\s*$";
                if((regcomp(&regex, patron, 0) != 1) && regexec(&regex, comandoLimpio, nmatch, pmatch, 0) == 0){
                    salir_flag = TRUE;
                }
            break;

            case EXIT_INSTR:
                patron = "^\\s*EXIT\\s*$";
                if((regcomp(&regex, patron, 0) != 1) && regexec(&regex, comandoLimpio, nmatch, pmatch, 0) == 0){
                    salir_flag = TRUE;
                }
            break;

            case LOAD:
                patron = "^\\s*LOAD\\s\\+\\([A-Z]\\)\\s\\+\"\\(.\\+\\)\"\\s*$";
                if((regcomp(&regex, patron, 0) != 1) && regexec(&regex, comandoLimpio, nmatch, pmatch, 0) == 0){

                    letraMatriz0 = comandoLimpio[pmatch[1].rm_so];    // Obtener el char al inicio del grupo
                    copiarString(str, comando, pmatch[2].rm_so, pmatch[2].rm_eo);
                    salir_flag = TRUE;
                }
            break;
            case SAVE:
                patron = "^\\s*SAVE\\s\\+\\([A-Z]\\)\\s\\+\"\\(.\\+\\)\"\\s*$";
                if((regcomp(&regex, patron, 0) != 1) && regexec(&regex, comandoLimpio, nmatch, pmatch, 0) == 0){
                    letraMatriz0 = comandoLimpio[pmatch[1].rm_so];
                    copiarString(str, comando, pmatch[2].rm_so, pmatch[2].rm_eo);
                    salir_flag = TRUE;
                }
            break;
            case PRINT:
                patron = "^\\s*PRINT\\s\\+\\([A-Z]\\)\\s*$";
                if((regcomp(&regex, patron, 0) != 1) && regexec(&regex, comandoLimpio, nmatch, pmatch, 0) == 0){

                    letraMatriz0 = comandoLimpio[pmatch[1].rm_so];

                    salir_flag = TRUE;
                }
            break;
            case CLEAR:
                patron = "^\\s*CLEAR\\s\\+\\([A-Z]\\)\\s*$";
                if((regcomp(&regex, patron, 0) != 1) && regexec(&regex, comandoLimpio, nmatch, pmatch, 0) == 0){

                    letraMatriz0 = comandoLimpio[pmatch[1].rm_so];

                    salir_flag = TRUE;
                }
            break;
            case IGUAL:
                patron = "^\\s*\\([A-Z]\\)\\s*=\\s*\\([A-Z]\\)\\s*$";
                if((regcomp(&regex, patron, 0) != 1) && regexec(&regex, comandoLimpio, nmatch, pmatch, 0) == 0){

                    letraMatriz0 = comandoLimpio[pmatch[1].rm_so];
                    letraMatriz1 = comandoLimpio[pmatch[2].rm_so];

                    salir_flag = TRUE;
                }
            break;

            case SUMA:
                patron = "^\\s*\\([A-Z]\\)\\s*=\\s*\\([A-Z]\\)\\s*+\\s*\\([A-Z]\\)\\s*$";
                if((regcomp(&regex, patron, 0) != 1) && regexec(&regex, comandoLimpio, nmatch, pmatch, 0) == 0){
                    letraMatriz0 = comandoLimpio[pmatch[1].rm_so];
                    letraMatriz1 = comandoLimpio[pmatch[2].rm_so];
                    letraMatriz2 = comandoLimpio[pmatch[3].rm_so];

                    salir_flag = TRUE;
                }
            break;
            case RESTA:
                patron = "^\\s*\\([A-Z]\\)\\s*=\\s*\\([A-Z]\\)\\s*-\\s*\\([A-Z]\\)\\s*$";
                if((regcomp(&regex, patron, 0) != 1) && regexec(&regex, comandoLimpio, nmatch, pmatch, 0) == 0){
                    letraMatriz0 = comandoLimpio[pmatch[1].rm_so];
                    letraMatriz1 = comandoLimpio[pmatch[2].rm_so];
                    letraMatriz2 = comandoLimpio[pmatch[3].rm_so];

                    salir_flag = TRUE;
                }
            break;
            case MULT:
                patron = "^\\s*\\([A-Z]\\)\\s*=\\s*\\([A-Z]\\)\\s*\\*\\s*\\([A-Z]\\)\\s*$";
                if((regcomp(&regex, patron, 0) != 1) && regexec(&regex, comandoLimpio, nmatch, pmatch, 0) == 0){
                    letraMatriz0 = comandoLimpio[pmatch[1].rm_so];
                    letraMatriz1 = comandoLimpio[pmatch[2].rm_so];
                    letraMatriz2 = comandoLimpio[pmatch[3].rm_so];

                    salir_flag = TRUE;
                }
            break;
            case TRANS:
                patron = "^\\s*\\([A-Z]\\)\\s*=\\s*\\TRANS\\s\\+\\([A-Z]\\)\\s*$";
                if((regcomp(&regex, patron, 0) != 1) && regexec(&regex, comandoLimpio, nmatch, pmatch, 0) == 0){
                    letraMatriz0 = comandoLimpio[pmatch[1].rm_so];
                    letraMatriz1 = comandoLimpio[pmatch[2].rm_so];

                    salir_flag = TRUE;
                }
            break;
            case MULTCONST:
                patron = "^\\s*\\([A-Z]\\)\\s*=\\s*\\([A-Z]\\)\\s*\\*\\s*\\([0-9]\\+\\)\\s*$";
                if((regcomp(&regex, patron, 0) != 1) && regexec(&regex, comandoLimpio, nmatch, pmatch, 0) == 0){
                    letraMatriz0 = comandoLimpio[pmatch[1].rm_so];
                    letraMatriz1 = comandoLimpio[pmatch[2].rm_so];

                    // Leer el numero (constante multiplicativa)
                    char numeroString[64];
                    copiarString(numeroString, comandoLimpio, pmatch[3].rm_so, pmatch[3].rm_eo);
                    numerico = atoi(numeroString);

                    valorNumerico_flag = TRUE;
                    salir_flag = TRUE;
                }
            break;

        } // Switch

        // En caso que se haya detectado que se debe salir, entonces se realiza un break
        if(salir_flag == TRUE){
            out->opcode = i;    // Si llego aca gracias a default, significa que "i" no
                                // corresponde a ninguna instruccion, por lo tanto es instruccion desconocida

            out->arg0 = indiceMatriz(letraMatriz0);
            out->arg1 = indiceMatriz(letraMatriz1);
            out->arg2 = (valorNumerico_flag == TRUE)? numerico : indiceMatriz(letraMatriz2);

            strcpy(out->str, str);
            break;
        }

        i++;
    }

    regfree(&regex);            // Liberar el regex

}





// Descripcion: Ejecuta la instruccion
void ejecutarInstruccion(instruccion* instruccion, matriz* arregloMatrices, int* statusCode){

    int opcode = instruccion->opcode;
    int arg0 = instruccion->arg0;
    int arg1 = instruccion->arg1;
    int arg2 = instruccion->arg2;
    char* str = instruccion->str;

    matriz matrizNula;
    matrizNula.n = 0;
    matrizNula.m = 0;
    matrizNula.matriz = NULL;


    // Leer el opcode de la instruccion, para escoger cual instruccion ejecutar
	switch(opcode){

        default:
			*statusCode = INSTRUCCION_DESCONOCIDA;
		break;

        /*
        *
        *   COMANDOS SIN EXEC
        */
        case NOP:
            break;

		case LOAD:
            load(str, arg0, arregloMatrices, statusCode);

		break;

		case SAVE:
            save(str, arg0, arregloMatrices, statusCode);

		break;

		case PRINT:
            print(&arregloMatrices[arg0], statusCode);

		break;

		case CLEAR:
            clearMatriz(&arregloMatrices[arg0]);
		break;

		case IGUAL:
            igualar(&arregloMatrices[arg0], &arregloMatrices[arg1]);
		break;

		case EXIT_INSTR:
            *statusCode = EXIT;
		break;

        /*
        *
        *   COMANDOS CON EXEC
        */


		case SUMA:
            abrirProceso("execs/suma", &arregloMatrices[arg0], &arregloMatrices[arg1], &arregloMatrices[arg2], 0, statusCode);

		break;
		case RESTA:
            abrirProceso("execs/resta", &arregloMatrices[arg0], &arregloMatrices[arg1], &arregloMatrices[arg2], 0, statusCode);

		break;
		case MULT:
            abrirProceso("execs/mult", &arregloMatrices[arg0], &arregloMatrices[arg1], &arregloMatrices[arg2], 0, statusCode);

		break;
		case TRANS:
            // No tiene segundo operador matriz
            abrirProceso("execs/trans", &arregloMatrices[arg0], &arregloMatrices[arg1], &matrizNula, 0, statusCode);

		break;
		case MULTCONST:
            // No tiene segundo operador matriz
            abrirProceso("execs/multconstante", &arregloMatrices[arg0], &arregloMatrices[arg1], &matrizNula, arg2, statusCode);

		break;


	}


	if(*statusCode != OK && *statusCode != EXIT){
        errorCode(*statusCode);
        *statusCode = OK;
    }


}


#endif // CONSOLA_H_INCLUDED
