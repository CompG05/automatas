#include <stdio.h>

#include "automata.h"
#include "readAutomata.h"
#include "writeAutomata.h"


int main() {
    printf("Testing automata 3\n\n");

    printf("Reading automata from test/files/automataIT3.dot...\n");
    Automata a = readAutomata("test/files/automataIT3.dot");

    printf("Determinizing automata...\n");
    Automata aDFA = toAFD(a);
    freeAutomata(&a);

    printf("Writing deterministic automata to test/files/dfa_automataIT3.dot...\n");
    writeAutomata(aDFA, "test/files/dfa_automataIT3.dot");

    printf("Testing strings...\n");
    char *validStrings3[] = {"", "0022", "1"};
    char *invalidStrings3[] = {"10", "020", "3"};

    for (int i = 0; i < 3; i++) {
        printf("\"%s\" is %s (expected: accepted)\n", validStrings3[i],
               runAutomata(aDFA, validStrings3[i]) ? "accepted" : "rejected");
    }
    for (int i = 0; i < 3; i++) {
        printf("\"%s\" is %s (expected: rejected)\n", invalidStrings3[i],
               runAutomata(aDFA, invalidStrings3[i]) ? "accepted" : "rejected");
    }
    freeAutomata(&aDFA);
}
