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
	while (ssline >> token) states.insert(token);

	// Get the alphabet from the second line
	std::getline(input, line);
	ssline.clear();
	ssline.str(line);
	while (ssline >> token) alphabet.insert(token);

	// Get the start state
	std::getline(input, startState);

	// Get the final states
	std::getline(input, line);
	ssline.clear();
	ssline.str(line);
	while (ssline >> token) finalStates.insert(token);

	// Set the transitions in the transitions table
	unsigned int count = 0;
	while (std::getline(input, line)) {
		ssline.clear();
		ssline.str(line);
		std::string a, symbol, b;
		ssline >> a >> symbol >> b;
		if (
			states.find(a) == states.end() ||
			states.find(b) == states.end() ||
			alphabet.find(symbol) == alphabet.end()
		) {
			throw std::domain_error {"Transition rule contains invalid "
				"state(s) or symbol: " + line};
		}
		transition[a][symbol] = b;
		++count;
	}

	// Throw exception if there aren't enough rules
	if (count != states.size() * alphabet.size()) {
		throw std::length_error {"There are not the appropriate amount of "
			"transition rules for the FA to be deterministic"};
	}
}

// Output the DFA in the graphviz dot language
void DFA::dot(std::ostream& output) const {
	output << "digraph DFA {\n\trankdir=LR;\n";
	output << "\tnode [shape = none] [width = 0] [fixedsize = true]; \"\";\n";
	output << "\tnode [shape = doublecircle] [fixedsize = false];";
	for (const auto& state: finalStates) {
		output << " \"" << state << "\"";
	}
	output << ";\n\tnode [shape = circle];\n";
	output << "\t\"\" -> \"" << startState << "\";\n";
	for (const auto& a : transition) {
		for (const auto& b : a.second) {
			output << "\t\"" << a.first << "\" -> \"" << b.second << "\" "
				"[label = \"" << b.first << "\"];\n";
		}
	}
	output << "}\n" << std::flush;
}

std::ostream& operator<<(std::ostream& output, const DFA& dfa) {
	dfa.dot(output);
	return output;
}

// Collapses the DFA into its minimum representation
void DFA::minimize() {
	// Distinction table
	std::map<std::string, std::map<std::string, bool>> distinct {};

	// Set two elements as distinct when one is final and the other is not
	for (const auto& a : states) {
		for (const auto& b : states) {
			if (a == b) continue; // Don't compare an element to itself
			bool aFinal = finalStates.find(a) != finalStates.end();
			bool bFinal = finalStates.find(b) != finalStates.end();
			distinct[a][b] = aFinal ^ bFinal;
		}
	}

	// Iterate over the distinct table until no new elements are distinct
	bool newlyDistinctElement;
	do {
		newlyDistinctElement = false;
		for (const auto& a : states) {
			for (const auto& b : states) {
				if (a == b || distinct[a][b]) continue;
				for (const auto& s : alphabet) {
					// Get the transition state for each state
					auto aD = transition[a][s];
					auto bD = transition[b][s];
					if (aD != bD && distinct[aD][bD]) {
						distinct[a][b] = true;
						newlyDistinctElement = true;
					}
				}
			}
		}
	} while (newlyDistinctElement);

	// Merge indistinguishable states by grouping them into sets within a set
	std::set<std::set<std::string>> mergedStateSets {};
	for (const auto& s : states) {
		// Skip iteration if this state has been previously merged
		if (inSetofSets(s, mergedStateSets)) continue;

		// Create a new set and put indistinguishable states in it
		std::set<std::string> newSet {s};
		for (const auto& t : states) {
			if (s != t && !distinct[s][t]) {
				newSet.insert(t);
			}
		}
		mergedStateSets.insert(newSet);
	}

	// From the merged sets, make new identifiers and identify the start state
	// and the final states
	std::set<std::string> newStates {};
	std::string newStartState {};
	std::set<std::string> newFinalStates {};
	std::map<std::string, std::map<std::string, std::string>> newTransition {};

	for (const auto& set : mergedStateSets) {
		bool isStart = false;
		bool isFinal = false;

		// Construct a new state identifier
		std::string newState = "{ ";
		for (const auto& state : set) {
			if (state == startState) isStart = true;
			if (finalStates.find(state) != finalStates.end()) isFinal = true;
			newState += state + " ";
		}
		newState += "}";

		// Add to the set of new states
		newStates.insert(newState);
		if (isStart) newStartState = newState;
		if (isFinal) newFinalStates.insert(newState);
	}

	// Create the new transtitions by mapping the original state transitions
	// onto the new merged states
	for (const auto& state : states) {
		for (const auto& symbol : alphabet) {
			std::string transitionState        = transition[state][symbol];
			std::string mergedState            = mergedStateFor(state, newStates);
			std::string mergedTransitionState  = mergedStateFor(transitionState, newStates);
			newTransition[mergedState][symbol] = mergedTransitionState;
		}
	}

	// Replace the member attributes with the new ones
	states      = std::move(newStates);
	startState  = std::move(newStartState);
	finalStates = std::move(newFinalStates);
	transition  = std::move(newTransition);
}

/* Returns whether a state is contained in one of the sets of states in a set */
bool DFA::inSetofSets(const std::string& s, const std::set<std::set<std::string>>& stateSets) {
	for (const auto& set : stateSets) {
		for (const auto& state : set) {
			if (s == state) return true;
		}
	}
	return false;
}

/* Returns the merged state that contains the specified original state */
std::string DFA::mergedStateFor(const std::string& s, const std::set<std::string>& states) {
	for (const auto& mergedState : states) {
		if (mergedState.find(s) != std::string::npos) return mergedState;
	}
	return "";
}
