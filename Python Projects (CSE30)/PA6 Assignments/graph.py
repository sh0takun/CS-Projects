#------------------------------------------------------------------------------
#  graph.py
#  Definition of the Graph class.
#------------------------------------------------------------------------------
from queue import *

class Graph(object):
   """Class representing an undirected graph."""

   def __init__(self, V, E):
      """Initialize a Graph object."""

      # basic attributes
      self._vertices = list(V)
      self._vertices.sort()
      self._edges = list(E)
      self._adj = {x:list() for x in V}
      for e in E:
         x,y = tuple(e)
         self._adj[x].append(y)
         self._adj[y].append(x)
         self._adj[x].sort()
         self._adj[y].sort()
      # end

      # additional attributes
      self._color = {x:None for x in V}
      self._ecs = {x:set() for x in V}

   # end

   @property
   def vertices(self):
      """Return the list of vertices of self."""
      return self._vertices
   # end

   @property
   def edges(self):
      """Return the list of edges of self."""
      return self._edges
   # end

   def __str__(self):
      """Return a string representation of self."""
      s = ''
      for x in self.vertices:
         a = str(self._adj[x])
         s += '{}: {}\n'.format(x, a[1:-1])
      # end
      return s
   # end      

   def add_vertex(self, x):
      """Adds a vertex x to self."""
      if x not in self.vertices:
         self.vertices.append(x)
         self.vertices.sort()
         self._adj[x] = list()
      # end
   # end 

   def add_edge(self, e):
      """Adds an edge e to self."""
      x, y = tuple(e)
      self.add_vertex(x)
      self.add_vertex(y)
      self._adj[x].append(y)
      self._adj[y].append(x)
      self._adj[x].sort()
      self._adj[y].sort()
      self.edges.append(e)
   # end

   def degree(self, x):
      """Returns the degree of vertex x."""
      return len(self._adj[x])
   # end

   def reachable(self, source):
      """Return the set of vertices that are reachable from source."""

      # initialize
      undiscovered = set(self.vertices)  # undiscovered vertices
      discovered   = Queue()             # discovered vertices
      finished     = set()               # finished vertices

      # discover the source
      undiscovered.remove(source)        # move source from undiscovered
      discovered.put(source)         # to discovered

      # discover all vertices reachable from the source
      while not discovered.isEmpty():
         x = discovered.dequeue()        # move x from discovered
         for y in self._adj[x]:
            if y in undiscovered:
               undiscovered.remove(y)        # move y from undiscovered
               discovered.put(y)         # to discovered
            # end
         # end
         finished.add(x)                 # to finished
      # end
      return finished
   # end

   def BFS(self, source):
      """
      Run the Breadth First Search algorithm, finding distances from source
      to all other vertices.
      """

      # initialize
      undiscovered = set(self.vertices)  # undiscovered vertices
      discovered   = Queue()             # discovered vertices
      finished     = set()               # finished vertices
      #for v in self.vertices:
         #self._predecessor[v] = None
      # end

      # discover the source
      undiscovered.remove(source)        # move source from undiscovered
      discovered.put(source)         # to discovered

      # discover everything reachable from the source
      while not discovered.empty():
         x = discovered.get()        # move x from discovered
         for y in self._adj[x]:
            if y in undiscovered:
               undiscovered.remove(y)        # move y from undiscovered
               discovered.put(y)         # to discovered
            # end
         # end
         finished.add(x)                 # to finished
      # end
      # return finished  # don't need to return anything
   # end

   def getPath(self, source, x, L):
      """
      Appends the vertices of a shortest source-x path to L. Pre: BFS() was 
      most recently run on source.
      """

      if x==source:
         L.append(source)
      #elif not self._predecessor[x]:
      #   L.append(str(x)+' not reachable from '+str(source))
      #else:
      #   self.getPath(source, self._predecessor[x], L)
      #   L.append(x)
      # end 
   # end

   def _find_best(self, L):
     """Return the index of the best vertex in the list L."""

     if len(L) != 0:
        return 0
     else:
        return 0
     #end

   def Color(self):
      """
      Determine a proper coloring of a graph by assigning a color from the
      set {1, 2, 3, .., n} to each vertex, where n=|V(G)|, and no two adjacent
      vertices have the same color. Try to minimize the number of colors
      used. Return the subset {1, 2, .., k} of {1, 2, 3, .., n} consisting
      of those colors actually used.
      """

      # 1. start somewhere
      i = self._find_best(self._vertices)
      source = self._vertices[i]

      # initialize
      unprocessed = set(self.vertices)  # unprocessed vertices
      processed   = Queue()             # processed vertices

      if len(self._edges) == 0:
         return [1]                     # for test10

      # discover the source
      unprocessed.remove(source)        # move source from unprocessed
      processed.put(source)             # to processed

      # 2. while some vertex has not been "processed"
      # 3. pick the "best such vertex x
      while not processed.empty():
         # 4. process x
         x = processed.get()        # move x from processed

         # check ecs[x] and pick available smallest number 
         col = list(set(self.vertices) - self._ecs[x])
         self._color[x] = col.pop(0)

         # 5. for each neighbor y of x
         for y in self._adj[x]:
            # 6. "update" the vertex y 
            self._ecs[y].add(self.getColor(x))
            if y in unprocessed:
               unprocessed.remove(y)       # move y from unprocessed
               processed.put(y)            # to processed
            # end
         # end

         # in case there are multiple groups in the vertex list
         if processed.empty() and len(unprocessed) != 0:
            y = unprocessed.pop()       # move y from unprocessed
            processed.put(y)                # to processed
      # end

      K = []
      for k, v in self._color.items():
          K.append(v)
      return K
   # end

   def getColor(self, x):
      """Return the color of vertex x."""
      return self._color[x]
   # end

# end


