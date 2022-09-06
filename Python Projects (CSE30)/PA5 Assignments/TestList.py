from list import List


#------------------------------------------------------------------------------
#  Test the List type
#------------------------------------------------------------------------------
def main():

   L = List()
   L.append(1)
   L.append(2)
   L.append(3)
   print(len(L))
   print(L)
   print(repr(L))

   A = List()
   A.append(1)
   A.append(2)
   A.append(3)
   print('A==L :', A==L)
   A.append(4)
   print('A==L :', A==L)
   L.append(5)
   print(L)
   print(A)
   print('A==L is', A==L)

   L.clear()
   print(len(L))
   print(L)

   B = A.copy()
   print(B)
   print(repr(B))
   print('A==B :', A==B)
   print('A is B :', A is B)

   print()
   print(B)
   B.insert(0, 'foo')
   print(B)
   B.insert(3, 'bar')
   print(B)
   B.insert(6, 'one')
   print(B)
   B.insert(-2, 'two')
   print(B)
   print(repr(B))
   print(len(B))

   print()
   print(B.pop(0))
   print(B)
   print(B.pop(2))
   print(B)
   print(B.pop(5))
   print(B)
   print(B.pop(-2))
   print(B)
   print(len(B))
   print()

   # my tests
   C = List('00000234567891')
   print(C)

   #remove
   C.remove('1')
   print(C)

   #reverse
   C.reverse()
   print(C)

   C = List('0123456789')
   # get item
   x = C[0]
   print('item at 0 is ', x)
   x = C[-10]
   print('item at -10 is ', x)


   # set item
   C[3] = 9
   print('item at 3 is set to ', C[3])
   print(C)

   C[-3] = 0
   print('item at -3 is set to ', C[-3])
   print(C)

   # concat list
   D = List('000000')
   C += D
   D += B
   print(C)
   print(D)

   # add list
   C = A + B
   print(C)

   # mul list
   C = A*3
   print(C)

   # rmul list
   C = 3*B
   print(C)

# end

#------------------------------------------------------------------------------
if __name__=='__main__':

   main()

# end
     