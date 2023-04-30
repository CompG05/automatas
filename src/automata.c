#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "automata.h"
#include "Set.h"

const int MAX_ALPHABET_SIZE = 127 - 32;
const char LAMBDA = '\\';
const int LAMBDA_CODE = 92 - 32;

int codeOf(char c) {
  return c - 32;
}

Automata newAutomata(int num_states, List *alphabet, Transition transitions[],
                     int start, List *finals) {
  // Pre: num_states > 0
  //      32 <= c <= 126 and c != 92 for all c in alphabet
  //      0 <= start < num_states
  //      0 <= f < num_states for all f in finals
  Automata a;
  a.num_states = num_states;
  a.alphabet = alphabet;
  a.transitions = transitions;
  a.start = start;
  a.finals = finals;

  a.transitions_table = (List **)malloc(num_states * sizeof(int *));
  for (int i = 0; i < num_states; i++) {
    a.transitions_table[i] = (Set *) malloc((MAX_ALPHABET_SIZE) * sizeof(Set)); // Space for all symbols + lambda
    for (int j = 0; j < MAX_ALPHABET_SIZE; j++)
      a.transitions_table[i][j] = *newSet();
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

Transition newTransition(int from, Set *to, char symbol) {
  Transition t;
  t.from = from;
  t.to = to;
  t.symbol = symbol;

  return t;
}

int runAutomata(Automata a, char str[]) {
  int state = a.start;
  Set outgoing;
  for (int i = 0; i < strlen(str); i++) {
    char symbol = str[i];
    outgoing = a.transitions_table[state][codeOf(symbol)];

    if (isEmpty(outgoing))
      return 0;

    state = listGet(asList(outgoing), 0);
  }

  return contains(*a.finals, state);
}


Automata toAFD(Automata a) {
  // Not implemented
  return newAutomata(0, newSet(), NULL, 0, newSet());
}

Set lClosure(Automata a, Set states) {
  Set *result = newSet();
  List resultList = asList(*result);
  Set *addedStates;
  int state;
  Set lAdjacents;
  int changed = 1;

  addAll(result, states);

  while (changed) {
    changed = 0;
    addedStates = newSet();
    for (int i = 0; i < size(*result); i++) {
      state = listGet(resultList, i);
      lAdjacents = a.transitions_table[state][LAMBDA_CODE];

      addAll(addedStates, lAdjacents);
    }

    int old_size = size(*result);
    addAll(result, *addedStates);
    if(old_size != size(*result)) changed = 1;
  }
  return *result;
}

Set move(Automata a, Set states, char symbol) {
  Set *result = newSet();
  List statesList = asList(states);
  int state;

  for (int i= 0; i < statesList.size; i++){
    state = listGet(statesList, i);
    Set moved = a.transitions_table[state][codeOf(symbol)];
    addAll(result, moved);
  }

  return *result;
}
