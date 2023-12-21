#ifndef UTILITIES_H
#define UTILITIES_H

#include "forest.h"

// Déclaration forward pour le type Forest
struct Forest;

int isValidCoordinate(struct Forest *forest, int x, int y);
int getRandomNumber(int min, int max);
void initializeForestRandomly(struct Forest *forest);
char getRandomCellType();
int getRandomDegree(char cellType);

//d'autres déclarations de fonctions

#endif
