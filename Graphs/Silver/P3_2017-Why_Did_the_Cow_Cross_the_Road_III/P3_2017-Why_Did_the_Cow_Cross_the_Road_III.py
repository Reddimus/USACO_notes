import collections

with open("countcross.in", "r") as f:
	n, k, r = map(int, f.readline().split())
	# Create n * n grid/graph
	# grid = [[False] * n for r in range(n)]
	# Read in start (r, c) and end (r', c') positions of roads
	roads = set()
	for ln in range(r):
		r0, c0, r1, r2 = map(int, f.readline().split())
		roads.add((r0, c0))
		roads.add((r1, r2))
	# Read in positions of cows
	cows = set(tuple(map(int, f.readline().split())) for ln in range(k))
	# for ln in range(k):
	# 	r, c = map(int, f.readline().split())
	# 	grid[r-1][c-1] = True

	# cows = [tuple(map(int, f.readline().split())) for ln in range(k)]

# for road in list(roads):
# 	if road not in cows:
# 		roads.remove(road)

directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

def bfs(r: int, c: int) -> int:	
	pairs = 0
	q = collections.deque([(r, c)])
	visited = set()

	while q:
		# print(q)
		# print(f"cows: {cows}")
		# print(f"pairs: {pairs}")
		# print(f"visited: {visited}")
		# print()
		cr, cc = q.popleft()
		if (cr, cc) in cows:
			cows.remove((cr, cc))

		for dr, dc in directions:
			nr, nc = cr + dr, cc + dc

			if (1 <= nr <= n and 1 <= nc <= n and
			(cr, cc, nr, nc) not in visited and 
			(nr, nc, cr, cc) not in visited and
			(nr, nc) in roads and (nr, nc) in cows):
				q.append((nr, nc))
				visited.add((cr, cc, nr, nc))
				visited.add((nr, nc, cr, cc))
				pairs += 1

	return pairs

# def dfs(r: int, c: int) -> int:
# 	if (r < 0 or n < r or
# 	c < 0 or n < c or 
# 	(r, c) not in roads or 
# 	(r, c) not in cows or
	
# 		return 0
	
# 	visited.add((r, c))
# 	# cows.remove((r, c))

# 	for dr, dc in directions:
# 		nr, nc = r + dr, c + dc
# 		if (nr, nc) in roads:
# 			visited.add((r, c, nr, nc))
# 			visited.add((nr, nc, r, c))

# 	return (1 +
# 	dfs(r+1, c) +
# 	dfs(r-1, c) +
# 	dfs(r, c+1) +
# 	dfs(r, c-1))

# print(roads)
# print()

distant_cows = 0
for r, c in list(cows):
	if (r, c) in cows:
		distant_cows += bfs(r, c)

# 	print(r, c)
# 	print(distant_cows)
# 	print(cows)
# 	print()

# print(roads)
# print(distant_cows)
print(distant_cows, file=open("countcross.out", "w"))

'''
input:
3 3 3
2 1 2 2
2 2 2 3
2 2 3 2
3 3 3 2
3 3 2 3
3 2 3 1
3 1 2 1
3 3
2 2
2 3
2 1
3 1
3 2

[0, 0, 0]
[1, 1, 1]
[1, 1, 1]
'''