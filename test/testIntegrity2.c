#include <stdio.h>

#include "automata.h"
#include "readAutomata.h"
#include "writeAutomata.h"


int main() {
    printf("Testing automata 2\n\n");

    printf("Reading automata from test/files/automataIT2.dot...\n");
    Automata a = readAutomata("test/files/automataIT2.dot");

    printf("Determinizing automata...\n");
    Automata aDFA = toAFD(a);
    freeAutomata(&a);

    printf(
            "Writing deterministic automata to test/files/dfa_automataIT2.dot...\n");
    writeAutomata(aDFA, "test/files/dfa_automataIT2.dot");

    printf("Testing strings...\n");
    char *validStrings2[] = {"c", "babab", "bbc"};
    char *invalidStrings2[] = {"aaab", "baaa", ""};

    for (int i = 0; i < 3; i++) {
        printf("\"%s\" is %s (expected: accepted)\n", validStrings2[i],
               runAutomata(aDFA, validStrings2[i]) ? "accepted" : "rejected");
    }
    for (int i = 0; i < 3; i++) {
        printf("\"%s\" is %s (expected: rejected)\n", invalidStrings2[i],
               runAutomata(aDFA, invalidStrings2[i]) ? "accepted" : "rejected");
    }
    freeAutomata(&aDFA);
}
