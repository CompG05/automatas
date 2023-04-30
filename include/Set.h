#ifndef SET_H
#define SET_H

#include "LinkedList.h"

typedef struct Set {
  List *list;
} Set;

Set* newSet();

Set* newSetFromArray(int elements[], int n);

int size(Set set);

int isEmpty(Set set);

int contains(Set set, int elem);

int add(Set *set, int elem);

void addAll(Set *a, Set b);

void printSet(Set set);

#endif SET_H
