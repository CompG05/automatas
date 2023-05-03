#include <stdio.h>

#include "automata.h"
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
  printAutomata(a);

  Automata aAFD = toAFD(a);

  char s1[] = "aaaaaabaaaaaccababcbacab"; // 1
  char s2[] = "ab"; // 0
  char s3[] = "abaaaaaaa"; // 0
  char s4[] = "c"; // 1
  char s5[] = "cacbabacbacbacba"; // 1

  printf("AFD accepts '%s' (exp: 1) : %d\n", s1, runAutomata(aAFD, s1));
  printf("AFD accepts '%s' (exp: 0) : %d\n", s2, runAutomata(aAFD, s2));
  printf("AFD accepts '%s' (exp: 0) : %d\n", s3, runAutomata(aAFD, s3));
  printf("AFD accepts '%s' (exp: 1) : %d\n", s4, runAutomata(aAFD, s4));
  printf("AFD accepts '%s' (exp: 1) : %d\n", s5, runAutomata(aAFD, s5));

}
