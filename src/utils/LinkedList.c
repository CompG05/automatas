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

void insert(List *ls, int position, int i) {
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

void insertAll(List *ls, int position, int elements[], int n) {
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

int get(List ls, int position) {
    Node *current = ls.head->next;
    for (int j = 0; j < position; j++) {
        current = current->next;
    }
    return current->data;
}

int delete(List *ls, int position) {
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

int freeList(List *ls){
    for (int j = 0; j < ls->size -1; j++){
        delete(ls, 0);
    }
    free(ls->head);
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