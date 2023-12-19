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

typedef enum {
    FEU,
    EN_FEU,
    ETEINT
} ETAT;

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
    int** visited;
    Cell** cells;
} Forest, ForestState;

// Prototypes des fonctions
void initializeForest(Forest* forest, int length, int width);
void fillRandomForest(Forest* forest);
void fillManualForest(Forest* forest);
void printForest(const Forest* forest);
void modifyCell(Forest* forest, int row, int col, int newType, int newState, int newDegree);

#endif // FOREST_H

