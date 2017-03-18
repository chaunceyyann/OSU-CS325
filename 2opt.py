##################################################################################
# Project 4 for CS 325 @ Oregon State
# Group 11: Chauncey Yan, Molly Michel Arwood, Mengying Fan
##################################################################################
import math, re, sys

def main(instancefile):
    cities = readinstance(instancefile)
    solution = [n[2] for n in cities] # create initial solution which using the input
    print solution
    run = True
    while run:
        (run,solution) = twoOpt(cities, solution, len(solution))
        tour = checksolution(cities,solution)
        print tour 
    print solution
    solutionfile=instancefile+".tour"
    createsolution(solutionfile,tour,solution)

##################################################################################
# provided by Juli Schutfort     schutfoj@engr.oregonstate.edu
##################################################################################
def readinstance(filename):
    # each line of input file represents a city given by three integers:
    # identifier x-coordinate y-coordinate (space separated)
    # city identifiers are always consecutive integers starting with 0
    # (although this is not assumed here explicitly,
    #    it will be a requirement to match up with the solution file)
    f = open(filename,'r')
    line = f.readline()
    cities = []
    while len(line) > 1:
        lineparse = re.findall(r'[^,;\s]+', line)
        cities.append([int(lineparse[1]),int(lineparse[2]),int(lineparse[0])])
        line = f.readline()
    f.close()
    return cities

##################################################################################
# Write tour distance and solution to file
##################################################################################
def createsolution(filename,best,solution):
    w = open(filename, 'w')
    w.write(str(best)+'\n')
    for city in solution:
        w.write("%s\n" % city)

##################################################################################
# provided by Juli Schutfort     schutfoj@engr.oregonstate.edu
##################################################################################
def distance(a,b):
    # a and b are integer pairs (each representing a point in a 2D, integer grid)
    # Euclidean distance rounded to the nearest integer:
    dx = a[0]-b[0]
    dy = a[1]-b[1]
    #return int(math.sqrt(dx*dx + dy*dy)+0.5) # equivalent to the next line
    return int(round(math.sqrt(dx*dx + dy*dy)))

##################################################################################
#    Before 2opt             After 2opt
#       Y   N                    Y   N
#       O   O----->              O-->O---->
#      / \  ^                     \
#     /   \ |                      \
#    /     \|                       \
# ->O       O              ->O------>O
#   P       X                P       X
#(Graph from https://youtu.be/q6fPk0--eHY,Frans Slothouber)
#
# In a 2opt, considering two nodes X and Y. Note: they may not connected.
# Node Y following P and the node N following X.
#
# Swap from  PY and XN to PX and YN if (PY + XN)-(PX + YN) is the best gain 
#
# Swap steps:(from wikipedia 2-opt section)
# 1. take route[1] to route[i-1] and add them in order to new_route
# 2. take route[i] to route[k] and add them in reverse order to new_route
# 3. take route[k+1] to end and add them in order to new_route
#
# Read the formated input file, write the tour distance and solution to solution file
##################################################################################
def twoOpt(nodes, solution, node_size):
    best = 0
    best_sol = None
    # scan all nodes
    for pi in range(node_size):
        for xi in range(node_size):
            yi = (pi+1)%node_size  # Y is following P
            ni = (xi+1)%node_size  # N is following X
            
            # calculate the distances
            py = distance(nodes[solution[pi]],nodes[solution[yi]])
            xn = distance(nodes[solution[xi]],nodes[solution[ni]])
            px = distance(nodes[solution[pi]],nodes[solution[xi]])
            yn = distance(nodes[solution[yi]],nodes[solution[ni]])

            # make sure they are not the same node
            if pi!=xi and pi!=yi and pi!=ni and xi!=yi and xi!=ni and yi!=ni:
                gain = (py+xn)-(px+yn)
                if gain > best:
                    best_sol = (pi,yi,xi,ni)
                    best = gain
    print best
    # Reconstruct solution from the best swap saved in best_sol
    if best_sol !=  None:
        (pi,yi,xi,ni) = best_sol # restore the best solution to individual variables

        new_solution = [0]*node_size # new empty solution list
        
        # Put the P at the head of the new list.
        new_solution[0] = solution[pi]

        # reverse copy X to Y in the direction of Y to X
        c = 1
        while xi != yi:
            new_solution[c] = solution[xi]
            c += 1
            xi = (xi-1)%node_size
        new_solution[c] = solution[yi]

        # Copy N to last and start to P into the second half of the list.
        c += 1
        while ni != pi:
            new_solution[c] = solution[ni]
            c += 1
            ni = (ni+1)%node_size # overflow 

        return (True,new_solution)
    else:
        return (False,solution)


##################################################################################
# provided by Juli Schutfort     schutfoj@engr.oregonstate.edu
##################################################################################
def checksolution(cities, cityorder):
    # calculate the length of the tour given by cityorder:
    n = len(cities)
    dist = 0
    for i in range(n):
        dist = dist + distance(cities[cityorder[i]],cities[cityorder[i - 1]])
    return dist

##################################################################################
if __name__ == '__main__':
	main(sys.argv[1])
