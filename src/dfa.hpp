/* Header for DFA class */
#ifndef DFA_HEADER
#define DFA_HEADER

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

class DFA {
	std::set<std::string> states;
	std::set<std::string> alphabet;
	std::string startState;
	std::set<std::string> finalStates;
	std::map<std::string, std::map<std::string, std::string>> transition;

public:
	DFA() {}
	DFA(std::istream&);
	void dot(std::ostream&);
	std::ostream& operator<<(std::ostream&);
	void minimize();
	bool inSetofSets(const std::string&, const std::set<std::set<std::string>>&);
};

#endif
