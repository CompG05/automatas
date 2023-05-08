#include <stdio.h>

#include "automata.h"
#include "writeAutomata.h"
#include "Set.h"

int main(int argc, char** argv) {
  int alphabet_array[] = {'a', 'b', 'c'};
  int num_states = 3;
  Set *alphabet = newSetFromArray(alphabet_array, 3);
  Transition transitions[] = {
          newTransition(0, newSetFromArray((int[]) {0}, 1), 'a'),
          newTransition(0, newSetFromArray((int[]) {1}, 1), 'b'),
          newTransition(0, newSetFromArray((int[]) {2}, 1), 'c'),
          newTransition(1, newSetFromArray((int[]) {0}, 1), '_'),
          newTransition(1, newSetFromArray((int[]) {1}, 1), 'a'),
          newTransition(1, newSetFromArray((int[]) {2}, 1), 'b'),
          newTransition(2, newSetFromArray((int[]) {1}, 1), '_'),
          newTransition(2, newSetFromArray((int[]) {2}, 1), 'a'),
          newTransition(2, newSetFromArray((int[]) {0}, 1), 'c'),
          newTransition(-1, newSet(), ' '),
  };
  int start = 0;
  Set *finals = newSetFromArray((int []){2}, 1);

  Automata a = newAutomata(num_states, alphabet, transitions, start, finals);
  printf("Writing following automata to test/files/test_write_autom.dot\n");
  printAutomata(a);

  writeAutomata(a,"test/files/test_write_autom.dot");
  freeAutomata(&a);
  printf("\nfinished!\n");

}

