// simulation.h
#ifndef SIMULATION_H
#define SIMULATION_H

#include "forest.h"

void simulateFire(Forest* forest, int iterations);
int isNeighborOnFire(const Forest* forest, int row, int col);
void propagateFire(Forest* forest, int iterations);
void copyForest(const Forest* source, Forest* destination);
//void checkFirePropagation(Forest* forest);
int checkFirePropagation(Forest* forest, int pointA, int pointB, int* steps);
void goBackInSimulation(Forest* forest, int steps);
void saveCurrentState(Forest* forest, ForestState* state);
void restorePreviousState(Forest* forest, ForestState* state);
void resetVisitedCells(Forest* forest);

#endif // SIMULATION_H

