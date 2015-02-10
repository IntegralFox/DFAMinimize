/* Main file for user interaction */
#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include "dfa.hpp"

int main(int argc, char** argv) {
	if (argc == 1) {
		std::cerr << "minimize: No DFA file specified" << std::endl;
		return 1;
	}

	try {
		// Open the DFA and create the DFA object
		std::string filename {argv[1]};
		std::ifstream dfaFile {filename};
		if (!dfaFile.is_open()) throw std::runtime_error {"Could not open file " + filename};
		DFA automaton {dfaFile};

		// Open the output file and output the original DFA in the dot language
		std::ofstream dotFile {filename + ".dot"};
		if (!dotFile.is_open()) throw std::runtime_error {"Could not open file " + filename + ".dot"};
		dotFile << automaton;

		// Open the output file and output the minimized DFA
		std::ofstream minDotFile {filename + "-min.dot"};
		if (!minDotFile.is_open()) throw std::runtime_error {"Could not open file " + filename + "-min.dot"};
		automaton.minimize();
		minDotFile << automaton;
	} catch (std::runtime_error e) {
		std::cerr << "minimize: " << e.what() << std::endl;
		return 2;
	}
}
