#include <stdio.h>

#include "automata.h"
#include "readAutomata.h"


int main() {
    Automata a = readAutomata("test/files/test_read_autom.dot");
    printf("Automata read from file:\n");
    printAutomata(a);
}