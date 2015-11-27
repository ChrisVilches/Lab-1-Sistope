
DIR_OUTPUT = ./bin
DIR_SRC = ./src
DIR_EXEC = execs
NOMBRE_MAIN = main

all: exec main

main:
# Crear el directorio "bin"
	mkdir -p $(DIR_OUTPUT)

# Compilar el main
	gcc $(DIR_SRC)/$(NOMBRE_MAIN).c -o $(DIR_OUTPUT)/$(NOMBRE_MAIN) -O2

	@echo Entrar a la carpeta $(DIR_OUTPUT) y ejecutar ./$(NOMBRE_MAIN)
	@echo Para mas informacion, leer el readme

exec:
# Crear el directorio "bin/execs"
	mkdir -p $(DIR_OUTPUT)/$(DIR_EXEC)

# Compilar los exec
	gcc $(DIR_SRC)/$(DIR_EXEC)/mult.c -o $(DIR_OUTPUT)/$(DIR_EXEC)/mult -O2
	gcc $(DIR_SRC)/$(DIR_EXEC)/multconstante.c -o $(DIR_OUTPUT)/$(DIR_EXEC)/multconstante -O2
	gcc $(DIR_SRC)/$(DIR_EXEC)/resta.c -o $(DIR_OUTPUT)/$(DIR_EXEC)/resta -O2
	gcc $(DIR_SRC)/$(DIR_EXEC)/suma.c -o $(DIR_OUTPUT)/$(DIR_EXEC)/suma -O2
	gcc $(DIR_SRC)/$(DIR_EXEC)/trans.c -o $(DIR_OUTPUT)/$(DIR_EXEC)/trans -O2

clean:
	rm -rf $(DIR_OUTPUT)/*
