typedef struct Transition {
  int from;
  int to;
  char symbol;
} Transition;


typedef struct Automata {
  int *states;
  char *alphabet;
  Transition *transitions;
  int start;
  int *finals;
} Automata;


Automata newAutomata(int states[], char alphabet[], Transition transitions[], int start, int finals[]);

Transition newTransition(int from, int to, char symbol);

void printTransition(Transition t);

void printAutomata(Automata a);
