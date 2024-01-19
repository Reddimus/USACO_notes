# Graphs - Disjoint Set Union (DSU) approach
# T: O(n^2 * log(n)), M: O(n^2), where n is the number of cows

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