# automatas

This project requires cmake for building.

For building instructions, check out the [building instructions](building_instructions.txt).


There are 2 main executables, and 4 testing executables built into the bin/ directory:

- bin/toAFD: Constructs a DFA from a given automata file (.dot)
- bin/runAutomata: Given an automata file (.dot) and a string, check if the automata accepts the string
- bin/test{AFNtoAFD,RunAutomata,ReadAutomata,WriteAutomata}: scripts to test the respective functionality
