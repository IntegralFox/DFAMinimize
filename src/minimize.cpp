/* Main file for user interaction */
#include <iostream>
#include <fstream>
#include "dfa.hpp"

int main(int argc, char** argv) {
	DFA automaton {std::cin};
	std::cout << automaton;
	automaton.minimize();
	std::cout << automaton;
}
