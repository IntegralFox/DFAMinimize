"""
Utility functions for minimization.
"""


class State:
	def __init__(self):
		self.final = False
		self.start = False
		self.transition = {}


class DFA:
	def __init__(self, dfaFile):
		self.state = {}
		self.key = []

		# Read the first line (state names) and create state objects for each
		for key in dfaFile.readline().strip().split():
			self.key.append(key)
			self.state[key] = State()

		# Read in the alphabet
		self.alphabet = dfaFile.readline().strip().split()

		# Set the start state flag
		self.start = dfaFile.readline().strip()
		self.state[self.start].start = True

		# Read in the final state names and set the appropriate flags
		self.final = dfaFile.readline().strip().split()
		for key in self.final:
			self.state[key].final = True

		# Set the transitions in each state based on the rest of the rules
		for line in dfaFile:
			key, symbol, transitionKey = line.strip().split()
			self.state[key].transition[symbol] = transitionKey


# Returns the logical XOR of two booleans since this operator does not
# Exist in python
def xor(op0, op1):
	return op0 != op1
