/* Main file for user interaction */
#include <iostream>
#include <fstream>
#include <memory>
#include "dfa.hpp"

int main(int argc, char** argv) {
	if (argc == 1) {
		std::cerr << "No DFA file specified." << std::endl;
		return 0;
	}

	// Acquire the files
	std::string filename {argv[1]};
	std::ifstream dfaFile {filename};
	std::ofstream dotFile {filename + ".dot"}, minDotFile {filename + "-min.dot"};

	// Create a DFA object and minimize
	DFA automaton {dfaFile};
	dotFile << automaton;
	automaton.minimize();
	minDotFile << automaton;
}
