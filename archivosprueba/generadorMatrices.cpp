#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(){
    int i,j;
    FILE* fp;
    char nombreArchivo[16];
    char c;

    // seed
    srand(time(NULL));

    for(c='A'; c<='Z'; c++){

        // Crear el nombre del archivo y abrirlo
        sprintf(nombreArchivo, "%c.txt", c);
        fp = fopen(nombreArchivo, "w");

        // Generar dimensiones
        //int n = rand()%10 + 5;
        //int m = rand()%10 + 5;
        int n = 4;
        int m = 8;

        // Escribir dimensiones
        fprintf(fp, "%d\n", n);
        fprintf(fp, "%d\n", m);

        // Escribir numeros
        for(i=0; i<n; i++){
            if(i!=0){
                fprintf(fp, "\n");
            }
            for(j=0; j<m; j++){
                if(j!=0){
                    fprintf(fp, " %d", rand()%10);
                } else {
                    fprintf(fp, "%d", rand()%10);
                }
                
            } 
        } 
        fclose(fp);
    }
    return 0;
}
