# Nom du fichier exécutable
EXEC = projet_sudoku

# Nom du fichier source
SRC = src/projet_sudoku.c

# Compilateur
CC = gcc

# Options de compilation pour la construction normale
CFLAGS = -Wall -Wextra -pthread -Iheader
LDFLAGS = -L./lib -lsudoku -Wl,-rpath,./lib

# Options de compilation pour le mode debug
DEBUG_FLAGS = -g

# Règle par défaut : build
all: build

# Règle pour compiler le programme
build: $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC) $(LDFLAGS)

# Règle pour exécuter le programme avec une valeur spécifiée
run: build
	@read -p "Entrez une valeur entre 40 et 50 : " value; \
	./$(EXEC) $$value

# Règle pour compiler le programme en mode debug
debug: $(SRC)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(EXEC) $(SRC) $(LDFLAGS)

# Règle pour nettoyer les fichiers générés par la compilation
clean:
	rm -f $(EXEC)
	rm -f *.o

.PHONY: all build run debug clean
