typedef struct Transition {
  int from;
  int to;
  char symbol;
} Transition;


typedef struct Automata {
  int num_states;
  char *alphabet;
  Transition *transitions;
  int **transitions_table;
  int start;
  int *finals;
} Automata;


Automata newAutomata(int num_states, char alphabet[], Transition transitions[], int start, int finals[]);

Transition newTransition(int from, int to, char symbol);

int runAutomata(Automata a, char str[]);

void printTransition(Transition t);

void printAutomata(Automata a);
