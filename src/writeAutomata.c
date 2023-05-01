#include <stdlib.h>
#include <stdio.h>

#include "automata.h"

void writeAutomata(Automata a, char filename[]){
  FILE *f = fopen(filename, "w");
  if (f == NULL)
    exit(EXIT_FAILURE);

  fputs("digraph{\n", f);
  fputs("inic[shape=point];\n", f);
  fprintf(f ,"inic->q%d;\n\n", a.start);

//  for (int state = 0; state < a.num_states; state++) {
//    for (int otherState = state+1; otherState < a.num_states; otherState++) {
//      Transition t = a.transitions[0];
//      int k = 0;
//
//      List *symbols = newList();
//      while (t.from >= 0) {
//
//      }
//    }
//  }

  Transition t = a.transitions[0];
  int state;
  int state2;
  int k = 0;
  int k2 = 0;
  List destStates;
  List destStates2;

  while (t.from >= 0) {
    List *symbols = newList();
    listInsert(symbols, t.symbol);

    // For state in destStates
    destStates = asList(*t.to);
    for (int i = 0; i < destStates.size; i++) {
      state = listGet(destStates, i);

      //For every following transition
      Transition t2 = a.transitions[k+1];
      while(t2.from>=0){
        if(t.from == t2.from){
          destStates2 = asList(*t2.to);
          if (listContains(destStates2, state)) listInsert(symbols, t2.symbol);
        }
      }

      fprintf(f, "q%d->q%d [label=\"%c\"];\n", t.from, state, t.symbol);
    }

    t = a.transitions[++k];
  }

  fputs("\n", f);

  List finals = asList(*a.finals);
  int final;
  for (int i = 0; i < finals.size; i++){
    final = listGet(finals, i);
    fprintf(f, "q%d[shape=doublecircle];\n", final);
  }

  fputs("}", f);

}