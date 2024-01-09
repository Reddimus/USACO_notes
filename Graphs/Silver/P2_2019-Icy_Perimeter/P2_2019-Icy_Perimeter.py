# Breadth First Search (BFS) | Flood fill Graph approach
# T & M: O(n^2) where n is the side length of the grid

from collections import deque

with open("perimeter.in", "r") as fin:
	# First line: n = sides of graph
	n = int(fin.readline())
	# For the next n lines read n sized strings representing ice cream blob graph
	graph = [list(fin.readline().strip()) for ln in range(n)]

directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

# Breadth First Search (BFS) perimeter and area of blob
def bfs(r: int, c: int) -> tuple:
	area, perimeter = 1, 0
	graph[r][c] = ' '	# mark as visited
	q = deque([(r, c)])
	while q:
		qr, qc = q.popleft()

		for dr, dc in directions:
			ar, ac = qr + dr, qc + dc
			# If adjacent row/col outside of blob
			if (ar < 0 or n <= ar or
			ac < 0 or n <= ac or
			graph[ar][ac] == '.'):
				perimeter += 1
			# Else if adjacent row/col is part of the same blob component
			elif (graph[ar][ac] == '#'):
				area += 1
				graph[ar][ac] = ' '
				q.append((ar, ac))
	return (area, perimeter)
	
largest_blob = (0, n + 1)	# largest_blob = area, perimeter
for r in range(n):
	for c in range(n):
		# Group blobs into their own components and update largest blob
		if graph[r][c] == '#':
			blob = bfs(r, c)
			# Update blob to largest area then smallest perimeter
			if (largest_blob[0] < blob[0] or
			(largest_blob[0] == blob[0] and largest_blob[1] > blob[1])):
				largest_blob = blob

# Write largest blob with smallest perimeter to output file
print(f"{largest_blob[0]} {largest_blob[1]}", file=open("perimeter.out", "w"))