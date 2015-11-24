#ifndef CMD_NO_EXEC_H_INCLUDED
#define CMD_NO_EXEC_H_INCLUDED


// Descripcion: imprime la matriz (comando ejecutable desde la consola)
void print(matriz* mat, int* statusCode){
    if(mat->n == 0 || mat->m == 0){
        *statusCode = MATRIZ_VACIA;
        return;
    }
    imprimirMatriz(mat);
    *statusCode = OK;
}



// Descripcion: libera la memoria usada por una matriz
void clearMatriz(matriz* mat){

    if(mat->m == 0 || mat->n == 0){
        return;
    }

    liberarMemoriaMatriz(mat->matriz, mat->n);
    mat->m = 0;
    mat->n = 0;
}


// Descripcion: iguala dos matrices A = B
void igualar(matriz* A, matriz* B){

    int i, j;

    // Eliminar matriz
    clearMatriz(A);

    // Obtener las nuevas dimensiones
    int n = B->n;
    int m = B->m;

    if(n==0 || m==0) return; // No hay nada que copiar

    A->n = n;
    A->m = m;

    // Malloc la nueva matriz
    A->matriz = crearMatriz(A->n, A->m);

    // Copiar valores
    for(i=0; i<n; i++){
        for(j=0; j<m; j++){
            A->matriz[i][j] = B->matriz[i][j];
        }
    }
}


// Descripcion: guarda una matriz en un archivo de texto
void save(char* nombreArchivo, int cualMatriz, matriz* arregloMatrices, int* statusCode){

    matriz mat = arregloMatrices[cualMatriz];
    if(mat.n == 0 || mat.m == 0){
        *statusCode = MATRIZ_VACIA;
        return;
    }

    FILE* fp = fopen(nombreArchivo, "w");

    fprintf(fp, "%d\n%d\n", mat.n, mat.m);
    int i,j;
    for(i=0; i<mat.n; i++){
        if(i != 0){
            fprintf(fp, "\n");
        }
        for(j=0; j<mat.m; j++){
            if(j != 0){
                fprintf(fp, " %d", mat.matriz[i][j]);
            } else {
                fprintf(fp, "%d", mat.matriz[i][j]);
            }
        }
    }
    fclose(fp);
}


// Descripcion: lee el archivo de texto y rellena la matriz con los datos
void load(char* nombreArchivo, int cualMatriz, matriz* arregloMatrices, int* statusCode){

    FILE* fp = fopen(nombreArchivo, "r");
    if(fp == NULL){
        *statusCode = ERR_ARCHIVO_NO_EXISTE;
        return;
    }
    char buf[512];
    int i;
    int j;

    matriz mat = arregloMatrices[cualMatriz];

    // Liberar la memoria usada por la matriz actualmente

    clearMatriz(&mat);

    // Leer las dimensiones de la matriz

    fgets (buf, sizeof(buf), fp);   // Leer N
    mat.n = atoi(buf);

    fgets (buf, sizeof(buf), fp);   // Leer M
    mat.m = atoi(buf);

    // Reservar memoria para la matriz

    mat.matriz = crearMatriz(mat.n, mat.m);

    // Comenzar a leer los numeros de la matriz

    char* token;

    // Leer todas las filas de la matriz
    for(i=0; i<mat.n; i++){
        // Leer la linea
        fgets (buf, sizeof(buf), fp);

        token = strtok(buf, " "); // Primer strtok
        mat.matriz[i][0] = atoi(token); // Primer numero de la fila

        // Los demas strtok
        for(j=1; j<mat.m; j++){
            token = strtok(NULL, " ");
            mat.matriz[i][j] = atoi(token);
        }
    }
    arregloMatrices[cualMatriz] = mat;
    fclose(fp);
    *statusCode = OK;
}


#endif // CMD_NO_EXEC_H_INCLUDED
