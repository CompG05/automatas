#include <stdio.h>

#include "automata.h"
#include "LinkedList.h"
#include "Set.h"

int main() {
    int alphabet_array[] = {'a', 'b'};
    int num_states = 4;
    Set *alphabet = newSetFromArray(alphabet_array, 2);
    Transition transitions[] = {
            newTransition(0, newSetFromArray((int[]) {1}, 1), 'a'),
            newTransition(1, newSetFromArray((int[]) {2}, 1), 'b'),
            newTransition(1, newSetFromArray((int[]) {3}, 1), 'a'),
            newTransition(3, newSetFromArray((int[]) {3}, 1), 'a'),
            newTransition(3, newSetFromArray((int[]) {3}, 1), 'b'),
            newTransition(0, newSetFromArray((int[]) {2}, 1), '\\'),
            newTransition(-1, newSet(), ' '),
    };
    int start = 0;
    Set *finals = newSetFromArray((int []){2}, 1);

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