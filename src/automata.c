#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "automata.h"
#include "Set.h"

const int MAX_ALPHABET_SIZE = 127 - 32;
const char LAMBDA = '_';
const int LAMBDA_CODE = '_' - 32;

int codeOf(char c) {
  return c - 32;
}

Automata newAutomata(int num_states, Set *alphabet, Transition transitions[],
                     int start, Set *finals) {
  // Pre: num_states > 0
  //      32 <= c <= 126 and c != LAMBDA for all c in alphabet
  //      0 <= start < num_states
  //      0 <= f < num_states for all f in finals
  Automata a;
  a.num_states = num_states;
  a.alphabet = alphabet;
  a.transitions = transitions;
  a.start = start;
  a.finals = finals;

  a.transitions_table = (Set **)malloc(num_states * sizeof(int *));
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
  //declare local variables

  List alphabet = asList(*a.alphabet);
  int already_counted = 0;
  int M_position = 0;


  //initialize Set of sets of states (T) and  Set of transitions (transitions)

  Set* T = (Set*) malloc((int) pow(2,a.num_states) * sizeof(Set));
  int size_t = 0;
  Transition* transitions = (Transition*) malloc((int) pow(2,a.num_states) * size(*a.alphabet) * sizeof(Transition));
  int size_transitions = 0;


  //calculate initial-state's lClosure and insert it in T

  Set *start_set = newSetFromArray((int[]) {a.start}, 1);
  T[0] = lClosure(a,*start_set);
  size_t++;

  for(int i=0; i<size_t; i++){                                    //for each S in T
    for (int j=0; j<size(*a.alphabet); j++){                  //for each alphabet symbol
      char symbol = (char) listGet(alphabet, j);
      Set M = lClosure(a, move(a, T[i], symbol));    //create M=lClosure(move(S,symbol))

      already_counted = 0;                                        //check whether M is in T or not
      for(int z=0; z<size_t; z++){
        if (equals(M,T[z])){
          already_counted = 1;
          M_position = z;
        }
      }
      if(!already_counted) {                                      //if M wasn't in T already
        M_position = size_t;
        T[M_position] = M;                                        //insert M in T
        size_t++;
      }

      Set *to = newSetFromArray((int[]) {M_position}, 1);
      transitions[size_transitions++] = newTransition(i, to, symbol);            //define delta transition (i --'symbol'-> {M_position})
    }
  }

  transitions[size_transitions++] = newTransition(-1, newSet(), ' ');  //insert transition's final mark

  Set *finals = newSet();
  for (int i=0; i<size_t; i++){                                           //for each S in T
    if(!isEmpty(intersection(*a.finals, T[i]))){                //if its intersection with a.finals is not empty
      add(finals, i);                                           //insert it in new finals set
    }
  }


  // return deterministic automata
  return newAutomata(size_t, a.alphabet, transitions, 0, finals);
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



void printTransition(Transition t) {
  if (t.symbol == '_')
    printf("%d --> 'λ' --> [", t.from);
  else
    printf("%d --> '%c' --> [", t.from, t.symbol);
  List arrivalList = asList(*t.to);
  for (int i = 0; i < size(*t.to) - 1; i++) {
    printf("%d, ", listGet( arrivalList, i));
  }
  printf("%d]", listGet(asList(*t.to), size(*t.to) - 1));
}

void printAutomata(Automata a) {
  printf("Q = {");
  for (int state = 0; state < a.num_states - 1; state++) {
    printf("%d, ", state);
  }
  printf("%d}\n", a.num_states - 1);

  List alphabetList = asList(*a.alphabet);
  printf("S = {");
  for (int i = 0; i < alphabetList.size - 1; i++) {
    printf("'%c', ", listGet(alphabetList, i));
  }
  printf("'%c'}\n", listGet(alphabetList, alphabetList.size - 1));

  printf("q0 = %d\n", a.start);


  if (size(*a.finals) == 0) {
    printf("F = {}\n");
  } else {
    List finalsList = asList(*a.finals);
    printf("F = {");
    for (int i = 0; i < finalsList.size - 1; i++) {
      printf("%d, ", listGet(finalsList, i));
    }
    printf("%d}\n", listGet(finalsList, finalsList.size - 1));
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


void freeAutomata(Automata *a) {
  free(a->alphabet);
  for (int i = 0; i < a->num_states; i++) {
    free(a->transitions_table[i]);
  }
  free(a->transitions_table);
  free(a->finals);
}
