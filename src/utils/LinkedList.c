#include <stdlib.h>
#include <stdio.h>

#include "LinkedList.h"

Node* newNode(int data){
    Node *n = (Node*) malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    return n;
}

void setNext(Node *node, Node *next){
    node->next = next;
}

List* newList(){
    List* l = (List*) malloc(sizeof(List));
    l->head = newNode(-1);
    l->size = 0;
    return l;
}

List *newListFrom(int elements[], int n) {
    List *l = newList();
    insertAllArray(l, 0, elements, n);
    return l;
}

int listIsEmpty(List ls){
    return ls.size == 0;
}

void listInsert(List *ls, int position, int i) {
    Node *n = newNode(i);
    Node *current = ls->head;
    for (int j = 0; j < position; j++) {
        current = current->next;
    }
    Node *next = current->next;
    n->next = next;
    current->next = n;
    ls->size++;
}

void insertAllList(List *ls, int position, List in) {
  int arr[in.size];
  Node *current = in.head;
  for (int i = 0; i < in.size; i++) {
    current = current->next;
    arr[i] = current->data;
  }
  insertAllArray(ls, position, arr, in.size);
}

void insertAllArray(List *ls, int position, int elements[], int n) {
    if (n == 0) return;
    Node *first = newNode(elements[0]);
    Node *last = first;
    Node *node;

    for (int i = 1; i < n; i++) {
        node = newNode(elements[i]);
        last->next = node;
        last = node;
    }

    // Go to the position
    Node *current = ls->head;
    for (int j = 0; j < position; j++) {
        current = current->next;
    }

    Node *next = current->next;
    last->next = next;
    current->next = first;
    ls->size += n;
}

int listGet(List ls, int position) {
    Node *current = ls.head->next;
    for (int j = 0; j < position; j++) {
        current = current->next;
    }
    return current->data;
}

int listContains(List ls, int i) {
    Node *current = ls.head->next;

    while (current != NULL) {
        if (current->data == i)
            return 1;
        current = current->next;
    }
    return 0;
}

int listDelete(List *ls, int position) {
    if (position >= ls->size) return -1;

    Node* current = ls->head;
    for (int j = 0; j < position; j++) {
         current = current->next;
    }

    Node* node = current->next;
    current->next = node->next;
    int data = node->data;
    free(node);
    ls->size--;
    return data;
}

void removeRepeated(List *ls) {
  Node *left = ls->head;
  Node *right, *prev;
  int removed;

  for (int i = 0; i < ls->size; i++) {
    left = left->next;
    right = left;
    prev = left;
    removed = 0;
    for (int j = i+1; j < ls->size; j++) {
      right = right->next;

      if (right->data == left->data) {
        prev->next = right->next;
        removed++;
      } else {
        prev = right;
      }
    }
    ls->size -= removed;
  }
}

int freeList(List *ls){
    for (int j = 0; j < ls->size; j++){
        listDelete(ls, 0);
    }
    free(ls->head);
    free(ls);
}

void printList(List ls) {
    if (ls.size == 0) {
        printf("[]\n");
        return;
    }
    Node *current = ls.head->next;
    printf("[");
    for (int i = 0; i < ls.size - 1; i++) {
        printf("%d, ", current->data);
        current = current->next;
    }
    printf("%d]\n", current->data);
}