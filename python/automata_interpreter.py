import sys

if (len(sys.argv) != 3):
    print ('error')
    sys.exit()

try:
    machine = open(sys.argv[1])
except OSError:
    print ('Error opening', sys.argv[1])
    sys.exit()

try:
    infile = open(sys.argv[2])
except OSError:
    print('Error opening', sys.argv[2])
    sys.exit()

try:
    machina = list(machine)
except OSError:
    print('Error reading', sys.argv[1])
    sys.exit()

try:
    readfile = list(infile)
except OSError:
    print('Error reading', sys.argv[2])
    sys.exit()

machina = list(map(lambda s: s.rstrip(), machina))

machine_dec = machina[0].split(' ')

if (machine_dec[0] != 'machine' or not machine_dec[-1].endswith(':')):
    print(machine_dec, 'at line 1 is not a valid machine declaration')
    sys.exit()

if (machina[0] != machina[0].strip()):
    print('At line 1, machine declarations must be unindented')
    sys.exit()

if (machina[1].strip().split(' ')[0] != 'state'):
    print(machina[1], 'at line 2 is not a valid state declaration')
    sys.exit()

state_length = machina[1].find('s')

states=[]
for line in machina:
    if (line.strip().split(' ')[0] == 'state'):
        parse_state = line.strip().split(' ')
        parse_state = parse_state[1:]
        state_name = ' '.join(parse_state)[:-1]
        states.append(state_name)

lc = 1
transition_length = 0
new_state = False
found = False
ops = set()
for line in machina:
    if (lc == 1):
        lc = lc + 1
        continue
    
    if (line.strip().split(' ')[0] == 'state'):
        if (line.find('s') != state_length):
            print('At line', lc, 'all state declarations must have the same indentation')
            sys.exit()
        if (line.strip().split(' ')[-1][-1] != ':'):
            print('At line', lc, 'malformed state declaration')
            sys.exit()
        new_state = True
    else:
        if (new_state):
            transition_length = line.find('\S')
        new_state = False
        if (line.find('->') == -1):
            print('At line', lc, 'missing -> operator')
            sys.exit()
        if (line.find('\S') != transition_length):
            print('At line', lc, 'all transitions declarations within a state must have the same indentation')
            sys.exit()
        transition = line.split('->')[1].strip()
        ops.add(line.split('->')[0].strip())
        for state in states:
            if (transition.find(state) == 0):
                if (transition.split(state)[1].strip()[0] != '/'):
                    print('At line', lc, 'missing / operator')
                    sys.exit()
                found = True
        if (not found):
            print('At line', lc, 'invalid destination state')
            sys.exit()

index = 1
parse_state = machina[1].strip().split(' ')[1:]
initial_state = ' '.join(parse_state)[:-1]
first = True
lc = 1
for instruction in readfile:
    instruction = instruction.rstrip()
    if first:
        first = False
    else:
        print()
    print('input:', instruction)
    if (instruction not in ops):
        print('At line', lc, 'of input file, invalid input.')
        continue
    
    i = index+1;
    while (machina[i].strip().split()[0] != 'state'):
        
        command = machina[i].split('->')[0].strip()
        
        if (command == instruction):
            preparse = machina[i].split('->')[1].strip()
            
            if '/' in preparse:
                output = preparse.split('/')[1].strip()
                print('output:', output)
            
            transition = preparse.split('/')[0].strip()
            print('transitioning to', transition)
            
            break
        else:
            i = i+1
    
    new_state = 'state ' + transition + ':'
    
    index = 0
    while (machina[index].strip() != new_state):
        index = index + 1
