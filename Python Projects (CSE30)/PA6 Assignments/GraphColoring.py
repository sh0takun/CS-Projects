#------------------------------------------------------------------------------
#  GraphColoring.py
#------------------------------------------------------------------------------
import sys
from graph import *

def CheckProperColoring(G):
    """
    Return True if no two adjacent vertices in G have like colors,
    False otherwise.
    """

    K = list()

    V = G.vertices
    E = G.edges
    K = G.Color()

    # sanity check
    if len(V) != len(K):
       return False
    if len(V) == 0 or len(K) == 0:
       return False
    if len(E) == 0:
       return False
    if len(K) == 0:
       return False

    for x in range(0, len(E)):
       v1 = E[x][0]   # assuming edges are always two
       v2 = E[x][1]
       if K[v1-1] == K[v2-1]:  # should not be the same color
          return False

    return True
#end

# usage()
# Prints error messages to stderr
def usage():
   print("Usage: $ python3 GraphColoring.py <input file> <output file>", file=sys.stderr, end='')
   exit()
# end

def main():

    # check command line arguments and open files
    if len(sys.argv)!=3:
        usage()
    # end
    try:
        infile = open(sys.argv[1])
    except FileNotFoundError as e:
        print(e, file=sys.stderr)
        usage()

    outfile = open(sys.argv[2], 'w')
    vertices = 0; 
    V = []
    E = []

    # read each line of input file
    lines = infile.readlines()

    # get number of vertices on first line, create vertex list
    for line in lines:
       L = line.split()
       if (vertices == 0):
          vertices = int(L[0])
          if vertices == 0:
              exit(0)
          for i in range(1, vertices+1):
              V.append(i)
          continue
    # create edge list from remaining lines
       for i in range(0, len(L)):
           L[i] = int(L[i])
       if (len(L)!= 0):
          E.append(L)

    if len(V) == 0:
        exit(0)

    # create graph G
    G = Graph(V,E)

    # Determine a proper coloring of G and print it to the output file
    K = G.Color()

    r = CheckProperColoring(G)

    N = list(set(K))

    msg = "{} colors used: ".format(len(N))
    msg += "{"
    for i in range(0, len(N)):
       msg += str(N[i])
       if(i == len(N)-1):
          msg += "}"
       else:
          msg += ", "
    
    print(msg, file=outfile)

    print("", file=outfile)
    print("vertex    color", file=outfile)
    print("----------------", file=outfile)

    for i in range(0, len(V)):
       msg = " {}" .format(str(i+1))
       for j in range(1, 1+10-len(str(i+1))):
           msg += " "
       if len(K) != 0:
          msg += "{}" .format(str(K[i]))
       print(msg, file=outfile)

    # Check that the coloring is correct
    #print(file=outfile)
    #msg = "coloring is proper: {}".format(CheckProperColoring(G))
    #print(msg, file=outfile)

    exit(0)

# end

#------------------------------------------------------------------------------
if __name__=='__main__':

   main()

# end