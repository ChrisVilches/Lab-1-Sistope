# Lab 1 Sistemas Operativos

## Descripcion del proyecto

Calculadora de matrices. Utiliza fork, pipes y dup. El usuario puede cargar matrices (desde archivos), operar con ellas, guardarlas, etc, por medio de comandos.

El programa ```header/pipes.h``` contiene los procedimientos necesarios y mas importantes de este proyecto, los cuales envian y reciben matrices por pipe, y ejecutan (exec) nuevos procesos, etc.

## Compilacion

```
make
```

## Instrucciones y ejemplos de uso

1. Luego de compilar usando make, entrar a la carpeta bin y ejecutar ./main.
2. Debe colocarse uno o mas archivos de prueba en el mismo directorio que el ejecutable main.
3. Para empezar, cargar una matriz usando el comando "load".


```
a = b + c
b = c - a
h = g * f
g = e * 3
c = trans g
print a
load a "A.txt"
save h "B.txt"
clear b
t = r
exit
```

## Caracteristicas del programa
1. Utiliza regex para la linea de comandos. Los comandos pueden tener mayusculas o minusculas, espacio blanco extra, etc.
2. Tiene un modulo de "compilacion" del comando, el cual crea una estructura de "instruccion".
3. La instruccion es ejecutada por otro modulo, en un estilo similar a una maquina virtual.
4. La lectura y escritura por pipes es binarizada; no envia strings legibles por humanos.

-------

Laboratorio 1 de Sistemas Operativos 2-2015

Felipe Vilches Cespedes, 18.015.608-9

Profesor Fernando Rannou

Ingenieria Informatica, Universidad de Santiago de Chile.
