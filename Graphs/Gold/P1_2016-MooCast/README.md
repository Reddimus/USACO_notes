# [USACO 2016 December Contest, Gold](http://www.usaco.org/index.php?page=dec16results)
## [Problem 1. Moocast](http://www.usaco.org/index.php?page=viewproblem2&cpid=669)

Farmer John's `N` cows `(1≤N≤1000)` want to organize an emergency "moo-cast" system for broadcasting important messages among themselves.

Instead of mooing at each-other over long distances, the cows decide to equip themselves with walkie-talkies, one for each cow. These walkie-talkies each have a limited transmission radius, but cows can relay messages to one-another along a path consisting of several hops, so it is not necessary for every cow to be able to transmit directly to every other cow.

The cows need to decide how much money to spend on their walkie-talkies. If they spend $X, they will each get a walkie-talkie capable of transmitting up to a distance of `sqrt(X)`. That is, the squared distance between two cows must be at most `X` for them to be able to communicate.

Please help the cows determine the minimum integer value of `X` such that a broadcast from any cow will ultimately be able to reach every other cow.

### INPUT FORMAT (file moocast.in):

The first line of input contains `N`.

The next `N` lines each contain the `x` and `y` coordinates of a single cow. These are both integers in the range `0…25,000`.

### OUTPUT FORMAT (file moocast.out):

Write a single line of output containing the integer `X` giving the minimum amount the cows must spend on walkie-talkies.

### SAMPLE INPUT:

```
4
1 3
5 4
7 2
6 1
```

### SAMPLE OUTPUT:

```
17
```

# [Solutions](https://github.com/Reddimus/USACO_notes/tree/main/Graphs/Gold/P1_2016-MooCast)

## Graphs - Disjoint Set Union (DSU) approach

### Steps
1.

### Time & Space complexity:
Time: `O(N^2 * log(N))`  
Space: `O(N^2)`

Where `N` is the number of cows. `α(N)` is the inverse Ackermann function which means it is effectively constant.

### Python Code:
```python
class DisjointSetUnion:
	# Initialize nodes to single sized node graphs
	def __init__(self, n: int) -> None:
		self.parent = [*range(n)]
		self.size = [1] * n

	# Recursively find and assign parent of current node
	def get_parent(self, v: int) -> int:
		if self.parent[v] == v:
			return v
		# Path compression optimization
		self.parent[v] = self.get_parent(self.parent[v])
		return self.parent[v]
	
	# Attempt to union two components
	def link(self, a: int, b: int) -> bool:
		a, b = self.get_parent(a), self.get_parent(b)
		if a == b:		# If nodes are already in same component
			return False
		
		if self.size[a] < self.size[b]:
			a, b = b, a		# Union by size optimization
		# Merge smaller component (b) into larger component (a)
		self.parent[b] = a
		self.size[a] += self.size[b]
		return True

with open("moocast.in", "r") as fin:
	# First line: n = number of cows
	n = int(fin.readline().strip())
	# For the next n lines read in coordinates of cows
	coords = [tuple(map(int, fin.readline().split())) for ln in range(n)]

# Store edges of indexed coordinates and calculate distances between all pairs of cows
edges = [(l_idx, r_idx, (coords[l_idx][0] - coords[r_idx][0])**2 + (coords[l_idx][1] - coords[r_idx][1])**2) for l_idx in range(n - 1) for r_idx in range(l_idx + 1, n)]

# Sort edges by their distance
edges.sort(key=lambda x: x[2])

# Union closest cows until all cows are connected
last_dist = 0
dsu = DisjointSetUnion(n)
for l_idx, r_idx, dist in edges:
	if dsu.link(l_idx, r_idx):
		last_dist = dist
		n -= 1
		if n == 1:	# If all cows are connected
			break

# The distance of the last unioned edge is the minimum amount to spend
print(last_dist, file=open("moocast.out", "w"))
```

### C++ Code:
```cpp
```

## Graphs - 

### Steps
1.

### Time & Space complexity:
Time: `O()`  
Space: `O()`

Where `N` is the number of cows. 

### Python Code:
```python
```

### C++ Code:
```cpp
```
