#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "automata.h"
#include "readAutomata.h"
#include "writeAutomata.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }
    Automata a = readAutomata(argv[1]);
    writeAutomata(toAFD(a), argv[2]);
}