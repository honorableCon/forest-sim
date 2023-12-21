#ifndef FOREST_H
#define FOREST_H

typedef struct Cell {
    char type;
    int state;
    int degree;
} Cell;

typedef struct Forest {
    Cell **cells;
    int rows;
    int cols;
} Forest;

Forest* createForest(int rows, int cols);
void destroyForest(Forest *forest);
void initializeForest(Forest *forest);
void printForest(Forest *forest);
void startSimulation(Forest *forest, int iterations);
void modifyCell(Forest *forest);
void checkFireSpread(Forest *forest);

// d'autre fonctions

#endif
