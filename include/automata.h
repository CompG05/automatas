#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "LinkedList.h"

typedef struct Transition {
  int from;
  List *to;
  char symbol;
} Transition;


typedef struct Automata {
  int num_states;
  List *alphabet;
  Transition *transitions;
  List **transitions_table;
  int start;
  List *finals;
} Automata;


Automata newAutomata(int num_states, List *alphabet, Transition transitions[], int start, List *finals);

Transition newTransition(int from, List *to, char symbol);

int runAutomata(Automata a, char str[]);

void printTransition(Transition t);

void printAutomata(Automata a);

Automata toAFD(Automata a);

List closure(Automata a, List states);

List move(Automata a, List states, char symbol);

#endif
