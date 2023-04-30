#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node* newNode(int data);

void setNext(Node *node, Node *next);

typedef struct List {
  Node *head;
  int size;
} List;

List* newList();

List* newListFrom(int elements[], int n);

int listIsEmpty(List ls);

void listInsert(List *ls, int position, int i);

void insertAllList(List *ls, int position, List in);

void insertAllArray(List *ls, int position, int elements[], int n);

int listGet(List ls, int position);

int listContains(List ls, int i);

int listDelete(List *ls, int position);

void removeRepeated(List *ls);

int freeList(List *ls);

void printList(List ls);

#endif