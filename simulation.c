// simulation.c
#include <stdio.h>
#include "simulation.h"
#include "forest.h"

void simulateFire(Forest* forest, int iterations) {
    for (int t = 0; t < iterations; ++t) {
        printf("Iteration %d :\n", t);
        printForest(forest);

        Forest tempForest;
        initializeForest(&tempForest, forest->length, forest->width);

        for (int i = 0; i < forest->length; ++i) {
            for (int j = 0; j < forest->width; ++j) {
                if (forest->cells[i][j].type == FEU) {
                    propagateFire(forest, &tempForest, i, j);
                }
            }
        }

        copyForest(&tempForest, forest);
    }
}

void propagateFire(Forest* forest, int iterations) {
    for (int t = 0; t < iterations; ++t) {
        // Code pour la propagation du feu selon les règles spécifiées
        Forest tempForest;
        copyForest(forest, &tempForest);

        for (int i = 0; i < forest->length; ++i) {
            for (int j = 0; j < forest->width; ++j) {
                if (forest->cells[i][j].type != SOL && forest->cells[i][j].type != EAU) {
                    if (forest->cells[i][j].state == EN_FEU && forest->cells[i][j].degree == 2) {
                        // La cellule devient en cendres
                        tempForest.cells[i][j].type = CENDRES;
                        tempForest.cells[i][j].state = ETEINT;
                        tempForest.cells[i][j].degree = 0;
                    } else if (forest->cells[i][j].state == CENDRES && forest->cells[i][j].degree == 1) {
                        // Les cendres éteintes se transforment en cendres
                        tempForest.cells[i][j].type = CENDRES;
                        tempForest.cells[i][j].state = ETEINT;
                        tempForest.cells[i][j].degree = 0;
                    } else if (forest->cells[i][j].type == ARBRE || forest->cells[i][j].type == ROCHE ||
                               forest->cells[i][j].type == HERBE || forest->cells[i][j].type == FEUILLE) {
                        if (isNeighborOnFire(forest, i, j)) {
                            // La cellule prend feu
                            tempForest.cells[i][j].state = EN_FEU;
                            tempForest.cells[i][j].degree -= 1;
                        }
                    } else if (forest->cells[i][j].state == EN_FEU && forest->cells[i][j].degree > 2) {
                        // Le feu se propage et diminue le degré
                        tempForest.cells[i][j].degree -= 1;
                    }
                }
            }
        }

        // Copie la forêt temporaire dans la forêt principale
        copyForest(&tempForest, forest);

        // Affiche l'état de la forêt à chaque itération
        printf("Iteration %d:\n", t + 1);
        printForest(forest);
    }
}

// simulation.c
#include "simulation.h"

int isNeighborOnFire(const Forest* forest, int row, int col) {
    // Coordonnées des 8 voisins possibles (en supposant que la matrice est torique)
    int neighbors[][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},            {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (int i = 0; i < 8; ++i) {
        int newRow = row + neighbors[i][0];
        int newCol = col + neighbors[i][1];

        // Vérifie que les indices du voisin sont valides
        if (newRow >= 0 && newRow < forest->length && newCol >= 0 && newCol < forest->width) {
            // Vérifie si le voisin est en feu
            if (forest->cells[newRow][newCol].state == EN_FEU) {
                return 1;  // Un voisin est en feu
            }
        }
    }

    return 0;  // Aucun voisin n'est en feu
}


// simulation.c
#include "simulation.h"

void copyForest(const Forest* source, Forest* destination) {
    for (int i = 0; i < source->length; ++i) {
        for (int j = 0; j < source->width; ++j) {
            destination->cells[i][j].type = source->cells[i][j].type;
            destination->cells[i][j].state = source->cells[i][j].state;
            destination->cells[i][j].degree = source->cells[i][j].degree;
        }
    }
}
//---------------------------------------------------



void saveCurrentState(Forest* forest, ForestState* state) {
    // Copie de la matrice de cellules dans la structure ForestState
    for (int i = 0; i < forest->length; ++i) {
        for (int j = 0; j < forest->width; ++j) {
            state->cells[i][j].type = forest->cells[i][j].type;
            state->cells[i][j].state = forest->cells[i][j].state;
            state->cells[i][j].degree = forest->cells[i][j].degree;
        }
    }
}

void restorePreviousState(Forest* forest, ForestState* state) {
    // Restauration de l'état précédent à partir de la structure ForestState
    for (int i = 0; i < forest->length; ++i) {
        for (int j = 0; j < forest->width; ++j) {
            forest->cells[i][j].type = state->cells[i][j].type;
            forest->cells[i][j].state = state->cells[i][j].state;
            forest->cells[i][j].degree = state->cells[i][j].degree;
        }
    }
}

void goBackInSimulation(Forest* forest, int steps) {
    // Structure pour sauvegarder l'état précédent
    ForestState prevState;

    // Sauvegarde l'état actuel pour le restaurer ultérieurement
    saveCurrentState(forest, &prevState);

    // Effectue la simulation pour revenir en arrière
    for (int i = 0; i < steps; ++i) {
        simulateFire(forest, 1);
        saveCurrentState(forest, &prevState);
    }

    // Restaure l'état initial de la forêt
    restorePreviousState(forest, &prevState);
}


//---------------------------------------------------
// Fonction de recherche en profondeur
void dfs(Forest* forest, int row, int col, int* steps) {
    // Marquer la cellule actuelle comme visitée
    forest->visited[row][col] = 1;

    // Incrémenter le nombre d'étapes
    (*steps)++;

    // Coordonnées des voisins
    int neighbors[8][2] = {
        {-1, 0}, {-1, 1}, {0, 1}, {1, 1},
        {1, 0}, {1, -1}, {0, -1}, {-1, -1}
    };

    // Explorer les voisins
    for (int i = 0; i < 8; ++i) {
        int newRow = row + neighbors[i][0];
        int newCol = col + neighbors[i][1];

        // Vérifier les limites de la forêt
        if (newRow >= 0 && newRow < forest->length && newCol >= 0 && newCol < forest->width) {
            // Vérifier si la cellule n'a pas été visitée et si elle est en feu
            if (!forest->visited[newRow][newCol] && forest->cells[newRow][newCol].type == FEU) {
                // Appeler la recherche en profondeur pour le voisin non visité
                dfs(forest, newRow, newCol, steps);
            }
        }
    }
}

// Autres fonctions de simulation

int checkFirePropagation(Forest* forest, int pointA, int pointB, int* steps) {
    // Assurez-vous que les points A et B sont valides
    if (pointA < 0 || pointA >= forest->length * forest->width || pointB < 0 || pointB >= forest->length * forest->width) {
        printf("Coordonnées invalides pour les points A et B.\n");
        return -1;
    }

    // Convertissez les indices 1D en indices 2D
    int rowA = pointA / forest->width;
    int colA = pointA % forest->width;
    int rowB = pointB / forest->width;
    int colB = pointB % forest->width;

    // Vérifiez si un incendie peut se propager
    if (forest->cells[rowA][colA].type != FEU) {
        printf("La cellule de départ ne contient pas de feu.\n");
        return -1;
    }

    // Réinitialisez la forêt (marquez toutes les cellules comme non visitées)
    resetVisitedCells(forest);

    // Effectuez une recherche en profondeur pour vérifier la propagation du feu
    dfs(forest, rowA, colA, steps);

    // Si la cellule de destination a été visitée, l'incendie peut se propager
    if (forest->visited[rowB][colB]) {
        printf("L'incendie peut se propager de A à B en %d étapes.\n", *steps);
        return 1;
    } else {
        printf("L'incendie ne peut pas se propager de A à B.\n");
        return 0;
    }
}

// Autres fonctions de simulation

// Fonction de réinitialisation des cellules visitées
void resetVisitedCells(Forest* forest) {
    for (int i = 0; i < forest->length; ++i) {
        for (int j = 0; j < forest->width; ++j) {
            forest->visited[i][j] = 0;
        }
    }
}

// ... (autres fonctions de simulation)

