#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "automata.h"

void writeAutomata(Automata a, char filename[]){
  List destStates;
  FILE *f = fopen(filename, "w");
  if (f == NULL)
    exit(EXIT_FAILURE);

  fputs("digraph{\n", f);
  fputs("inic[shape=point];\n", f);
  fprintf(f ,"inic->q%d;\n\n", a.start);

  int mark[a.num_states];
  for (int i = 0; i < a.num_states; i++)
    mark[i] = 0;

  for (int state = 0; state < a.num_states; state++) {
    for (int otherState = 0; otherState < a.num_states; otherState++) {
      if (state == otherState) {
        // Ensure loops are checked only once
        if (mark[state]) continue;
        else mark[state] = 1;
      }
      Transition t = a.transitions[0];
      int k = 0;

      List *symbols = newList();
      while (t.from >= 0) {
        destStates = asList(*t.to);
        if(t.from == state && listContains(destStates, otherState))
          listInsert(symbols, symbols->size, t.symbol);

        t = a.transitions[++k];
      }

      if(listIsEmpty(*symbols))
        continue;

      fprintf(f, "q%d->q%d [label=\"", state, otherState);
      for(int i=0; i<symbols->size-1; i++){
        fprintf(f, "%c,", listGet(*symbols, i));
      }
      fprintf(f, "%c\"];\n", listGet(*symbols, symbols->size-1));
    }
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