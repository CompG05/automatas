#include <stdio.h>

#include "automata.h"
#include "Set.h"

int main(int argc, char** argv) {
  printf("\n\n\n-----------------------~ Move and lClosure ~--------------------------\n");
  int alphabet_array[] = {'a', 'b'};
  int num_states = 4;
  Set *alphabet = newSetFromArray(alphabet_array, 2);
  Transition transitions[] = {
          newTransition(0, newSetFromArray((int[]) {1}, 1), 'a'),
          newTransition(1, newSetFromArray((int[]) {2}, 1), 'b'),
          newTransition(1, newSetFromArray((int[]) {3}, 1), 'a'),
          newTransition(3, newSetFromArray((int[]) {3}, 1), 'a'),
          newTransition(3, newSetFromArray((int[]) {3}, 1), 'b'),
          newTransition(0, newSetFromArray((int[]) {2}, 1), '_'),
          newTransition(2, newSetFromArray((int[]) {3}, 1), '_'),
          newTransition(3, newSetFromArray((int[]) {0,2}, 2), '_'),
          newTransition(-1, newSet(), ' '),
  };
  int start = 0;
  Set *finals = newSetFromArray((int []){2}, 1);

  Automata a = newAutomata(num_states, alphabet, transitions, start, finals);
  printAutomata(a);

  Set *states = newSetFromArray((int[]) {0,1}, 2);
  printf("Lambda Closure of {0,1}: ");
  printSet(lClosure(a,*states));

  Set *states2 = newSetFromArray((int[]) {0,1,3}, 3);
  printf("Move with _ from {0,1,3}: ");
  printSet(move(a,*states2,'_'));

  Set *states3 = newSetFromArray((int[]) {1}, 1);
  printf("Lambda Closure ( Move({1}, a) ): ");
  printSet(lClosure(a,move(a,*states3,'a')));


  printf("\n\n\n-----------------------~ toAFD Test ~--------------------------\n");

  int alphabet_array2[] = {'a', 'b'};
  int num_states2 = 5;
  Set *alphabet2 = newSetFromArray(alphabet_array2, 2);
  Transition transitions2[] = {
          newTransition(0, newSetFromArray((int[]) {1}, 1), 'b'),
          newTransition(0, newSetFromArray((int[]) {2}, 1), '_'),
          newTransition(1, newSetFromArray((int[]) {0, 2}, 2), 'a'),
          newTransition(2, newSetFromArray((int[]) {3}, 1), 'b'),
          newTransition(3, newSetFromArray((int[]) {4}, 1), 'b'),
          newTransition(4, newSetFromArray((int[]) {2}, 1), 'a'),
          newTransition(-1, newSet(), ' '),
  };
  int start2 = 0;
  Set *finals2 = newSetFromArray((int []){2}, 1);

  Automata a2 = newAutomata(num_states2, alphabet2, transitions2, start2, finals2);
  printf("AFN: \n");
  printAutomata(a2);
    printf("\nAFD: \n");
  printAutomata(toAFD(a2));
}