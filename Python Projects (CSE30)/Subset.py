import sys
def to_string(B):
	#input is B, binary array in UCSC format 
	# if our input is B = [*,0,0,1,0,1,1,0]
	# our output should just print 
	# {3, 5, 6}
	S = "" #Builder string
	for i in range(len(B)):
		if B[i] == 1:
			S = S + str(i) + ","
	S = "{" + S[:-1] + "}"
	if S=="{}":
                S="{ }" 
	return S
def printSubsets(B, k, i):
	#B is an array in binary, where the first element is going to be some number we ignore,
	#ex, [*,1,1,1]
	#K is the integer length of our subsets: e.g. 2
	#i will be the element in consideration (intialized always at 1)

	#base case (halt condition)
	if (k > len(B) -i):
		return
	if (k == 0):
		print(to_string(B[:i]))
		return
	else:
		#use it or lose it
		useItB = B[:]
		loseItB = B[:]
		useItB[i] = 1
		loseItB[i] = 0
		#recursive code
		printSubsets(useItB, k-1, i+1)
		printSubsets(loseItB, k, i+1) 


if __name__=='__main__':
        try:
                N = int(sys.argv[1])
                K = int(sys.argv[2])
                B=[5]+[1]*int(N)
                I=1
                printSubsets(B, K, I)
        except:
                quit()

        
        
        
        



