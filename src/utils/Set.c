#include <stdlib.h>

#include "Set.h"
#include "LinkedList.h"

Set* newSet() {
  Set *s = (Set*) malloc(sizeof(Set));
  s->list = newList();
  return s;
}

Set* newSetFromArray(int elements[], int n) {
  Set *s = (Set*) malloc(sizeof(Set));
  s->list = newListFrom(elements, n);
  removeRepeated(s->list);
  return s;
}

int size(Set set) {
  return set.list->size;
}

int isEmpty(Set set) {
  return size(set) == 0;
}

int contains(Set s, int elem) {
  return listContains(*s.list, elem);
}

int add(Set *set, int elem) {
  listInsert(set->list, 0, elem);
  removeRepeated(set->list);
}

void addAll(Set *a, Set b) {
  List bList = *b.list;
  List *aList = a->list;
  insertAllList(aList, 0, bList);
  removeRepeated(a->list);
}

void printSet(Set set) {
  printList(*set.list);
}

List asList(Set set) {
  return *set.list;
}
