/* DFA Implementation */

#include "dfa.hpp"
#include <string>
#include <sstream>
#include <stdexcept>

DFA::DFA(std::istream& input) {
	std::string line, token;
	std::stringstream ssline {};

	// Get the states fromt the first line
	std::getline(input, line);
	ssline.str(line);
	while (ssline >> token) state.insert(token);

	// Get the alphabet from the second line
	std::getline(input, line);
	ssline.clear();
	ssline.str(line);
	while (ssline >> token) alphabet.insert(token);

	// Get the start state
	std::getline(input, start);

	// Get the final states
	std::getline(input, line);
	ssline.clear();
	ssline.str(line);
	while (ssline >> token) final.insert(token);

	// Set the transitions in the transitions table
	unsigned int count = 0;
	while (std::getline(input, line)) {
		ssline.clear();
		ssline.str(line);
		std::string a, symbol, b;
		ssline >> a >> symbol >> b;
		if (
			state.find(a) == state.end() ||
			state.find(b) == state.end() ||
			alphabet.find(symbol) == state.end()
		) {
			throw std::domain_error {"Transition rule contains invalid "
				"state(s) or symbol: " + line};
		}
		transMap[a][symbol] = b;
		++count;
	}

	// Throw exception if there aren't enough rules
	if (count != state.size() * alphabet.size()) {
		throw std::length_error {"There are not the appropriate amount of "
			"transition rules for the FA to be deterministic"};
	}
}

// Output the DFA in the graphviz dot language
void DFA::dot(std::ostream& output) {
	output << "digraph DFA {\n";
	for (const auto& a : transMap) {
		for (const auto& b : a.second) {
			output << "\t" << a.first << " -> " << b.first << " [label = " <<
				b.second << "];\n";
		}
	}
	output << "}\n" << std::flush;
}
