#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

#include <ctype.h>
#include <string.h>
#include "const.h"
#include "enum.h"
#include <unistd.h>



// Descripcion: Limpia un texto. Cambia todas las letras a mayusculas, y elimina el salto de linea al final
void limpiarTextoComando(char* destino, char* fuente){
	int length = strlen(fuente);
	int i;

	// Remover el salto de linea al final del fgets
	// Y cambiar cada caracter a mayuscula
	for(i=0; i<length; i++){
		if(fuente[i] == '\n'){
			destino[i] = '\0';
		} else {
			destino[i] = toupper(fuente[i]);
		}
	}
}

// Descripcion: retorna el indice de la matriz en el arreglo, usando la letra para identificarla
int indiceMatriz(char letra){
    int i;
    for(i=0; i<MAX_MATRICES; i++){
        if(matrizEnum[i] == letra){
            return i;
        }
    }
    return -1;
}


// Descripcion: reserva memoria para una matriz NxM y retorna el puntero a esa memoria
int** crearMatriz(int n, int m){

    int** mat;

    mat = (int **) malloc(n*sizeof(int *));

    int i;
    for(i=0;i<n;i++)
        mat[i] = (int *) malloc(m*sizeof(int));

    return mat;
}


// Descripcion: libera la memoria de una matriz
void liberarMemoriaMatriz(int** ptrMatriz, int n){
    int i;
    for(i = 0; i < n; i++){
        free(ptrMatriz[i]);
    }
    free(ptrMatriz);
}


// Descripcion: Clona una matriz
matriz clonarMatriz(matriz* mat){
    matriz resultado;
    resultado.n = mat->n;
    resultado.m = mat->m;
    resultado.matriz = crearMatriz(resultado.n, resultado.m);
    int i,j;
    for(i=0; i<mat->n; i++){
        for(j=0; j<mat->m; j++){
            resultado.matriz[i][j] = mat->matriz[i][j];
        }
    }
    return resultado;
}



// Descripcion: Mostrar matriz por pantalla (es llamada por el comando ejecutable desde consola
// y por otras funciones para debug del codigo)
void imprimirMatriz(matriz* mat){
    int i,j;
    for(i=0; i<mat->n; i++){
        for(j=0; j<mat->m; j++){
            printf("%d ", mat->matriz[i][j]);
        }
        printf("\n");
    }
}



// Descripcion: Copia strings desde un indice hasta otro
void copiarString(char* destino, char* fuente, int indice1, int indice2){
    int i;
    int j = 0;
    for(i=indice1; i<indice2; i++){
        destino[j] = fuente[i];
        j++;
    }
}



#endif // LIB_H_INCLUDED
