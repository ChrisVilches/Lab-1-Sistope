
DIR_OUTPUT = ./bin
DIR_SRC = ./src
DIR_EXEC = execs
NOMBRE_MAIN = main
CFLAGS = -O2 -pedantic

all: exec main

main:
# Crear el directorio "bin"
	mkdir -p $(DIR_OUTPUT)

# Compilar el main
	gcc $(CFLAGS) $(DIR_SRC)/$(NOMBRE_MAIN).c -o $(DIR_OUTPUT)/$(NOMBRE_MAIN)

	@echo Entrar a la carpeta $(DIR_OUTPUT) y ejecutar ./$(NOMBRE_MAIN)
	@echo Para mas informacion, leer el readme

exec:
# Crear el directorio "bin/execs"
	mkdir -p $(DIR_OUTPUT)/$(DIR_EXEC)

# Compilar los exec
	gcc $(CFLAGS) $(DIR_SRC)/$(DIR_EXEC)/mult.c -o $(DIR_OUTPUT)/$(DIR_EXEC)/mult
	gcc $(CFLAGS) $(DIR_SRC)/$(DIR_EXEC)/multconstante.c -o $(DIR_OUTPUT)/$(DIR_EXEC)/multconstante
	gcc $(CFLAGS) $(DIR_SRC)/$(DIR_EXEC)/resta.c -o $(DIR_OUTPUT)/$(DIR_EXEC)/resta
	gcc $(CFLAGS) $(DIR_SRC)/$(DIR_EXEC)/suma.c -o $(DIR_OUTPUT)/$(DIR_EXEC)/suma
	gcc $(CFLAGS) $(DIR_SRC)/$(DIR_EXEC)/trans.c -o $(DIR_OUTPUT)/$(DIR_EXEC)/trans

clean:
	rm -rf $(DIR_OUTPUT)/*
