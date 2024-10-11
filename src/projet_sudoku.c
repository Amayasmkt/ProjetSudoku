#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>

#define N 9
#define NB_THREADS 9

struct ThreadArgs {
    int** grille;
    int ligne;
    int colonne;
    bool* solution_trouvee;
};

// Check si on peut ajouter un chiffre dans la case
bool estValide(int** grille, int ligne, int colonne, int valeur) {
    for (int x = 0; x < N; x++) {
        if (sudoku_get(grille, ligne, x) == valeur || sudoku_get(grille, x, colonne) == valeur) {
            return false;
        }
    }

    int startLigne = ligne - ligne % 3, startColonne = colonne - colonne % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku_get(grille, i + startLigne, j + startColonne) == valeur) {
                return false;
            }
        }
    }

    return true;
}

bool rempliSudoku(int** grille, int ligne, int colonne) {
    if (ligne == N - 1 && colonne == N) {
        return true;
    }

    if (colonne == N) {
        ligne++;
        colonne = 0;
    }

    if (sudoku_get(grille, ligne, colonne) != 0) {
        return rempliSudoku(grille, ligne, colonne + 1);
    }

    int nums[N];
    for (int i = 0; i < N; i++) {
        nums[i] = i + 1;
    }

    for (int i = N - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    for (int k = 0; k < N; k++) {
        int num = nums[k];
        if (estValide(grille, ligne, colonne, num)) {
            sudoku_set(grille, ligne, colonne, num);
            if (rempliSudoku(grille, ligne, colonne + 1)) {
                return true;
            }
            sudoku_set(grille, ligne, colonne, 0);
        }
    }

    return false;
}

void genereGrilleComplete(int** grille) {
    rempliSudoku(grille, 0, 0);
}

// Fonction pour copier une grille de Sudoku
int** sudoku_copy(int** grille) {
    int** copy = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        copy[i] = (int*)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            copy[i][j] = sudoku_get(grille, i, j);
        }
    }
    return copy;
}

bool uniqueSolution(int** grille) {
    int** copy = sudoku_copy(grille);
    bool unique = rempliSudoku(copy, 0, 0);
    sudoku_free(copy);
    return unique;
}

void* thread_func(void* args) {
    struct ThreadArgs* arguments = (struct ThreadArgs*) args;
    int** grille = arguments->grille;
    bool* solution_trouvee = arguments->solution_trouvee;

    *solution_trouvee = uniqueSolution(grille);

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Veuillez préciser le nombre de cases que vous souhaitez en argument\n");
        exit(0);
    }

    int nbCases = atoi(argv[1]);

    if (nbCases < 17 || nbCases > 81) {
        printf("Le nombre de cases non vides doit être entre 17 et 81\n");
        exit(0);
    }

    srand(time(NULL));
    int** grille = sudoku_init();
    genereGrilleComplete(grille);

    int cases_a_vider = 81 - nbCases;

    while (cases_a_vider > 0) {
        int ligne = rand() % N;
        int colonne = rand() % N;

        if (sudoku_get(grille, ligne, colonne) != 0) {
            int temp = sudoku_get(grille, ligne, colonne);
            sudoku_set(grille, ligne, colonne, 0);

            pthread_t threads[NB_THREADS];
            struct ThreadArgs args;
            args.grille = grille;
            args.ligne = ligne;
            args.colonne = colonne;
            bool solution_trouvee = false;
            args.solution_trouvee = &solution_trouvee;

            for (int i = 0; i < NB_THREADS; i++) {
                pthread_create(&threads[i], NULL, thread_func, (void*)&args);
            }

            for (int i = 0; i < NB_THREADS; i++) {
                pthread_join(threads[i], NULL);
            }

            if (solution_trouvee) {
                cases_a_vider--;
            } else {
                sudoku_set(grille, ligne, colonne, temp);
            }
        }
    }

    sudoku_print(grille);
    sudoku_free(grille);

    return 0;
}
