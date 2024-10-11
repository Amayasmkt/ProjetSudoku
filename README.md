# Générateur de Sudoku

## Aperçu

Ce projet génère des puzzles Sudoku avec une solution unique, en partant d'une grille entièrement résolue et en retirant des valeurs jusqu'à ce qu'il ne reste qu'un nombre spécifié de chiffres (`N`). Le défi est de garantir que chaque fois qu'une valeur est retirée, le puzzle ne possède qu'une seule solution valide.

Le processus est très gourmand en calculs, et pour l'optimiser, la solution utilise le multi-threading. Pour chaque valeur pouvant potentiellement être retirée, des threads sont créés pour tester différentes possibilités en parallèle. Si une solution est trouvée par un thread, les autres sont arrêtés.

## Fonctionnalités
- Génère des grilles de Sudoku avec une solution unique.
- Utilise le multi-threading pour optimiser le processus de génération de puzzle.
- Permet à l'utilisateur de spécifier combien de chiffres (`N`) doivent rester dans la grille.
- Utilise la bibliothèque externe `libsudoku.so` pour gérer la grille de Sudoku.

## Fonctionnement
1. Le programme commence avec une grille de Sudoku entièrement résolue et valide.
2. Une case non vide est sélectionnée au hasard.
3. Plusieurs threads (un pour chaque nombre possible dans la case) sont créés pour vérifier si la grille a toujours une solution après avoir remplacé la valeur dans cette case.
4. Si aucune solution valide n'est trouvée par les threads, le chiffre est retiré de la grille.
5. Le processus se poursuit jusqu'à ce qu'il ne reste que `N` valeurs dans la grille.

## Installation

1. Clonez le dépôt :
    ```bash
   git clone https://github.com/Amayasmkt/SudokuProject.git
   cd SudokuProject
    ```
2. Compilez le projet en utilisant le fichier `Makefile` fourni.

## Compilation
Pour compiler le programme, éxecutez :
  ```bash
    make build
```

Pour exécuter le programme avec une valeur de `N` comprise entre 40 et 50 :
```bash
    make run
```

Pour compiler le programme en mode débogage :
```bash
    make debug
```

## Utilisation

Le programme prend un argument,`N`, qui est le nombre de cases non vides à laisser dans le puzzle Sudoku final.

Exemple d'utilisation :
```bash
./projet_sudoku 45
```

Cela générera un puzzle Sudoku avec 45 chiffres.

## Dépendances
* Le projet repose sur la bibliothèque externe `libsudoku.so`, qui fournit plusieurs fonctions pour la gestion des grilles de Sudoku :
  - `int **sudoku_init();` - Initialise une grille de Sudoku.
  - `void sudoku_free(int **sudoku);` - Libère la mémoire allouée pour une grille.
  - `void sudoku_print(int **sudoku);` - Affiche la grille de Sudoku.
  - `int sudoku_get(int **sudoku, int x, int y);` - Récupère la valeur d'une case.
  - `void sudoku_set(int **sudoku, int x, int y, int value);` - Modifie la valeur d'une case.

## Multi-threading
Pour chaque case non vide sélectionnée au hasard, le programme génère huit threads pour essayer de remplacer le chiffre actuel par d'autres possibilités (1-9). Si un thread trouve une 
solution valide, les autres sont arrêtés, et le programme passe à la case suivante. Cette approche multi-threadée aide à réduire le temps de calcul nécessaire pour vérifier 
la validité de la grille après chaque suppression de chiffre.

## Auteur
* Amayas Mokhtari
