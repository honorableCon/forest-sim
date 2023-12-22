#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"



// Fonctions auxiliaires pour la file d'attente utilisée dans BFS
void enqueue(Node **head, Node **tail, Point point) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    newNode->point = point;
    newNode->next = NULL;
    if (*tail != NULL) {
        (*tail)->next = newNode;
    }
    *tail = newNode;
    if (*head == NULL) {
        *head = newNode;
    }
}

bool dequeue(Node **head, Node **tail, Point *point) {
    if (*head == NULL) return false;
    Node *temp = *head;
    *point = temp->point;
    *head = (*head)->next;
    if (*head == NULL) {
        *tail = NULL;
    }
    free(temp);
    return true;
}

bool estAccessible(Foret *foret, int x, int y) {
    return x >= 0 && x < foret->longueur && y >= 0 && y < foret->largeur && 
           foret->cellules[x][y].type != EAU && foret->cellules[x][y].type != ROCHE;
}


