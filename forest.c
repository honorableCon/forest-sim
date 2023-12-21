#include "forest.h"
#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

Forest* createForest(int rows, int cols) {
    Forest *forest = (Forest*)malloc(sizeof(Forest));
    forest->rows = rows;
    forest->cols = cols;
    forest->cells = (Cell**)malloc(rows * sizeof(Cell*));

    for (int i = 0; i < rows; i++) {
        forest->cells[i] = (Cell*)malloc(cols * sizeof(Cell));
    }

    return forest;
}

void destroyForest(Forest *forest) {
    for (int i = 0; i < forest->rows; i++) {
        free(forest->cells[i]);
    }
    free(forest->cells);
    free(forest);
}

void initializeForest(Forest *forest) {
    for (int i = 0; i < forest->rows; i++) {
        for (int j = 0; j < forest->cols; j++) {
            forest->cells[i][j].type = ' ';  //  initialiser avec le type par défaut
            forest->cells[i][j].state = 0;
            forest->cells[i][j].degree = 0;
        }
    }
}
void printForest(Forest *forest) {
    for (int i = 0; i < forest->rows; i++) {
        for (int j = 0; j < forest->cols; j++) {
            // Afficher le type de cellule, l'état et le degré
            printf("%c%d%d ", forest->cells[i][j].type, forest->cells[i][j].state, forest->cells[i][j].degree);
        }
        printf("\n");
    }
}

/*void printForest(Forest *forest) {
    for (int i = 0; i < forest->rows; i++) {
        for (int j = 0; j < forest->cols; j++) {
            printf("%c%d%d ", forest->cells[i][j].type, forest->cells[i][j].state, forest->cells[i][j].degree);
        }
        printf("\n");
    }
}*/
void startSimulation(Forest *forest, int iterations) {
    for (int i = 0; i < iterations; i++) {
        checkFireSpread(forest);
        printf("Iteration %d:\n", i + 1);
        printForest(forest);
    }
}




void modifyCell(Forest *forest) {
    int x, y;
    printf("entrer les coordonnées de la cellule à modifier (x & y): ");
    scanf("%d %d", &x, &y);

    if (isValidCoordinate(forest, x, y)) {
        // Vous pouvez ajouter le code pour modifier la cellule à ces coordonnées ici
        // Par exemple, demandez à l'utilisateur de spécifier le nouveau type, l'état, ou le degré de la cellule

        printf("Enter le nouveau type, etat et degre de la cellule (%d, %d): ", x, y);
        scanf(" %c %d %d", &forest->cells[x][y].type, &forest->cells[x][y].state, &forest->cells[x][y].degree);

        // Modifier les symboles en fonction du type de cellule
        switch (forest->cells[x][y].type) {
            case '+':
                // Symbole pour le sol
                break;
            case '*':
                // Symbole pour l'arbre
                break;
            case ' ':
                // Symbole pour feuille
                break;
            case '#':
                // Symbole pour la roche
                break;
            case 'x':
                // Symbole pour herbe
                break;  
             case '/':
                // Symbole pour la eau
                break;  
             case '-':
                // Symbole pour la cendre
                break;
             case '@':
                // Symbole pour la ce,dr éteints
                break;
            
        }

        printf("Cellule: (%d, %d) modifiée.\n", x, y);

    } else {
        printf("Coordonnée invalides donc cellules non modifiée\n");
    }
}


/*void checkFireSpread(Forest *forest) {
    // Créer une copie de l'état actuel de la forêt pour éviter les modifications pendant la propagation du feu
    int copyState[forest->rows][forest->cols];

    for (int i = 0; i < forest->rows; i++) {
        for (int j = 0; j < forest->cols; j++) {
            copyState[i][j] = forest->cells[i][j].state;
        }
    }

    // Propagation du feu
    for (int i = 0; i < forest->rows; i++) {
        for (int j = 0; j < forest->cols; j++) {
            if (forest->cells[i][j].state == 1) {
                // La cellule est en feu

                // Si le degré est égal à 2, elle devient en cendres à la prochaine itération
                if (forest->cells[i][j].degree == 2) {
                    forest->cells[i][j].state = 0;  // En cendres
                    forest->cells[i][j].degree = 0;
                }
                // Si le degré est supérieur à 2, le degré diminue de 1
                else if (forest->cells[i][j].degree > 2) {
                    forest->cells[i][j].degree -= 1;
                }

                // Vérifier les voisins
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        int x = i + dx;
                        int y = j + dy;

                        if (isValidCoordinate(forest, x, y) &&
                            copyState[x][y] == 1 &&
                            forest->cells[x][y].type != 'S') {
                            // La cellule a un voisin en feu, elle s'enflamme à la prochaine itération
                            forest->cells[i][j].state = 1;
                            forest->cells[i][j].degree -= 1;
                            break;
                        }
                    }
                }
            }
        }
    }
}*/
void checkFireSpread(Forest *forest) {
    // Copie temporaire de la forêt pour stocker les modifications sans influencer les itérations en cours
    Forest tempForest;
    tempForest.rows = forest->rows;
    tempForest.cols = forest->cols;
    tempForest.cells = malloc(tempForest.rows * sizeof(Cell*));
    for (int i = 0; i < tempForest.rows; i++) {
        tempForest.cells[i] = malloc(tempForest.cols * sizeof(Cell));
    }

    // Copier la forêt actuelle dans la tempForest
    for (int i = 0; i < forest->rows; i++) {
        for (int j = 0; j < forest->cols; j++) {
            tempForest.cells[i][j] = forest->cells[i][j];
        }
    }

    // Implémentation de la fonction de vérification de la propagation du feu
    for (int i = 0; i < forest->rows; i++) {
        for (int j = 0; j < forest->cols; j++) {
            // Pour vérifier les voisins de chaque cellule
            if (tempForest.cells[i][j].state == 0 && tempForest.cells[i][j].type != 'S') {
                // La cellule n'est pas en feu et n'est pas du sol
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        int x = i + dx;
                        int y = j + dy;

                        if (isValidCoordinate(forest, x, y) &&
                            tempForest.cells[x][y].state == 1) {
                            // La cellule a un voisin en feu, elle s'enflamme
                            forest->cells[i][j].state = 1;
                            forest->cells[i][j].degree = tempForest.cells[i][j].degree - 1;
                            break;
                        }
                    }
                }
            }
        }
    }

    // Libérer la mémoire allouée pour la tempForest
    for (int i = 0; i < tempForest.rows; i++) {
        free(tempForest.cells[i]);
    }
    free(tempForest.cells);
}




