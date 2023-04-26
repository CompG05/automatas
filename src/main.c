#include <stdio.h>

#include "automata.h"
#include "LinkedList.h"

int main() {
    int a[] = {1,2,3,4, 5};
    List *ls = newList();
    insertAll(ls, 0, a, 5);
    printList(*ls);
    printf("Inserting 10 at position 3\n");
    insert(ls, 3, 10);
    printList(*ls);
    printf("Deleting from position 2\n");
    delete(ls, 2);
    printList(*ls);
    printf("Inserting 13,14 at position 0\n");
    int b[] = {13,14};
    insertAll(ls, 0, b, 2);
    printList(*ls);
    printf("Inserting 15,16 at position 2\n");
    int c[] = {15,16};
    insertAll(ls, 2, c, 2);
    printList(*ls);
    printf("Getting from position 7: %d\n", get(*ls, 7));
    printf("Current size: %d\n", ls->size);
}
