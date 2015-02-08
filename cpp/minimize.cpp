/* Main file for user interaction */
#include <iostream>
#include <fstream>
#include "dfa.hpp"

int main(int argc, char** argv) {
	DFA original {std::cin};
	original.dot(std::cout);
}
