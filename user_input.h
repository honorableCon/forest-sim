#ifndef USER_INPUT_H
#define USER_INPUT_H

// Inclure les fichiers d'en-tête nécessaires
#include "forest.h"

// Déclarations des fonctions
int getUserChoice();
void getUserDimensions(int* length, int* width);
void fillRandomForest(Forest* forest);
void fillManualForest(Forest* forest);
int getSimulationIterations();
void getCellModification(int* row, int* col, int* newType, int* newState, int* newDegree);

#endif // USER_INPUT_H

