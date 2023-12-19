#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "forest.h"

void initializeForest(Forest* forest, int length, int width) {
    forest->length = length;
    forest->width = width;

    // Allouer de la mémoire pour la matrice de cellules
    forest->cells = (Cell**)malloc(length * sizeof(Cell*));
    for (int i = 0; i < length; ++i) {
        forest->cells[i] = (Cell*)malloc(width * sizeof(Cell));
    }

    // Initialiser chaque cellule de la forêt
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
            forest->cells[i][j].type = SOL;
            forest->cells[i][j].state = 0;
            forest->cells[i][j].degree = 0;
        }
    }
}

void fillRandomForest(Forest* forest) {
    // Code pour remplir la forêt aléatoirement
    // ...

    // Exemple : Remplir avec des arbres au hasard
    srand(time(NULL));
    for (int i = 0; i < forest->length; ++i) {
        for (int j = 0; j < forest->width; ++j) {
            if (rand() % 2 == 0) {
                forest->cells[i][j].type = ARBRE;
            }
        }
    }
}

void fillManualForest(Forest* forest) {
    // Code pour permettre à l'utilisateur de remplir manuellement la forêt
    // ...

    // Exemple : Remplir avec des arbres selon la saisie de l'utilisateur
    for (int i = 0; i < forest->length; ++i) {
        for (int j = 0; j < forest->width; ++j) {
            printf("Entrez le type de cellule pour la position [%d, %d] (0-6) : ", i, j);
            scanf("%d", &(forest->cells[i][j].type));

            // Valide la saisie de l'utilisateur pour le type de cellule.
            if (forest->cells[i][j].type < 0 || forest->cells[i][j].type > 6) {
                printf("Type de cellule invalide. Utilisation de SOL par défaut.\n");
                forest->cells[i][j].type = SOL;
            }

            forest->cells[i][j].state = 0;
            forest->cells[i][j].degree = 0;
        }
    }
}



void modifyCell(Forest* forest, int row, int col, int newType, int newState, int newDegree) {
    if (row >= 0 && row < forest->length && col >= 0 && col < forest->width) {
        forest->cells[row][col].type = newType;
        forest->cells[row][col].state = newState;
        forest->cells[row][col].degree = newDegree;
        printf("Cellule modifiée avec succès.\n");
    } else {
        printf("Coordonnées de cellule invalides.\n");
    }
}


void printForest(const Forest* forest) {
    // Afficher la forêt en utilisant les symboles correspondants aux types de cellules
    for (int i = 0; i < forest->length; ++i) {
        for (int j = 0; j < forest->width; ++j) {
            switch (forest->cells[i][j].type) {
                case SOL:
                    printf("+ ");
                    break;
                case ARBRE:
                    printf("* ");
                    break;
                case FEUILLE:
                    printf("  ");
                    break;
                case ROCHE:
                    printf("# ");
                    break;
                case HERBE:
                    printf("x ");
                    break;
                case EAU:
                    printf("/ ");
                    break;
                case CENDRES:
                    printf("- ");
                    break;
                case CENDRES_ETEINTES:
                    printf("@ ");
                    break;
                default:
                    printf("? ");
                    break;
            }
        }
        printf("\n");
    }
}


