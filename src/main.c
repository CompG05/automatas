#include <stdio.h>

#include "automata.h"
#include "LinkedList.h"

int main() {
    int alphabet_array[] = {'a', 'b'};
    int num_states = 4;
    List *alphabet = newListFrom(alphabet_array, 2);
    Transition transitions[] = {
            newTransition(0, newListFrom((int[]) {1}, 1), 'a'),
            newTransition(1, newListFrom((int[]) {2}, 1), 'b'),
            newTransition(1, newListFrom((int[]) {3}, 1), 'a'),
            newTransition(3, newListFrom((int[]) {3}, 1), 'a'),
            newTransition(3, newListFrom((int[]) {3}, 1), 'b'),
            newTransition(-1, newList(), ' '),
    };
    int start = 0;
    List *finals = newListFrom((int []){2}, 1);

    Automata a = newAutomata(num_states, alphabet, transitions, start, finals);
    printAutomata(a);

    char s1[] = "ab";
    char s2[] = "abab";
    char s3[] = "a";
    char s4[] = "";

    printf("Accepts '%s': %d\n", s1, runAutomata(a, s1));
    printf("Accepts '%s': %d\n", s2, runAutomata(a, s2));
    printf("Accepts '%s': %d\n", s3, runAutomata(a, s3));
    printf("Accepts '%s': %d\n", s4, runAutomata(a, s4));

}
