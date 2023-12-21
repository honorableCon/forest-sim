#include "utilities.h"
#include "forest.h"
#include <stdio.h>
#include <stdlib.h>

int isValidCoordinate(struct Forest *forest, int x, int y) {
    return (x >= 0 && x < forest->rows && y >= 0 && y < forest->cols);
}

int getRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}


/*void initializeForestRandomly(struct Forest *forest) {
    for (int i = 0; i < forest->rows; i++) {
        for (int j = 0; j < forest->cols; j++) {
            // Remplir chaque cellule avec des valeurs par défaut
            forest->cells[i][j].type = getRandomCellType();
            forest->cells[i][j].state = 0;
            forest->cells[i][j].degree = 0;
        }
    }

    // Choisissez une cellule aléatoire pour commencer l'incendie
    int startX = getRandomNumber(0, forest->rows - 1);
    int startY = getRandomNumber(0, forest->cols - 1);

    // Allumer l'incendie dans la cellule initiale
    forest->cells[startX][startY].state = 1;
    forest->cells[startX][startY].degree = 1;
}*/
void initializeForestRandomly(struct Forest *forest) {
    for (int i = 0; i < forest->rows; i++) {
        for (int j = 0; j < forest->cols; j++) {
            // Remplir chaque cellule avec des valeurs aléatoires (type, état, degré)
            forest->cells[i][j].type = getRandomCellType();
            forest->cells[i][j].state = 0;  // Initialisez à 0, pas en feu
            // Utilisez la fonction getRandomDegree en fonction du type de cellule
            forest->cells[i][j].degree = getRandomDegree(forest->cells[i][j].type);
        }
    }
}


// Ajoutez cette fonction pour obtenir le degré aléatoire en fonction du type de cellule
int getRandomDegree(char cellType) { 
	int degree;
    switch (cellType) {
        case '+':
            return 0;
        case '*':
            return 4;
        case ' ':
            return 2;
        case '#':
            return 5;
        case 'x':
            return 3;
        case '/':
            return 0;
        case '-':
            return 1;
        case '@':
            return 0;
        default:
            return degree;
    }

char getRandomCellType() {
    char cellTypes[] = { '+', '*', ' ', '#', 'x', '/', '-', '@' };
    int numTypes = sizeof(cellTypes) / sizeof(char);
    int randomIndex = getRandomNumber(0, numTypes - 1);
    return cellTypes[randomIndex];
}
}


