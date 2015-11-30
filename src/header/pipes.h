#ifndef PIPES_H_INCLUDED
#define PIPES_H_INCLUDED

#include <unistd.h>
#include <sys/types.h>
#include "cmd_no_exec.h"

#define LECTURA 0
#define ESCRITURA 1


// Descripcion: Escribir constante al fd
void escribirConstanteFd(int fd, int c){
    write(fd, &c, sizeof(int));
}

// Descripcion: Leer constante desde fd
void leerConstanteFd(int fd, int* c){
    read(fd, c, sizeof(int));
}


// Descripcion: Lee una matriz desde el file descriptor. Sirve para enviar/recibir matrices por pipe.
void leerMatrizDesdeFd(int fd, matriz* out){

    read(fd, &out->n, sizeof(int));
    read(fd, &out->m, sizeof(int));
    out->matriz = crearMatriz(out->n, out->m);

    int i, j;
    for(i=0; i<out->n; i++){
        for(j=0; j<out->m; j++){

            read(fd, &out->matriz[i][j], sizeof(int));

        }
    }
}

// Descripcion: Escribe una matriz al file descriptor. Sirve para enviar/recibir matrices por pipe.
void escribirMatrizEnFd(int fd, matriz* matriz){

    // Escribir las dimensiones

    write(fd, &matriz->n, sizeof(int));

    write(fd, &matriz->m, sizeof(int));

    // Escribir los demas datos
    int i, j;
    for(i=0; i<matriz->n; i++){
        for(j=0; j<matriz->m; j++){
            write(fd, &matriz->matriz[i][j], sizeof(int));
        }
    }
}


// Descripcion: Abre un nuevo proceso (fork, exec) y se comunica con el enviandole la informacion necesaria
// (matrices para trabajar, constante, etc)
void abrirProceso(char* nombreProceso, matriz* arg0, matriz* arg1, matriz* arg2, int arg3, int* statusCode){

    // Preparar los pipes
    int padreAhijo[2];
    int hijoApadre[2];

    pipe(padreAhijo);
    pipe(hijoApadre);

    // Hacer fork
    pid_t pid;
    pid = fork();

    // Manejar el error
    if(pid < 0){
        perror("Hubo un error al hacer fork");
        exit(EXIT_FAILURE);
    }


    if(pid == 0){

        // Proceso hijo

        dup2(padreAhijo[LECTURA], STDIN_FILENO);
        dup2(hijoApadre[ESCRITURA], STDOUT_FILENO);

        close(hijoApadre[LECTURA]);
        close(padreAhijo[ESCRITURA]);
        close(padreAhijo[LECTURA]);
        close(hijoApadre[ESCRITURA]);


        // Exec nuevo proceso
        execl(nombreProceso, "ls","-al", (char*) 0);

        // Manejo error exec
        perror("Error al hacer exec");
        exit(EXIT_FAILURE);
    }

    // Proceso padre
    close(hijoApadre[ESCRITURA]);
    close(padreAhijo[LECTURA]);


    // Pasar todos los posibles argumentos

    // Pasar la constante
    escribirConstanteFd(padreAhijo[ESCRITURA], arg3);

    // Pasar la primera matriz
    escribirMatrizEnFd(padreAhijo[ESCRITURA], arg1);

    // Pasar la segunda matriz
    escribirMatrizEnFd(padreAhijo[ESCRITURA], arg2);

    // La matriz arg0 no se pasa ya que es donde
    // se guardan los resultados

    // Termino la escritura
    close(padreAhijo[ESCRITURA]);

    // Leer resultado
    matriz resultado;
    leerMatrizDesdeFd(hijoApadre[LECTURA], &resultado);

    // A veces los programas pueden enviar matrices
    // vacias, si se ha determinado que no se puede efectuar
    // la operacion
    if(resultado.n != 0 && resultado.m != 0){

        // Pasar el resultado y asignarlo a donde corresponde
        igualar(arg0, &resultado);

        // Limpiar la matriz que se leyo desde el hijo
        // ya que aca dentro hay un espacio del heap reservado
        // y debe liberarse
        clearMatriz(&resultado);

    } else {

        *statusCode = OPERACION_MATRIZ_SIN_EXITO;

    }

    // Termino la lectura
    close(hijoApadre[LECTURA]);

}




#endif // PIPES_H_INCLUDED
