#include <stdio.h>
#include "user_input.h"

int getUserChoice() {
    int choice;
    printf("\n1. Remplir la forêt aléatoirement\n");
    printf("2. Remplir la forêt manuellement\n");
    printf("3. Démarrer la simulation\n");
    printf("4. Modifier une cellule\n");
    printf("5. Vérifier la propagation du feu\n");
    printf("6. Quitter\n");
    printf("Entrez votre choix : ");
    scanf("%d", &choice);
    return choice;
}

void getUserDimensions(int* length, int* width) {
    printf("Entrez les dimensions de la forêt (longueur et largeur) : ");
    scanf("%d %d", length, width);
}

int getStepsToGoBack(){
    int steps;
    printf("Entrez le nombre de pas de simulation : ");
    scanf("%d", &steps);
    return steps;
}


int getSimulationIterations() {
    int iterations;
    printf("Entrez le nombre d'itérations de simulation : ");
    scanf("%d", &iterations);
    return iterations;
}

void getCellModification(int* row, int* col, int* newType, int* newState, int* newDegree) {
    printf("Entrez les coordonnées de la cellule à modifier (ligne colonne) : ");
    scanf("%d %d", row, col);

    printf("Entrez le nouveau type de cellule (0-6) : ");
    scanf("%d", newType);

    printf("Entrez le nouvel état de la cellule (0 ou 1) : ");
    scanf("%d", newState);

    printf("Entrez le nouveau degré de la cellule : ");
    scanf("%d", newDegree);
}
