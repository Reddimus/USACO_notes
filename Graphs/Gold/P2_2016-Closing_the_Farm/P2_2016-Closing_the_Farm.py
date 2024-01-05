# Graphs - Disjoint Set Union (DSU) approach
# T: O(N + M * alpha(N)), M: O(N + M)
# Where N = # of barns, M = # of paths, and α(N) ≈ O(1) ≈ inverse Ackermann function

class DisjointSetUnion:
	# Initialize nodes to single sized node graphs
	def __init__(self, num_barns: int) -> None:
		self.parent = [*range(num_barns)]
		self.size = [1] * num_barns

	# Recursively find and assign parent of current node
	def find_parent(self, v: int) -> int:
		if self.parent[v] == v:
			return v
		# Path compression optimization
		self.parent[v] = self.find_parent(self.parent[v])
		return self.parent[v]
	
	# Attempt to union two components
	def union(self, a: int, b: int) -> bool:
		a, b = self.find_parent(a), self.find_parent(b)
		if a == b:		# If nodes are already in same component
			return False
		
		if self.size[a] < self.size[b]:
			a, b = b, a		# Union by size optimization
		# Merge smaller component (b) into larger component (a)
		self.parent[b] = a
		self.size[a] += self.size[b]
		return True

with open("closing.in", "r") as fin:
	# Read in first line: n = # of barns, m = # of paths
	n, m = map(int, fin.readline().split())
	# For the next m lines, read in the barns connected by a path into graph
	graph = [[] for idx in range(n)]
	for ln in range(m):
		b1, b2 = map(lambda b: int(b) - 1, fin.readline().split())
		graph[b1].append(b2)
		graph[b2].append(b1)
	# For the next n lines, read in the barns to be removed
	remove_order = [int(fin.readline()) - 1 for ln in range(n)]

# In reverse removed order, open barns and union them to any open adjacent barns
dsu = DisjointSetUnion(n)
open_barns = set()
components = 0
fully_connected = []	# List of answer(s) in reversed order
for barn in reversed(remove_order):
	components += 1
	for adj in graph[barn]:
		if adj in open_barns and dsu.union(barn, adj):
			components -= 1	# group barns into one connected component

	fully_connected.append("YES" if components == 1 else "NO")
	open_barns.add(barn)

# Write fully connected barns in removed order to output file
print(*reversed(fully_connected), sep="\n", file=open("closing.out", "w"))