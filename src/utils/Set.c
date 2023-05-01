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

void add(Set *set, int elem) {
  listInsert(set->list, 0, elem);
  removeRepeated(set->list);
}

void addAll(Set *a, Set b) {
  List bList = *b.list;
  List *aList = a->list;
  insertAllList(aList, 0, bList);
  removeRepeated(a->list);
}

int equals(Set a, Set b){
  List aList = asList(a);
  List bList = asList(b);

  for(int i = 0; i < aList.size; i++){
    if (!listContains(bList, listGet(aList, i))) return 0;
  }
  for(int i = 0; i < bList.size; i++){
    if (!listContains(aList, listGet(bList, i))) return 0;
  }

  return 1;
}

Set intersection(Set a, Set b){
  Set *result = newSet();
  List aList = asList(a);
  List bList = asList(b);

  for(int i = 0; i < aList.size; i++){
    int state = listGet(aList, i);
    if(listContains(bList, state))  add(result, state);
  }

  return *result;

}

void printSet(Set set) {
  printList(*set.list);
}

List asList(Set set) {
  return *set.list;
}
