#include <stdio.h>
#include <stdlib.h>
#include "../header/struct.h"
#include "../header/lib.h"
#include "../header/pipes.h"


int main(int argc, char* argv []){

    // Definir las entradas y salidas correctas

    int fd_in = STDIN_FILENO;
    int fd_out = STDOUT_FILENO;

    // Obtener las matrices (operandos)
    // Leyendolos desde el file descriptor (in)

    int constArg;
    leerConstanteFd(fd_in, &constArg);

    matriz mat1;
    leerMatrizDesdeFd(fd_in, &mat1);

    matriz mat2;
    leerMatrizDesdeFd(fd_in, &mat2);


    /*
    *
    *
    *   Comienza la operacion
    *
    *
    */

    // Dimensiones primer operando
    int n1 = mat1.n;
    int m1 = mat1.m;

    // Inicializar matriz "resultado"
    matriz resultado;


    // Crear la matriz del resultado

    resultado.n = m1;
    resultado.m = n1;
    resultado.matriz = crearMatriz(resultado.n, resultado.m);

    // Realizar la transposicion

    int i,j;
    for(i=0; i<resultado.n; i++){
        for(j=0; j<resultado.m; j++){
            resultado.matriz[i][j] = mat1.matriz[j][i];
        }
    }


    /*
    *
    *
    *   Termina la operacion
    *
    *
    */


    // Escribir la matriz resultante en el file descriptor (out)

    escribirMatrizEnFd(fd_out, &resultado);


    return 0;
}
