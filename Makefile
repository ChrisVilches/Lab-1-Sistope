DIR_OUTPUT = ./bin
DIR_SRC = ./src
DIR_EXEC = execs
NOMBRE_MAIN = main

all: exec main

main:
# Crear el directorio "bin"
	mkdir -p $(DIR_OUTPUT)

# Compilar el main
	gcc $(DIR_SRC)/$(NOMBRE_MAIN).c -o $(DIR_OUTPUT)/$(NOMBRE_MAIN)

	@echo 
	@echo '******'
	@echo Entrar a la carpeta $(DIR_OUTPUT) y ejecutar ./$(NOMBRE_MAIN)
	@echo Para mas informacion, leer el readme
	@echo '******'

exec:
# Crear el directorio "bin/execs"
	mkdir -p $(DIR_OUTPUT)/$(DIR_EXEC)

# Compilar los exec
	gcc $(DIR_SRC)/$(DIR_EXEC)/mult.c -o $(DIR_OUTPUT)/$(DIR_EXEC)/mult
	gcc $(DIR_SRC)/$(DIR_EXEC)/multconstante.c -o $(DIR_OUTPUT)/$(DIR_EXEC)/multconstante
	gcc $(DIR_SRC)/$(DIR_EXEC)/resta.c -o $(DIR_OUTPUT)/$(DIR_EXEC)/resta
	gcc $(DIR_SRC)/$(DIR_EXEC)/suma.c -o $(DIR_OUTPUT)/$(DIR_EXEC)/suma
	gcc $(DIR_SRC)/$(DIR_EXEC)/trans.c -o $(DIR_OUTPUT)/$(DIR_EXEC)/trans

clean:
	rm -rf $(DIR_OUTPUT)/*
