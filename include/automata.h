#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "LinkedList.h"
#include "Set.h"

typedef struct Transition {
  int from;
  Set *to;
  char symbol;
} Transition;


typedef struct Automata {
  int num_states;
  Set *alphabet;
  Transition *transitions;
  Set **transitions_table;
  int start;
  Set *finals;
} Automata;


Automata newAutomata(int num_states, Set *alphabet, Transition transitions[], int start, Set *finals);

Transition newTransition(int from, Set *to, char symbol);

int runAutomata(Automata a, char str[]);

void printTransition(Transition t);

void printAutomata(Automata a);

Automata toAFD(Automata a);

Set lClosure(Automata a, Set states);

Set move(Automata a, Set states, char symbol);

List asList(Set set);

void freeAutomata(Automata *a);

#endif
