#include <stdio.h>

#include "automata.h"
#include "readAutomata.h"
#include "writeAutomata.h"


int main() {
    printf("Testing automata 1\n\n");

    printf("Reading automata from test/files/automataIT1.dot...\n");
    Automata a = readAutomata("test/files/automataIT1.dot");

    printf("Determinizing automata...\n");
    Automata aDFA = toAFD(a);
    freeAutomata(&a);

    printf(
            "Writing deterministic automata to test/files/dfa_automataIT1.dot...\n");
    writeAutomata(aDFA, "test/files/dfa_automataIT1.dot");

    printf("Testing strings...\n");
    char *validStrings[] = {"0", "0110", "100110101"};
    char *invalidStrings[] = {"01", "", "01101011"};

    for (int i = 0; i < 3; i++) {
        printf("\"%s\" is %s (expected: accepted)\n", validStrings[i],
               runAutomata(aDFA, validStrings[i]) ? "accepted" : "rejected");
    }
    for (int i = 0; i < 3; i++) {
        printf("\"%s\" is %s (expected: rejected)\n", invalidStrings[i],
               runAutomata(aDFA, invalidStrings[i]) ? "accepted" : "rejected");
    }
    freeAutomata(&aDFA);
}
