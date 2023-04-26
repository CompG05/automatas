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

int isEmpty(List ls);

void insert(List *ls, int position, int i);

void insertAll(List *ls, int position, int elements[], int n);

int get(List ls, int position);

int contains(List ls, int i);

int delete(List *ls, int position);

int freeList(List *ls);

void printList(List ls);

#endif