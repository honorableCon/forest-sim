#include "forest.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Foret *initialiserForet(int largeur, int longueur) {
    Foret *foret = malloc(sizeof(Foret));
    if (!foret) return NULL;

    foret->largeur = largeur;
    foret->longueur = longueur;

    foret->cellules = malloc(longueur * sizeof(Cellule*));
    if (!foret->cellules) {
        free(foret);
        return NULL;
    }

    for (int i = 0; i < longueur; i++) {
        foret->cellules[i] = malloc(largeur * sizeof(Cellule));
        if (!foret->cellules[i]) {
            // Libération de la mémoire en cas d'erreur
            for (int j = 0; j < i; j++) {
                free(foret->cellules[j]);
            }
            free(foret->cellules);
            free(foret);
            return NULL;
        }
    }

    // Initialisation des cellules
    for (int i = 0; i < longueur; i++) {
        for (int j = 0; j < largeur; j++) {
            foret->cellules[i][j].type = SOL;
            foret->cellules[i][j].etat = 0;
            foret->cellules[i][j].degre = 0;
        }
    }

    return foret;
}

void afficherForet(Foret *foret) {
    for (int i = 0; i < foret->longueur; i++) {
        for (int j = 0; j < foret->largeur; j++) {
            char symbole;
            switch (foret->cellules[i][j].type) {
                case SOL: symbole = '+'; break;
                case ARBRE: symbole = '*'; break;
                case FEUILLE: symbole = '2'; break;
                case ROCHE: symbole = '#'; break;
                case HERBE: symbole = 'x'; break;
                case EAU: symbole = '/'; break;
                case CENDRES: symbole = '-'; break;
                case CENDRES_ETEINTES: symbole = '@'; break;
                default: symbole = '?';
            }
            printf("%c ", symbole);
        }
        printf("\n");
    }
}

void libererForet(Foret *foret) {
    if (!foret) return;

    for (int i = 0; i < foret->longueur; i++) {
        free(foret->cellules[i]);
    }
    free(foret->cellules);
    free(foret);
}

void remplirForetAleatoire(Foret *foret) {
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

    for (int i = 0; i < foret->longueur; i++) {
        for (int j = 0; j < foret->largeur; j++) {
            int typeAleatoire = rand() % 8; // Génère un nombre entre 0 et 7
            foret->cellules[i][j].type = (TypeCellule)typeAleatoire;
            foret->cellules[i][j].etat = 0;
            foret->cellules[i][j].degre = (typeAleatoire == ARBRE || typeAleatoire == FEUILLE) ? 2 : 0;
        }
    }
}

void remplirForetManuel(Foret *foret) {
    int type;
    printf("Remplissage manuel de la forêt :\n");
    for (int i = 0; i < foret->longueur; i++) {
        for (int j = 0; j < foret->largeur; j++) {
            printf("Cellule [%d, %d] - Type (0: SOL, 1: ARBRE, 2: FEUILLE, 3: ROCHE, 4: HERBE, 5: EAU, 6: CENDRES, 7: CENDRES_ETEINTES): ", i, j);
            scanf("%d", &type);
            foret->cellules[i][j].type = (TypeCellule)type;
            foret->cellules[i][j].etat = 0;
            foret->cellules[i][j].degre = (type == ARBRE || type == FEUILLE) ? 2 : 0;
        }
    }
}

void modifierCellule(Foret *foret, int x, int y, TypeCellule type, int etat, int degre) {
    if (x >= 0 && x < foret->longueur && y >= 0 && y < foret->largeur) {
        foret->cellules[x][y].type = type;
        foret->cellules[x][y].etat = etat;
        foret->cellules[x][y].degre = degre;
    }
}

void propagerFeu(Foret *foret, int x, int y) {
    if (x < 0 || x >= foret->longueur || y < 0 || y >= foret->largeur) return;

    Cellule *cellule = &foret->cellules[x][y];
    if (cellule->type == EAU || cellule->type == ROCHE) return;

    if (cellule->etat == 1) {
        if (cellule->degre > 2) {
            cellule->degre--;
        } else {
            cellule->type = CENDRES;
            cellule->etat = 0;
            cellule->degre = 1;
        }
    } else if (cellule->etat == 0 && cellule->type != SOL && cellule->type != CENDRES && cellule->type != CENDRES_ETEINTES) {
        // Vérifiez les voisins pour voir si l'un d'entre eux est en feu
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                int voisinX = x + dx, voisinY = y + dy;
                if (voisinX >= 0 && voisinX < foret->longueur && voisinY >= 0 && voisinY < foret->largeur) {
                    Cellule voisin = foret->cellules[voisinX][voisinY];
                    if (voisin.etat == 1) {
                        cellule->etat = 1;
                        break;
                    }
                }
            }
            if (cellule->etat == 1) break;
        }
    }
}

void simulerIncendie(Foret *foret, int iterations, int x, int y) {
    if (x < 0 || x >= foret->longueur || y < 0 || y >= foret->largeur) return;

    foret->cellules[x][y].etat = 1; // Commencez l'incendie

    for (int it = 0; it < iterations; it++) {
        // Créez une copie de la forêt pour éviter de modifier la forêt en cours de parcours
        Foret *copieForet = initialiserForet(foret->largeur, foret->longueur);
        for (int i = 0; i < foret->longueur; i++) {
            for (int j = 0; j < foret->largeur; j++) {
                copieForet->cellules[i][j] = foret->cellules[i][j];
            }
        }

        // Propager le feu
        for (int i = 0; i < foret->longueur; i++) {
            for (int j = 0; j < foret->largeur; j++) {
                propagerFeu(copieForet, i, j);
            }
        }

        // Mettez à jour la forêt originale
        for (int i = 0; i < foret->longueur; i++) {
            for (int j = 0; j < foret->largeur; j++) {
                foret->cellules[i][j] = copieForet->cellules[i][j];
            }
        }

        libererForet(copieForet);

        // Afficher l'état actuel de la forêt
        afficherForet(foret);
        printf("Itération %d\n", it + 1);
    }
}


int verifierPropagation(Foret *foret, int x1, int y1, int x2, int y2) {
    if (!estAccessible(foret, x1, y1) || !estAccessible(foret, x2, y2)) {
        return 0;
    }

    bool **visited = malloc(foret->longueur * sizeof(bool *));
    for (int i = 0; i < foret->longueur; i++) {
        visited[i] = calloc(foret->largeur, sizeof(bool));
    }

    Node *queueHead = NULL, *queueTail = NULL;
    enqueue(&queueHead, &queueTail, (Point){x1, y1});

    int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    while (queueHead != NULL) {
        Point current;
        dequeue(&queueHead, &queueTail, &current);

        if (current.x == x2 && current.y == y2) {
            // Nettoyage
            for (int i = 0; i < foret->longueur; i++) {
                free(visited[i]);
            }
            free(visited);
            return 1;
        }

        for (int i = 0; i < 8; i++) {
            int newX = current.x + directions[i][0];
            int newY = current.y + directions[i][1];

            if (estAccessible(foret, newX, newY) && !visited[newX][newY]) {
                visited[newX][newY] = true;
                enqueue(&queueHead, &queueTail, (Point){newX, newY});
            }
        }
    }

    // Nettoyage
    for (int i = 0; i < foret->longueur; i++) {
        free(visited[i]);
    }
    free(visited);

    return 0;
}