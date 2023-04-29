#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "automata.h"

const int MAX_ALPHABET_SIZE = 127 - 32;

int codeOf(char c) {
  if (c == 10) // '\n' representing lambda
    return MAX_ALPHABET_SIZE;
  else
    return c - 32;
}

Automata newAutomata(int num_states, List *alphabet, Transition transitions[],
                     int start, List *finals) {
  // Pre: num_states > 0
  //      32 <= c <= 126 or c = 10 for all c in alphabet
  //      start <= num_states
  //      0 <= f < num_states for all f in finals
  Automata a;
  a.num_states = num_states;
  a.alphabet = alphabet;
  a.transitions = transitions;
  a.start = start;
  a.finals = finals;

  a.transitions_table = (List **)malloc(num_states * sizeof(int *));
  for (int i = 0; i < num_states; i++) {
    a.transitions_table[i] = (List *)malloc((MAX_ALPHABET_SIZE + 1) * sizeof(List)); // Space for all symbols + lambda
    for (int j = 0; j < 126 - 32; j++)
      a.transitions_table[i][j] = *newList();
  }

  Transition transition = transitions[0];
  int i = 0;
  while (transition.from >= 0) {
    a.transitions_table[transition.from][codeOf(transition.symbol)] =
        *transition.to;
    transition = transitions[++i];
  }

  return a;
}

Transition newTransition(int from, List *to, char symbol) {
  Transition t;
  t.from = from;
  t.to = to;
  t.symbol = symbol;

  return t;
}

int runAutomata(Automata a, char str[]) {
  int state = a.start;
  List outgoing;
  for (int i = 0; i < strlen(str); i++) {
    char symbol = str[i];
    outgoing = a.transitions_table[state][codeOf(symbol)];

    if (isEmpty(outgoing))
      return 0;

    state = get(outgoing, 0);
  }

  return contains(*a.finals, state);
}

void printTransition(Transition t) {
  if (t.symbol == '\n')
    printf("%d --> '' --> [", t.from);
  else
    printf("%d --> '%c' --> [", t.from, t.symbol);
  for (int i = 0; i < t.to->size - 1; i++) {
    printf("%d, ", get(*t.to, i));
  }
  printf("%d]", get(*t.to, t.to->size - 1));
}

void printAutomata(Automata a) {
  printf("Q = {");
  for (int state = 0; state < a.num_states - 1; state++) {
    printf("%d, ", state);
  }
  printf("%d}\n", a.num_states - 1);

  printf("S = {");
  for (int i = 0; i < a.alphabet->size - 1; i++) {
    printf("'%c', ", get(*a.alphabet, i));
  }
  printf("'%c'}\n", get(*a.alphabet, a.alphabet->size - 1));

  printf("q0 = %d\n", a.start);

  if (a.finals->size == 0) {
    printf("F = {}\n");
  } else {
    printf("F = {");
    for (int i = 0; i < a.finals->size - 1; i++) {
      printf("%d, ", get(*a.finals, i));
    }
    printf("%d}\n", get(*a.finals, a.finals->size - 1));
  }

  printf("Delta = {\n");

  int i = 0;
  Transition t = a.transitions[0];
  while (t.from >= 0) {
    printf("\t");
    printTransition(t);
    printf(" ,\n");
    t = a.transitions[++i];
  }
  printf("}\n");
}

Automata toAFD(Automata a) {
  // Not implemented
  return newAutomata(0, newList(), NULL, 0, newList());
}

List closure(Automata a, List states) {
  // Not implemented
  return *newList();
}

List move(Automata a, List states, char symbol) {
  // Not implemented
  return *newList();
}
