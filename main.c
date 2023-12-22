#include "forest.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int largeur, longueur, choix, iterations, x, y;
    Foret *foret = NULL;

    printf("Simulation de propagation d'incendie en forêt\n");
    printf("Entrez la largeur de la forêt: ");
    scanf("%d", &largeur);
    printf("Entrez la longueur de la forêt: ");
    scanf("%d", &longueur);

    foret = initialiserForet(largeur, longueur);
    if (!foret) {
        fprintf(stderr, "Erreur lors de l'initialisation de la forêt.\n");
        return 1;
    }

    do {
        printf("\nMenu:\n");
        printf("1. Remplir la forêt aléatoirement\n");
        printf("2. Remplir la forêt manuellement\n");
        printf("3. Simuler un incendie\n");
        printf("4. Modifier une cellule\n");
        printf("5. Vérifier la propagation d'un point A à un point B\n");
        printf("6. Quitter\n");
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                remplirForetAleatoire(foret);
                afficherForet(foret);
                break;
            case 2:
                remplirForetManuel(foret);
                afficherForet(foret);
                break;
            case 3:
                printf("Entrez le nombre d'itérations pour la simulation: ");
                scanf("%d", &iterations);
                printf("Entrez les coordonnées de départ du feu (x y): ");
                scanf("%d %d", &x, &y);
                simulerIncendie(foret, iterations, x, y);
                break;
            case 4:
                printf("Entrez les coordonnées de la cellule à modifier (x y): ");
                scanf("%d %d", &x, &y);
                int tempType, etat, degre;
                printf("Entrez le nouveau type (0: SOL, 1: ARBRE, etc.), état (0 ou 1) et degré: ");
                scanf("%d %d %d", &tempType, &etat, &degre);
                modifierCellule(foret, x, y, (TypeCellule)tempType, etat, degre);
                afficherForet(foret);
                break;
            case 5:
                printf("Entrez les coordonnées du point A (x y): ");
                scanf("%d %d", &x, &y);
                int x2, y2;
                printf("Entrez les coordonnées du point B (x y): ");
                scanf("%d %d", &x2, &y2);
                if (verifierPropagation(foret, x, y, x2, y2)) {
                    printf("Un incendie peut se propager du point A au point B.\n");
                } else {
                    printf("Un incendie ne peut pas se propager du point A au point B.\n");
                }
                break;
            case 6:
                printf("Quitter.\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 6);

    libererForet(foret);
    return 0;
}
