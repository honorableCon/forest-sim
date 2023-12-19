// simulation.h
#ifndef SIMULATION_H
#define SIMULATION_H

#include "forest.h"

void simulateFire(Forest* forest, int iterations);
int isNeighborOnFire(const Forest* forest, int row, int col);
void propagateFire(Forest* forest, Forest* tempForest, int row, int col);
void copyForest(const Forest* source, Forest* destination);
void checkFirePropagation(Forest* forest);
void goBackInSimulation(Forest* forest, int steps);
void saveCurrentState(Forest* forest, ForestState* state);
void restorePreviousState(Forest* forest, ForestState* state);

#endif // SIMULATION_H

