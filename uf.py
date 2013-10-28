'''
Union find
create: 10/18/2013
'''

import sys

class WeightedUnion(object):
    '''
    This class uses an improved version of quick union,
    It keeps track of the size of a tree. When making a union,
    it puts the smaller tree in the bigger tree so to avoid
    making a tall tree.

    
    '''
    def __init__ (self, size):
        self._size = size
        self._oarray = [ i for i in range(self._size)]
        self._treeSize = [ 1 ] * self._size
        

    def printOarray(self):
        print(self._oarray)
        print(self._treeSize)

        
    def findRoot(self, i):
        while (self._oarray[i] != i ):
            i = self._oarray[i]
        return i

    def isConnected(self, p, q):
        return self.findRoot(p) == self.findRoot(q)
        

    def makeUnion(self, p, q):

        if self.isConnected( p,q ):
            print(' Already connected')
            return
        print(' They are not yet connected')
            
        i = self.findRoot(p)
        j = self.findRoot(q)

        print(' Root of '+ str(p) + ' is '+ str(i) + ' size '+ str(self._treeSize[i]))
        print(' Root of '+ str(q) + ' is '+ str(j) + ' size '+ str(self._treeSize[j]))

        
        if self._treeSize[i] < self._treeSize[j]:
            ''' tree i is smaller than tree j,
                i should join j
            '''
            self._oarray[i] = j                    # make entry of i point to j
            self._treeSize[j] += self._treeSize[i] # update j tree size
            print(' Tree '+ str(i) + ' joined '+ str(j))
        else:
            ''' tree j is smaller or equal to than tree i,
                j should join i
            '''
            self._oarray[j] = i
            self._treeSize[i] += self._treeSize[j] 
            print(' Tree '+ str(j) + ' joined '+ str(i))

            
            
class QuickUnion(object):
    '''
	This method simply puts one root under 
        another when making a union of two trees.
	'''
    
    def __init__ (self, size):
        self._size = size
        self._oarray = [ i for i in range(self._size)]

    def printOarray(self):
        print(self._oarray)

        
    def findRoot(self, i):
        while (self._oarray[i] != i ):
            i = self._oarray[i]
        return i

    def isConnected(self, p, q):
        return self.isRoot(p) == self.isRoot(q)

    def makeUnion(self, p, q):
        i = self.findRoot(p)
        j = self.findRoot(q)
        self._oarray[i] = j

        
class QuickFindUF (object):

    '''Initialize an object array:
       indexed by the object number 0,1,2,...
       Each entry is an object ID, as if an pointer
       points to another object
    '''
    def __init__ (self, size):
        self._size = size
        self._oarray = [ i for i in range(self._size)]
        
    def printOarray(self):
        print(self._oarray)

    def isconnected(self, p, q):
        '''
        p and q have to be integers
        '''
        return self._oarray[p] == self._oarray[q]
        
    def makeUnion(self, p, q ):
        '''
        p and q have to be integers
        
        make a union of p and q so that all objects whose id
        is equal to that of q are changed to the object id of p
        
        '''
        
        pid = self._oarray[p] # This is the obj id we are changing to
        qid = self._oarray[q] # This is the obj id we are changing from

        for i in range(self._size):
            if self._oarray[i] == qid:
                self._oarray[i] = pid
        
                

###########################################'''
# Main function
###########################################'''

if __name__ == "__main__":


    ####################################
    # Weighted Union
    ####################################
    print(' Test Weighted Union ')
    C = WeightedUnion(10)
    C.printOarray()


    while(True):
        print('----------------------------------------------')
        print(' Enter two integers from among above to make a weighted union, 0 and 0 to quit')
        a = raw_input(" First  int: ")
        b = raw_input(" Second int: ")

        if a == '0' and b == '0':
            break
        C.makeUnion( int(a), int(b) )
        C.printOarray()

        
    Input = raw_input(' Do you want to continue? (Y/N) ')
    if Input == "N":
        sys.exit()
        
    ##################################
    # Quick find and union
    ##################################
    print(' Test Quick Lazy Union and Find (array to tree)')
    B = QuickUnion(10)
    B.printOarray()

    i = raw_input(' Test findRoot, enter an obj ID: ')
    j = B.findRoot(int(i))
    print(' The root of '+ i + ' is ' + str(j) )

    p = raw_input(" First  int to make a union: ")
    q = raw_input(" Second int to make a union: ")

    B.makeUnion(int(p), int(q))
    B.printOarray()

    ##################################    
    # Basic find and union
    ##################################
    print('Test Quick Union and Find')
    A = QuickFindUF(10)
    A.printOarray()


    while (True):
        print('------------------')
        print(' Enter two integers from among above to see if they are connected, \
              0 and 0 to quit')
        p = raw_input(" First int: ")
        q = raw_input(" Second int: ")

        if p == '0' and q == '0':
            break
            
        result = A.isconnected(int(p),int(q))
        if result != None:
            #print(result)
            if result == False:
                print(p + ' and ' + q + ' not a union, make one now')
                A.makeUnion(int(p), int(q))
                A.printOarray()
            else:
                print(' Already a union')
    
    print('Test Quick Union and Find Finished')


    
    
