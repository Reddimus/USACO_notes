# Depth First Search (DFS) | Flood Fill Graph approach
# T & M: O(n^2), where n is the side length of the grid

with open("countcross.in", "r") as f:
	# Read in first line: n = grid side length, k = # of cows, r = # of roads
	n, k, r = map(int, f.readline().split())
	# Read in start (r, c) and end (r', c') positions of two-way roads
	roads = set()
	for ln in range(r):
		sr, sc, er, ec = map(int, f.readline().split())
		roads.add((sr, sc, er, ec))
		roads.add((er, ec, sr, sc))
	# Read in (r, c) positions of cows
	cows = set(tuple(map(int, f.readline().split())) for ln in range(k))

visited = set()

# Depth first search number of cows that can be reached without crossing a road
def dfs(r: int, c: int, prev_r: int, prev_c: int) -> int:
	if (r < 1 or n < r
	or c < 1 or n < c
	or (r, c) in visited
	or (r, c, prev_r, prev_c) in roads):
		return 0
	
	visited.add((r, c))
	cow_count = 1 if (r, c) in cows else 0

	return (cow_count +
	dfs(r + 1, c, r, c) +
	dfs(r - 1, c, r, c) +
	dfs(r, c + 1, r, c) +
	dfs(r, c - 1, r, c))

# Group size of cow components to calculate distant pairs
cow_components = [dfs(r, c, r, c) for r, c in cows]

# Sum product of pairs from distinct cow groups for distant pairs
distant_pairs = 0
for i in range(len(cow_components)):
	for j in range(i + 1, len(cow_components)):
		distant_pairs += cow_components[i] * cow_components[j]

# Write number of distant pairs to output file
print(distant_pairs, file=open("countcross.out", "w"))
