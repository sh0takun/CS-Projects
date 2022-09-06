#------------------------------------------------------------------------------
#  ContinuedFractions.py
#------------------------------------------------------------------------------
import sys
from rational import *
from decimal import *

def CF(L):

    if len(L) == 1:
        return Rational(L[0])
    else:
        d = L.pop()
        return Rational(d) + Rational(1) / CF(L)

# usage()
# Prints error messages to stderr
def usage():
   print("Usage: $ python3 ContinuedFractions.py <input file> <output file>", file=sys.stderr, end='')
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
   # end
   outfile = open(sys.argv[2], 'w')

   # read in each line of infile, reverse it, then print to outfile
   lines = infile.readlines()
   for S in lines:
       L = S.split()
       # convert str to int
       for i in range(0, len(L)):
           L[i] = int(L[i])
       L.reverse()

       # call recursive function
       f = CF(L)

       #f = Rational(1, L[0])
       #f = Rational(L[1]) + Rational(1) / f
       #f = Rational(L[2]) + Rational(1) / f
       #f = Rational(L[3]) + Rational(1) / f
       #f = Rational(L[4]) + Rational(1) / f
       #f = Rational(L[5]) + Rational(1) / f

       print('', file=outfile)
       print(f, file=outfile)

       getcontext().prec = 100  # set Decimal precision to 100 digits
       r = Decimal(f.numer) / Decimal(f.denom)

       print(r, file=outfile)
       # end

   infile.close()
   outfile.close()
   exit(0)

# end



#------------------------------------------------------------------------------
if __name__=='__main__':

   main()

# end
