#include <stdlib.h>
#include <stdio.h>

#include "automata.h"

int main() {
  int states[] = {0, 1, 2, -1};
  char *alphabet = "01\0";
  Transition transitions[] = {
    newTransition(0, 2, '0'),
    newTransition(0, 1, '1'),
    newTransition(1, 2, '0'),
    newTransition(1, 1, '1'),
    newTransition(2, 2, '0'),
    newTransition(2, 1, '1'),
    newTransition(-1, -1, '\0')
  };
  int start = 0;
  int final[] = {0, 1, -1};

  Automata a = newAutomata(states, alphabet, transitions, start, final);

  printAutomata(a);
}
