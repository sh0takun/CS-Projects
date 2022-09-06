#------------------------------------------------------------------------------
#  Shota Tonari
#  stonari
#  CSE 30-02 Spring 2021
#  pa2
#
#  Queens.py
#  create a program that finds solutions of n queens on a nxn chessboard that doesn't
#  intersect horizontally, vertically, or diagonally.
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# import statements
import sys
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# definitions of optional helper functions
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# definitions of required functions, classes etc..
#------------------------------------------------------------------------------

def placeQueen(B, i, j):
   B[i][j] = 1   #makes wherever the queen goes to number 1
   B[i][0] = j   #stores the answers into the first column of the array, we can see that j equals the first to row, column zero

   size = len(B)     #the length of array pretty much what N is 
   for row in range(i+1, size):    #row is the constraints of what goes below the queen makes it 1
      B[row][j] -= 1     #the for loop goes all the way down and makes each box equal to -1

   c = 1 
   for right in range(i+1, size):      #the bottom right of the eliminated boxes from the queen
      if (j+c < len(B[0])):          #le epic code
        B[right][j+c] -= 1         #System.out.println('shota is the best coder.')
        c += 1                               #Scanner keyboard =　new Scanner();

   c = 1
   for left in range(i+1, size):
      if (j-c) >= 1:
        B[left][j-c] -= 1
        c += 1

def removeQueen(B, i, j):
   B[i][j] = 0
   B[i][0] = 0

   size = len(B)
   for row in range(i+1, size):
      B[row][j] += 1

   c = 1 
   for right in range(i+1, size):      #the bottom right of the eliminated boxes from the queen
      if (j+c < len(B[0])):          #le epic code
        B[right][j+c] += 1         #System.out.println('shota is the best coder.')
        c += 1                               #Scanner keyboard =　new Scanner();

   c = 1
   for left in range(i+1, size):
      if (j-c) >= 1:
        B[left][j-c] += 1
        c += 1

def printBoard(B):
    queens = '('
    for i in range(1, len(B)):
        queens += str((B[i][0]))
        if i < len(B)-1:
            queens += ', '
    queens += ')'
    print(queens)

def findSolutions(B, i, mode):
    sum = 0
    if (i>n):
        if (mode == "-v"):
            printBoard(B)
        return 1

    else:
      for j in range(1, len(B[0])):
          if (B[i][j] == 0):
              placeQueen(B, i, j)
              sum += findSolutions(B, i+1, mode)
              removeQueen(B, i, j)

    return sum

def usage():
        print("Usage: python3 Queens.py [-v] number\nOption: -v verbose output, print all solutions", file=sys.stderr)
        #print("Usage: python3 Queens.py [-v] number", file=sys.stderr)
        #print("Option: -v  verbose output, print all solutions", file=sys.stderr)
        exit()

def main():

        global n
        mode = ''

        if len(sys.argv) < 2 or len(sys.argv) > 3:
            usage()
        else:
            if len(sys.argv) == 2:
                if sys.argv[1].isnumeric():
                    n = int(sys.argv[1])
                else:
                    usage()
            else: # argv is 3
                if sys.argv[1].isnumeric():
                    n = int(sys.argv[1])
                elif sys.argv[2].isnumeric():
                    n = int(sys.argv[2])
                else:
                    usage()

                if sys.argv[1] == '-v':
                    mode = '-v'
                elif sys.argv[2] == '-v':
                    mode = '-v'
                else:
                    usage()

            if n >= 1 and n <= 13:
                B = [[0 for i in range(n+1)] for j in range(n+1)]
                # start from row 1 instead of 0
                solutionsFound = findSolutions(B, 1, mode)
                print(f"{n}-Queens has {solutionsFound} solutions")

            else:
                usage()




#------------------------------------------------------------------------------
# if this is a stand alone module, i.e. not a program to be run, then you can
# stop here. If this is a program to be run under python, then continue.
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# definition of function main()

   # do whatever it is the program is supposed to do



# end

#------------------------------------------------------------------------------
# closing conditional that calls main()
#------------------------------------------------------------------------------
if __name__=='__main__':

   main()

#end
