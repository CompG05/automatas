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

    printf("\nPress any key to continue\n");
    getc(stdin);
    fflush(stdout);
    printf("\n\n");

    printf("Testing automata 2\n\n");

    printf("Reading automata from test/files/automataIT2.dot...\n");
    a = readAutomata("test/files/automataIT2.dot");

    printf("Determinizing automata...\n");
    aDFA = toAFD(a);
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

    printf("\nPress any key to continue\n");
    getc(stdin);
    fflush(stdout);
    printf("\n\n");


    printf("Testing automata 3\n\n");

    printf("Reading automata from test/files/automataIT3.dot...\n");
    a = readAutomata("test/files/automataIT3.dot");

    printf("Determinizing automata...\n");
    aDFA = toAFD(a);
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
