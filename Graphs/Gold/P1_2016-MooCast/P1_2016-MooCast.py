# Graphs - Minimum Spanning Tree (MST) approach
# T: O(n^2), M: O(n), where n is the number of cows

with open("moocast.in", "r") as fin:
	# First line: n = number of cows
	n = int(fin.readline().strip())
	# For the next n lines read in coordinates of cows
	coords = [tuple(map(int, fin.readline().split())) for ln in range(n)]

# Initialize distance hashmap (x, y) -> distance and answer variable
distance = {coord: float("inf") for coord in coords}
distance[coords[0]] = 0
spend = 0

# For every cow, find the closest cow and update answer
for cow in range(n):
	ax, ay = min(distance, key=distance.get)	# Get smallest coordinate
	spend = max(spend, distance[(ax, ay)])
	del distance[(ax, ay)]
	# For every other non-visited/deleted coordinate, update distance
	for bx, by in distance.keys():
		curr_distance = (ax - bx)**2 + (ay - by)**2
		distance[(bx, by)] = min(distance[(bx, by)], curr_distance)

# Write the minimum distance/price to spend to the output file
print(spend, file=open("moocast.out", "w"))

'''
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

# Store edges of indexed coordinates and calculate distanceances between all pairs of cows
edges = [(l_idx, r_idx, (coords[l_idx][0] - coords[r_idx][0])**2 + (coords[l_idx][1] - coords[r_idx][1])**2) for l_idx in range(n - 1) for r_idx in range(l_idx + 1, n)]

# Sort edges by their distanceance
edges.sort(key=lambda x: x[2])

# Union closest cows until all cows are connected
last_distance = 0
dsu = DisjointSetUnion(n)
for l_idx, r_idx, distance in edges:
	if dsu.link(l_idx, r_idx):
		last_distance = distance
		n -= 1
		if n == 1:	# If all cows are connected
			break

# The distanceance of the last unioned edge is the minimum amount to spend
print(last_distance, file=open("moocast.out", "w"))
'''

'''
# Graphs - Binary Search + Breadth-first search (BFS) approach
# T: O(n^2 * log(hi)), M: O(n)
# Where n is the number of cows and hi is the maximum distanceance between any two cows

from collections import deque

with open("moocast.in", "r") as fin:
	# First line: n = number of cows
	n = int(fin.readline().strip())
	# For the next n lines read in coordinates of cows
	coords = [tuple(map(int, fin.readline().split())) for ln in range(n)]

# Breadth-first search (BFS) to find all cows reachable given a distanceance
def all_reachable(spent: int) -> bool:
	q = deque([0])
	seen = set([0])
	while q:
		node = q.popleft()
		nx, ny = coords[node]

		for adj in range(n):
			if adj in seen:
				continue

			ax, ay = coords[adj]
			distanceance = (nx - ax)**2 + (ny - ay)**2
			if distanceance <= spent:
				q.append(adj)
				seen.add(adj)

	return len(seen) == n

# Binary search to find the minimum distanceance/price to spend
min_x, min_y = min(coords)
max_x, max_y = max(coords)
lo, hi = 0, (max_x - min_x)**2 + (max_y - min_y)**2
while lo < hi:
	mid = (lo + hi) // 2
	if (all_reachable(mid)):
		hi = mid
	else:
		lo = mid + 1

# Write binary searched answer to output file
print(lo, file=open("moocast.out", "w"))
'''