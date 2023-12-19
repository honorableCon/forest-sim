#ifndef FOREST_H
#define FOREST_H

// Définir les types de cellules
typedef enum {
    SOL,
    ARBRE,
    FEUILLE,
    ROCHE,
    HERBE,
    EAU,
    CENDRES,
    CENDRES_ETEINTES
} CellType;

// Structure de la cellule de la forêt
typedef struct {
    CellType type;
    int state;
    int degree;
} Cell;

// Structure de la forêt
typedef struct {
    int length;
    int width;
    Cell** cells;
} Forest;

// Prototypes des fonctions
void initializeForest(Forest* forest, int length, int width);
void fillRandomForest(Forest* forest);
void fillManualForest(Forest* forest);
void printForest(const Forest* forest);

#endif // FOREST_H

