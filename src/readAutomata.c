#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "automata.h"
#include "readAutomata.h"

int parseInitial(char *s) {
  int initial;

  sscanf(s, "inic->q%d", &initial);

  return initial;
}

void parseTransitions(char *s, Transition result[], int *n_transitions) {
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
        break;
      }
    }
    if (added) {
      break;
    } else {
      result[(*n_transitions)++] = newTransition(from, newSetFromArray((int []) {to}, 1), symbol);
    }
  }
}

int parseFinal(char *s) {
  int final;

  sscanf(s, "q%d[shape=doublecircle]", &final);

  return final;
}

void updateNumStates(char s[], int *numStates) {
  // Pre: s matches a transition line
  int a, b;

  sscanf(s, "q%d->q%d [label=\"%s\"];", &a, &b, (char *) NULL);

  if (a >= *numStates) *numStates = a + 1;
  if (b >= *numStates) *numStates = b + 1;
}

void updateAlphabet(char *s, Set *alphabet) {
  // Pre: s matches a transition line
  int a;
  int b;
  char label[200];

  sscanf(s, "q%d->q%d [label=\"%199[^\"]\"];", &a,&b, label);

  for (int i = 0; i < strlen(label); i++) {
    char c = label[i];
    if (c == ',' || c == '_') continue;

    add(alphabet, c);
  }
}

Automata readAutomata(char filename[]) {
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

  while ((read = getline(&line, &len, fp)) != -1) {
    // printf("%s\n", line);
    if (!regexec(&initial_regex, line, 0, NULL, 0)) { // If the line defines an initial state
      start = parseInitial(line);
      if (start >= numStates)
        numStates = start + 1;
    } else if (!regexec(&final_regex, line, 0, NULL, 0)) { // If the line defines a final state
      final = parseFinal(line);
      add(finals, final);
      if (final >= numStates)
        numStates = final + 1;
    } else if (!regexec(&transition_regex, line, 0, NULL, 0)) { // If it defines a transition
      updateNumStates(line, &numStates);
      updateAlphabet(line, alphabet);
    }
  }
  free(line);
  Transition *transitions = (Transition *) malloc((numStates * size(*alphabet) + 1) * sizeof(Transition));

  rewind(fp);
  while ((read = getline(&line, &len, fp)) != -1) {
    if (!regexec(&transition_regex, line, 0, NULL, 0)) { // If it defines a transition
      parseTransitions(line, transitions, &n_transitions);
    }
  }
  free(line);
  fclose(fp);

  transitions[n_transitions] = newTransition(-1, newSet(), ' ');

  Automata automata = newAutomata(numStates, alphabet, transitions, start, finals);
  free(transitions);
  return automata;
}
