#include <stdio.h>

#include "automata.h"
#include "LinkedList.h"
#include "readAutomata.h"
#include "writeAutomata.h"
#include "Set.h"

int main() {
/*
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
          newTransition(2, newSetFromArray((int[]) {3}, 1), '\\'),
          newTransition(3, newSetFromArray((int[]) {0,2}, 2), '\\'),
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

  Set *states = newSetFromArray((int[]) {0,1}, 2);
  printf("Lambda Closure of {0,1}: ");
  printSet(lClosure(a,*states));

  Set *states2 = newSetFromArray((int[]) {0,1,3}, 3);
  printf("Move with \\ from {0,1,3}: ");
  printSet(move(a,*states2,'\\'));

  Set *states3 = newSetFromArray((int[]) {1}, 1);
  printf("Lambda Closure ( Move({1}, a) ): ");
  printSet(lClosure(a,move(a,*states3,'a')));


  printf("\n\n\n-----------------------toAFD Test--------------------------\n");

  int alphabet_array2[] = {'a', 'b'};
  int num_states2 = 5;
  Set *alphabet2 = newSetFromArray(alphabet_array2, 2);
  Transition transitions2[] = {
          newTransition(0, newSetFromArray((int[]) {1}, 1), 'b'),
          newTransition(0, newSetFromArray((int[]) {2}, 1), '\\'),
          newTransition(1, newSetFromArray((int[]) {0, 2}, 2), 'a'),
          newTransition(2, newSetFromArray((int[]) {3}, 1), 'b'),
          newTransition(3, newSetFromArray((int[]) {4}, 1), 'b'),
          newTransition(4, newSetFromArray((int[]) {2}, 1), 'a'),
          newTransition(-1, newSet(), ' '),
  };
  int start2 = 0;
  Set *finals2 = newSetFromArray((int []){2}, 1);

  Automata a2 = newAutomata(num_states2, alphabet2, transitions2, start2, finals2);
  printAutomata(a2);
  printAutomata(toAFD(a2));
*/

  Automata a = readAutomata("/home/pablo/UNI/automatas/automatas/automata.dot");
  printAutomata(a);
  printf("\n\n------------~ toAFD ~--------------\n");
  Automata aAFD = toAFD(a);
  printAutomata(aAFD);

  printf("\n\n------------~ runAutomata ~--------------\n");

  char s1[] = "11";
  char s2[] = "1";
  char s3[] = "";
  char s4[] = "1100010";

  printf("AFD accepts '%s' : %d\n", s1, runAutomata(aAFD, s1));
  printf("AFD accepts '%s' : %d\n", s2, runAutomata(aAFD, s2));
  printf("AFD accepts '%s' : %d\n", s3, runAutomata(aAFD, s3));
  printf("AFD accepts '%s' : %d\n", s4, runAutomata(aAFD, s4));

  writeAutomata(a, "../aNFA");
  writeAutomata(aAFD, "../aDFA");

}