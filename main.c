#include <stdio.h>
#include "forest.h"
#include "user_input.h"
#include "simulation.h"

int main() {
    // Déclarer la forêt
    Forest forest;

    // Demander à l'utilisateur les dimensions de la forêt
    int length, width;
    getUserDimensions(&length, &width);

    // Initialiser la forêt avec les dimensions fournies
    initializeForest(&forest, length, width);

    // Afficher le menu et traiter le choix de l'utilisateur
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Remplir la forêt aléatoirement\n");
        printf("2. Remplir la forêt manuellement\n");
        printf("3. Démarrer la simulation\n");
        printf("4. Revenir en arrière dans la simulation\n");
        printf("5. Vérifier la propagation du feu\n");
        printf("6. Quitter\n");
        printf("Entrez votre choix : ");
        choice = getUserChoice();

        // Traiter le choix de l'utilisateur
        switch (choice) {
            case 1:
                fillRandomForest(&forest);
                printForest(&forest);
                break;

            case 2:
                fillManualForest(&forest);
                printForest(&forest);
                break;

            case 3:
                // Demander le nombre d'itérations pour la simulation
                int iterations = getSimulationIterations();
                simulateFire(&forest, iterations);
                printForest(&forest);
                break;

            case 4:
                // Revenir en arrière dans la simulation
                int steps = getStepsToGoBack();
                goBackInSimulation(&forest, steps);
                printForest(&forest);
                break;
            case 5:
                // Modifier une cellule
                int row, col, newType, newState, newDegree;
                getCellModification(&row, &col, &newType, &newState, &newDegree);
                modifyCell(&forest, row, col, newType, newState, newDegree);
                printForest(&forest);
                break;
            case 6:
    		 checkFirePropagation(&forest);
    		 break;

            case 7:
                printf("Au revoir !\n");
                break;
            

            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choice != 7);

    return 0;
}

