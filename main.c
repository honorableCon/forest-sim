#include <stdio.h>
#include <stdlib.h>
#include "forest.h"
#include "utilities.h"

void initializeForestManually(Forest *forest) {
    for (int i = 0; i < forest->rows; i++) {
        for (int j = 0; j < forest->cols; j++) {
            printf("Enter the type, state, and degree for the cell at (%d, %d): ", i, j);
            scanf(" %c %d %d", &forest->cells[i][j].type, &forest->cells[i][j].state, &forest->cells[i][j].degree);
        }
    }
}

int main() {
    int rows, cols;
    printf("Enter the dimensions of the forest (rows and columns): ");
    scanf("%d %d", &rows, &cols);

    Forest *forest = createForest(rows, cols);
    initializeForest(forest);

    int choice;
    int iterations = 0;

    while (1) {
        printf("\nMenu :\n");
        printf("1. Remplir la forêt aléatoirement\n");
        printf("2. Remplir la forêt manuellement\n");
        printf("3. Démarrer la simulation\n");
        printf("4. Modifier une cellule\n");
        printf("5. Vérifier la propagation du feu\n");
        printf("6. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                // Fill Forest Randomly
                initializeForestRandomly(forest);
                printForest(forest);
                break;
            case 2:
                initializeForestManually(forest);
                printForest(forest);
                break;
            case 3:
                // Start Simulation
                if (iterations == 0) {
                    printf("Enter the number of simulation iterations: ");
                    scanf("%d", &iterations);
                }
                startSimulation(forest, iterations);
                break;
            case 4:
                // Modify Cell
                modifyCell(forest);
                printForest(forest);
                break;
            case 5:
                // Check Fire Spread
                checkFireSpread(forest);
                break;
            case 6:
                // Quit
                destroyForest(forest);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
