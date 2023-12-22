#ifndef FOREST_H
#define FOREST_H

typedef enum { SOL, ARBRE, FEUILLE, ROCHE, HERBE, EAU, CENDRES, CENDRES_ETEINTES } TypeCellule;

typedef struct {
    TypeCellule type;
    int etat; // 0 pour non en feu, 1 pour en feu
    int degre;
} Cellule;

typedef struct {
    Cellule **cellules;
    int largeur;
    int longueur;
} Foret;

Foret *initialiserForet(int largeur, int longueur);
void afficherForet(Foret *foret);
void libererForet(Foret *foret);
void remplirForetAleatoire(Foret *foret);
void remplirForetManuel(Foret *foret);
void simulerIncendie(Foret *foret, int iterations, int x, int y);
void modifierCellule(Foret *foret, int x, int y, TypeCellule type, int etat, int degre);
int verifierPropagation(Foret *foret, int x1, int y1, int x2, int y2);

#endif
