"""
Utility functions for minimization.
"""


class State:
	final = False
	start = False
	transition = {}


def readDFA(dfaFile):
	dfa = {}
	dfa['state'] = {}

	# Read the first line (state names) and create state objects for each
	for key in dfaFile.readline().strip().split():
		dfa['state'][key] = State()

	# Read in the alphabet
	dfa['alphabet'] = dfaFile.readline().strip().split()

	# Set the start state flag
	startKey = dfaFile.readline().strip()
	dfa['state'][startKey].start = True
	dfa['start'] = startKey

	# Read in the final state names and set the appropriate flags
	dfa['final'] = dfaFile.readline().strip().split()
	for key in dfa['final']:
		dfa['state'][key].final = True

	# Set the transitions in each state based on the rest of the rules
	for line in dfaFile:
		key, symbol, transitionKey = line.strip().split()
		dfa['state'][key].transition[symbol] = transitionKey

	return dfa


# Returns the logical XOR of two booleans since this operator does not
# Exist in python
def xor(op0, op1):
	if op0 != op1:
		return True
	else:
		return False
