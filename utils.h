#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include "forest.h"

typedef struct {
    int x, y;
} Point;

typedef struct Node {
    Point point;
    struct Node *next;
} Node;


void enqueue(Node **head, Node **tail, Point point);

bool dequeue(Node **head, Node **tail, Point *point) ;

bool estAccessible(Foret *foret, int x, int y);

#endif