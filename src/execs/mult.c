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

    // Dimensiones segundo operando
    int n2 = mat2.n;
    int m2 = mat2.m;

    // Inicializar matriz "resultado"
    matriz resultado;


    if(m1 != n2){   // Condicion para multiplicar

        // Guardar datos nulos en la matriz y retornar
        resultado.n = 0;
        resultado.m = 0;
        resultado.matriz = 0;

        // Enviar la matriz vacia
        escribirMatrizEnFd(fd_out, &resultado);
        return 1;
    }


    // Crear la matriz del resultado

    resultado.n = n1;
    resultado.m = m2;
    resultado.matriz = crearMatriz(resultado.n, resultado.m);

    // Realizar la multiplicacion y guardar los datos en el resultado

    int i,j,k;
    for(i=0; i<resultado.n; i++){
        for(j=0; j<resultado.m; j++){

            int suma = 0;
            for(k=0; k<m1; k++){
                suma += mat1.matriz[i][k] * mat2.matriz[k][j];

            }

            resultado.matriz[i][j] = suma;
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
