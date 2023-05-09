# automatas

This project requires cmake for building.

For building instructions, check out the [build instructions](build_instructions.txt).


There are 2 main executables, and some testing executables built into the bin/ directory:

- bin/toAFD: Constructs a DFA from a given automata file (.dot)
- bin/runAutomata: Given an automata file (.dot) and a string, check if the automata accepts the string
- bin/test{AFNtoAFD,RunAutomata,ReadAutomata,WriteAutomata}: scripts to test the respective functionality
- bin/testIntegrity{1,2,3}: scripts to test all the functionality

There are some automata .dot files in test/files/ directory necessary for the tests above.
For them to properly find the files, you must run the executables from the root directory of the project (automata/).
