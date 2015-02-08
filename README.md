# DFAMinimize
DFA Minimizer in C++11

## Building
Run `clang++ --std=c++11 -o minimize src/*.cpp` or similar.

## Usage
Run `./minimize <filename>`. Two graphviz dot files will be generated with the
suffixes `.dot` and `-min.dot` representing the original DFA and its
minimization, respectively.

Users of \*nix systems with graphviz and imgagemagick installed and configured
in their path can run `./mindisp.sh <filename>` to have the DFAs displayed
automatically after conversion to dot language.

## File Format
DFA files are plaintext representations of the following form:

* A line of whitespace-delimited state identifiers
* A line of whitespace-delimited alphabet symbols
* A line containing the start state identifier
* A line of whitespace-delimited accept states
* M\*N lines of state transitions of the form `<state> <symbol> <state>`
