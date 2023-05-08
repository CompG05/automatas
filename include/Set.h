#ifndef SET_H
#define SET_H

#include "LinkedList.h"

typedef struct Set {
  List *list;
  struct Set *selfPtr;
} Set;

Set* newSet();

Set* newSetFromArray(int elements[], int n);

int size(Set set);

int isEmpty(Set set);

int contains(Set set, int elem);

void add(Set *set, int elem);

void addAll(Set *a, Set b);

int equals(Set a, Set b);

Set intersection(Set a, Set b);

void printSet(Set set);

List asList(Set set);

Set* setCopy(Set* set);

void freeSet(Set *set);

#endif
