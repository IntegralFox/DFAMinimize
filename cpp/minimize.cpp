/* Main file for user interaction */
#include <iostream>
#include <fstream>
#include "dfa.hpp"

int main(int argc, char** argv) {
	DFA automaton {std::cin};
	automaton.dot(std::cout);
	automaton.minimize();
	automaton.dot(std::cout);
}
