#------------------------------------------------------------------------------
#  TestRational.py
#  A weak test of the Rational class.
#------------------------------------------------------------------------------
from rational import *
from decimal import *


def main():

   A = Rational(745839234, 293847742)  # 372919617/146923871
   B = Rational(658, -239) # -658/239
   C = A*B
   D = C.inverse()

   print()
   print(A)
   print(repr(A))
   print(B)
   print(repr(B))
   print(C)
   print(repr(C))
   print(D)
   print(repr(D))
   print()
   print(A+B)
   print(A-B)
   print(A*B)
   print(A/B)
   print(A.inverse())
   print()

   a = float(A)
   b = float(B)
   c = a*b
   d = 1/c
   print(a)
   print(b)
   print(c)
   print(d)
   print()

   getcontext().prec = 50  # set Decimal precision to 1000 digits
   a = Decimal(A.numer)/Decimal(A.denom)
   b = Decimal(B.numer)/Decimal(B.denom)
   c = a*b
   d = 1/c
   print(a)
   print(b)
   print(c)
   print(d)
   print()

   print(A>B)
   print(B>=C)
   print(C<D)
   print(D<=A)
   print( A==C/B )
   print( (A*B)/(C*D)==(A/C)*(B/D) )
   print()

   help(Rational)

# end

#------------------------------------------------------------------------------
if __name__=='__main__':

   main()

# end


# output of this program
"""

372919617/146923871
rational.Rational(372919617, 146923871)
-658/239
rational.Rational(-658, 239)
-245381107986/35114805169
rational.Rational(-245381107986, 35114805169)
-35114805169/245381107986
rational.Rational(-35114805169, 245381107986)

-7548118655/35114805169
185803695581/35114805169
-245381107986/35114805169
-12732541209/13810843874
146923871/372919617

2.538182627927085
-2.7531380753138075
-6.987967235046116
-0.14310313233650995

2.5381826279270847689549372137084517736399689605238
-2.7531380753138075313807531380753138075313807531381
-6.9879672350461162258257267222600889834941404854589
-0.14310313233650996413591522089753875058941188947705

True
True
True
True
True
True

Help on class Rational in module rational:

class Rational(builtins.object)
 |  Rational(n, d=1)
 |  
 |  Class representing a rational number.
 |  
 |  Methods defined here:
 |  
 |  __add__(self, other)
 |      Return the sum of two rational numbers.
 |  
 |  __eq__(self, other)
 |      Return True if self == other, False otherwise.
 |  
 |  __float__(self)
 |      Return the float equivalent of self.
 |  
 |  __ge__(self, other)
 |      Return true if self >= other, False otherwise.
 |  
 |  __gt__(self, other)
 |      Return true if self > other, False otherwise.
 |  
 |  __init__(self, n, d=1)
 |      Initialize a Rational object.
 |  
 |  __le__(self, other)
 |      Return true if self <= other, False otherwise.
 |  
 |  __lt__(self, other)
 |      Return true if self < other, False otherwise.
 |  
 |  __mul__(self, other)
 |      Return the product of two rational numbers.
 |  
 |  __ne__(self, other)
 |      Return False if self == other, True otherwise.
 |  
 |  __repr__(self)
 |      Return the detailed string representation of a rational number.
 |  
 |  __str__(self)
 |      Return the string representation of a rational number.
 |  
 |  __sub__(self, other)
 |      Return the difference of two rational numbers.
 |  
 |  __truediv__(self, other)
 |      Return the quotient of two rational numbers.
 |  
 |  inverse(self)
 |      Return the multiplicative inverse of a rational number.
 |  
 |  ----------------------------------------------------------------------
 |  Readonly properties defined here:
 |  
 |  denom
 |      Return the denominator of a rational number.
 |  
 |  numer
 |      Return the numerator of a rational number.
 |  
 |  ----------------------------------------------------------------------
 |  Data descriptors defined here:
 |  
 |  __dict__
 |      dictionary for instance variables (if defined)
 |  
 |  __weakref__
 |      list of weak references to the object (if defined)
 |  
 |  ----------------------------------------------------------------------
 |  Data and other attributes defined here:
 |  
 |  __hash__ = None

"""