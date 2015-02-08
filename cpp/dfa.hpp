/* Header for DFA class */
#ifndef DFA_HEADER
#define DFA_HEADER

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

class DFA {
	std::set<std::string> state;
	std::set<std::string> alphabet;
	std::string start;
	std::set<std::string> final;
	std::map<std::string, std::map<std::string, std::string>> transMap;

public:
	DFA() {}
	DFA(std::istream&);
	void dot(std::ostream&);
};

#endif
