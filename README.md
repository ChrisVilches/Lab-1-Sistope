# Lab 1 Sistemas Operativos

## Compilacion

```
make
```

## Ejemplos de uso
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
4. Utiliza fork, dup, y pipes.
5. La lectura y escritura por pipes es binarizada; no envia strings legibles por humanos.

-------

Laboratorio 1 de Sistemas Operativos 2-2015

Felipe Vilches Cespedes, 18.015.608-9

Profesor Fernando Rannou

Ingenieria Informatica, Universidad de Santiago de Chile
