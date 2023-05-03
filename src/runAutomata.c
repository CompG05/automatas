#include <stdio.h>

#include "automata.h"
#include "readAutomata.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <automata_file> <string>\n", argv[0]);
        return 1;
    }
    Automata a = readAutomata(argv[1]);
    Automata aAFD = toAFD(a);
    printf("'%s' is %s\n",
           argv[2],
           runAutomata(aAFD, argv[2]) ? "accepted" : "rejected");
}