#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "automata.h"
#include "readAutomata.h"

int parseInitial(char *s) {
  printf("Reading initial state\n");
  int initial;

  sscanf(s, "inic->q%d", &initial);
  printf("Initial state found: %d\n", initial);

  return initial;
}

void parseTransitions(char *s, Transition result[], int *n_transitions) {
  printf("Reading transition\n");
  int from;
  int to;
  char symbols[200];
  int added = 0;
  Transition t;

  sscanf(s, "q%d->q%d [label=\"%199[^\"]\"]", &from, &to, symbols);

  // For symbol in symbols
  for (int i = 0; i < strlen(symbols); i++) {
    char symbol = symbols[i];
    if (symbol == ',') continue;

    added = 0;
    // For t in result
    for (int j = 0; j < *n_transitions; j++) {
      t = result[j];

      if (t.from == from && t.symbol == symbol) {
        add(t.to, to);
        added = 1;
        printf("Transition added: %d->%d [%c]\n", from, to, symbol);
        break;
      }
    }
    if (added) {
      break;
    } else {
      result[(*n_transitions)++] = newTransition(from, newSetFromArray((int []) {to}, 1), symbol);
      printf("Transition added: %d->%d [%c]\n", from, to, symbol);
    }
  }
}

int parseFinal(char *s) {
  printf("Reading final state\n");
  int final;

  sscanf(s, "q%d[shape=doublecircle]", &final);
  printf("Final state added: %d\n", final);

  return final;
}

void updateNumStates(char s[], int *numStates) {
  // Pre: s matches a transition line
  printf("Updating states\n");
  int a, b;

  sscanf(s, "q%d->q%d [label=\"%s\"];", &a, &b, (char *) NULL);

  if (a >= *numStates) *numStates = a + 1;
  if (b >= *numStates) *numStates = b + 1;
  printf("Number of states: %d\n", *numStates);
}

void updateAlphabet(char *s, Set *alphabet) {
  // Pre: s matches a transition line
  printf("Updating alphabet\n");
  int a;
  int b;
  char label[200];

  sscanf(s, "q%d->q%d [label=\"%199[^\"]\"];", &a,&b, label);

  for (int i = 0; i < strlen(label); i++) {
    char c = label[i];
    if (c == ',') continue;

    add(alphabet, c);
    printf("Symbol added: %c\n", c);
  }
}

Automata readAutomata(char filename[]) {
  printf("Reading from %s\n", filename);
  FILE *fp;
  char *line;
  size_t len;
  ssize_t read;

  regex_t initial_regex;
  regex_t transition_regex;
  regex_t final_regex;

  regcomp(&initial_regex, "inic->q[0-9]+", REG_EXTENDED);
  regcomp(&transition_regex, "q[0-9]+->q[0-9]+ \\[label=\".(,.)*\"]", REG_EXTENDED);
  regcomp(&final_regex, "q[0-9]+\\[shape=doublecircle]", REG_EXTENDED);

  int numStates = 0;
  Set *alphabet = newSet();
  int n_transitions = 0;
  int start;
  int final;
  Set *finals = newSet();

  fp = fopen(filename, "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  printf("File opened\n");

  while ((read = getline(&line, &len, fp)) != -1) {
    // printf("%s\n", line);
    if (!regexec(&initial_regex, line, 0, NULL, 0)) { // If the line defines an initial state
      printf("Line matched initial (%s)\n", line);
      start = parseInitial(line);
      if (start >= numStates)
        numStates = start + 1;
    } else if (!regexec(&final_regex, line, 0, NULL, 0)) { // If the line defines a final state
      printf("Line matched final (%s)\n", line);
      final = parseFinal(line);
      add(finals, final);
      if (final >= numStates)
        numStates = final + 1;
    } else if (!regexec(&transition_regex, line, 0, NULL, 0)) { // If it defines a transition
      printf("Line matched transition (%s)\n", line);
      updateNumStates(line, &numStates);
      updateAlphabet(line, alphabet);
    }
  }
  Transition *transitions = (Transition *) malloc((numStates * size(*alphabet) + 1) * sizeof(Transition));

  rewind(fp);
  while ((read = getline(&line, &len, fp)) != -1) {
    if (!regexec(&transition_regex, line, 0, NULL, 0)) { // If it defines a transition
      printf("Adding transition\n");
      parseTransitions(line, transitions, &n_transitions);
    }
  }

  transitions[n_transitions] = newTransition(-1, newSet(), ' ');

  return newAutomata(numStates, alphabet, transitions, start, finals);
}
