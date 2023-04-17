#include <stdio.h>
#include <stdlib.h>

#include "automata.h"


Automata newAutomata(int states[], char alphabet[], Transition transitions[], int start, int finals[]) {
  Automata a;
  a.states = states;
  a.alphabet = alphabet;
  a.transitions = transitions;
  a.start = start;
  a.finals = finals;

  return a;
}

Transition newTransition(int from, int to, char symbol) {
  Transition t;
  t.from = from;
  t.to = to;
  t.symbol = symbol;

  return t;
}

void printTransition(Transition t) {
  printf("%d --> '%c' --> %d", t.from, t.symbol, t.to);
}

void printAutomata(Automata a) {
  printf("Q = {");

  int i = 0;
  int state = a.states[0];
  while (state >= 0) {
    printf("%d, ", state);
    state = a.states[++i];
  }
  printf("}\n");

  printf("S = {");
  i = 0;
  char symbol = a.alphabet[0];
  while (symbol != '\0') {
    printf("%c, ", symbol);
    symbol = a.alphabet[++i];
  }
  printf("}\n");

  printf("q0 = %d\n", a.start);

  printf("F = {");
  i = 0;
  int final = a.finals[0];
  while (final >= 0) {
    printf("%d, ", final);
    final = a.finals[++i];
  }
  printf("}\n");

  printf("Delta = {\n");
  i = 0;
  Transition t = a.transitions[0];
  while (t.from >= 0) {
    printf("\t");
    printTransition(t);
    printf(" ,\n");
    t = a.transitions[++i];
  }
  printf("}\n");
}
