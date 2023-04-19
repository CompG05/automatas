#include <stdio.h>

#include "automata.h"


int codeOf(char c) {
    return c - 32;
}

Automata newAutomata(int num_states, char alphabet[], Transition transitions[], int start, int finals[]) {
  Automata a;
  a.num_states = num_states;
  a.alphabet = alphabet;
  a.transitions = transitions;
  a.transitions_table[num_states][126-32]; // 126 - 32 is the maximum number of symbols in the alphabet
  a.start = start;
  a.finals = finals;

  Transition transition = transitions[0];
  int i = 0;
    while (transition.from >= 0) {
        a.transitions_table[transition.from][transition.symbol - 32] = transition.to;
        transition = transitions[++i];
    }

  return a;
}

Transition newTransition(int from, int to, char symbol) {
  Transition t;
  t.from = from;
  t.to = to;
  t.symbol = symbol;

  return t;
}

int runAutomata(Automata a, char str[]){

}

void printTransition(Transition t) {
  printf("%d --> '%c' --> %d", t.from, t.symbol, t.to);
}

void printAutomata(Automata a) {
  printf("Q = {");

  for (int state = 0; state < a.num_states; state++) {
    printf("%d, ", state);
  }
  printf("%d}\n", a.num_states);

  printf("S = {");
  int i = 0;
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
