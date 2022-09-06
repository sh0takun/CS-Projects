#------------------------------------------------------------------------------
#  rational.py
#  Rational class
#------------------------------------------------------------------------------

# helper function
def _gcd(a, b):
    while b != 0:
        a, b = b, a%b
    return a

class Rational(object):

   #Class representing a rational number.
   
   #Methods defined here:
   
   def __add__(self, other):
       #Return the sum of two rational numbers.
       factor1 = other.denom
       factor2 = self.denom
       return Rational(self.numer * factor1 + other.numer * factor2, self.denom * other.denom)

   def __eq__(self, other):
       #Return True if self == other, False otherwise.
       factor1 = other.denom
       factor2 = self.denom
       return (self.numer * factor1 == other.numer * factor2)

   def __float__(self):
       #Return the float equivalent of self.
       return self.numer / self.denom
   
   def __ge__(self, other):
       #Return true if self >= other, False otherwise.
       factor1 = other.denom
       factor2 = self.denom
       return (self.numer * factor1 >= other.numer * factor2)
   
   def __gt__(self, other):
       #Return true if self > other, False otherwise.
       factor1 = other.denom
       factor2 = self.denom
       return (self.numer * factor1 > other.numer * factor2)
   
   def __init__(self, n, d=1):
       divisor = _gcd(n, d)
       if d // divisor < 0:
           divisor = -divisor
       self._numer = n // divisor
       self._denom = d // divisor

   def __le__(self, other):
       #Return true if self <= other, False otherwise.
       factor1 = other.denom
       factor2 = self.denom
       return (self.numer * factor1 <= other.numer * factor2)
   
   def __lt__(self, other):
       #Return true if self < other, False otherwise.
       factor1 = other.denom
       factor2 = self.denom
       return (self.numer * factor1 < other.numer * factor2)
   
   def __mul__(self, other):
       #Return the product of two rational numbers.
       return Rational(self.numer*other.numer, self.denom*other.denom)
   
   def __ne__(self, other):
       #Return False if self == other, True otherwise.
       factor1 = other.denom
       factor2 = self.denom
       return (self.numer * factor1 != other.numer * factor2)
   
   def __repr__(self):
       #Return the detailed string representation of a rational number.
       return 'rational.Rational({}, {})'.format(self.numer, self.denom)
   
   def __str__(self):
       #Return the string representation of a rational number.
       return '{}/{}'.format(self.numer, self.denom)
   
   def __sub__(self, other):
       #Return the difference of two rational numbers.
       factor1 = other.denom
       factor2 = self.denom
       return Rational(self.numer * factor1 - other.numer * factor2, self.denom * other.denom)
   
   def __truediv__(self, other):
       #Return the quotient of two rational numbers.
       return Rational(self.numer * other.denom, self.denom * other.numer)
   
   def inverse(self):
       #Return the multiplicative inverse of a rational number.
       return Rational(self.denom, self.numer)
   
 #  ----------------------------------------------------------------------
 #  Readonly properties defined here:
   
   @property
   def numer(self):
     return self._numer
   
   @property
   def denom(self):
     return self._denom
   
 #  ----------------------------------------------------------------------
 #  Data descriptors defined here:
   
 #  __dict__
 #      dictionary for instance variables (if defined)
   
 #  __weakref__
 #      list of weak references to the object (if defined)
   
 #  ----------------------------------------------------------------------
 #  Data and other attributes defined here:
   
 #  __hash__ = None

