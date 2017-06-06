import sys
import re

#
# Ensure that there are at least three arguments
#
if len(sys.argv) < 3:
    print("usage:\n\n    %s <automaton file> <input file>\n"%sys.argv[0])
    sys.exit(-1) # terminate with an error state

try:
    automaton_file = file(sys.argv[1],"r")
except IOError,ex:
    print("Unable to open %s for reading."%sys.argv[1])
    sys.exit(-1) # terminate with an error state

try:
    input_file = file(sys.argv[2],"r")
except IOError,ex:
    print("Unable to open %s for reading."%sys.argv[2])
    sys.exit(-1) # terminate with an error state

for line in automaton_file.readlines():
    # this matches transitions
    match = re.findall(r'(\s*)(\S+)\s*->\s*(\S+)\s*(/\s*(.*))?',line)
    print line
    print match
    # make a match for states
    # make a match for the machine name

for line in input_file.readlines():
    line = line.strip() # remove leading/training whitespace and newline
    print 'input:',line
    # feed the line into the machine
