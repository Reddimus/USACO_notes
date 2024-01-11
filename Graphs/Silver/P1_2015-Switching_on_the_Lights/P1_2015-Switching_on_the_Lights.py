# Graphs - Breadth First Search (DFS) | Flood fill approach
# T & M: O(n^2 + m)
# Where n is the number of rows and columns in the switches graph and m is the number of switches

from collections import deque

with open("lightson.in", "r") as fin:
	# First line: n = graph side length, m = # of switches
	n, m = map(int, fin.readline().split())
	# For the next m lines map x, y room to room a, b that can be lit
	graph = {}	# 1-indexed
	for ln in range(m):
		x, y, a, b = map(int, fin.readline().split())
		graph[(x, y)] = graph.get((x, y), []) + [(a, b)]

lit = {(1, 1)}
seen = set()
directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
q = deque([(1, 1)])

# Breadth First Search (BFS) lit rooms
while q:
	r, c = q.popleft()
	if (r, c) in seen:
		continue
	seen.add((r, c))

	# Turn on new lights of current room
	if (r, c) in graph:
		for sr, sc in graph[(r, c)]:
			if (sr, sc) in lit:
				continue
			lit.add((sr, sc))
			# Check if the newly lit room can be connected and hasn't been visited
			q += [(sr, sc) for dr, dc in directions if (sr + dr, sc + dc) in seen and (sr, sc) not in seen]

	# Explore valid adjacent rooms
	q += [(r + dr, c + dc) for dr, dc in directions if (r + dr, c + dc) in lit and (r + dr, c + dc) not in seen]

# Write number of lit rooms accessible from (1, 1) to output file
print(len(lit), file=open("lightson.out", "w"))

'''
# Graphs - Depth First Search (DFS) | Flood fill approach
# T & M: O(n^2 + m) where n is the number of rooms and m is the number of switches

with open("lightson.in", "r") as fin:
	# First line: n = # of rooms, m = # of switches
	n, m = map(int, fin.readline().split())
	# For the next m lines map x, y room to room a, b that can be lit
	graph = {}	# 1-indexed
	for ln in range(m):
		x, y, a, b = map(int, fin.readline().split())
		graph[(x, y)] = graph.get((x, y), []) + [(a, b)]

lit = {(1, 1)}
seen = set()
directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
stack = [(1, 1)]

# Iteratively Depth First Search (DFS) lit rooms
while stack:
	r, c = stack.pop()
	if (r, c) in seen:
		continue
	seen.add((r, c))

	# Turn on new lights of current room
	if (r, c) in graph:
		for sr, sc in graph[(r, c)]:
			lit.add((sr, sc))
			# Check if the newly lit room can be connected and hasn't been visited
			stack += [(sr, sc) for dr, dc in directions if (sr + dr, sc + dc) in seen and (sr, sc) not in seen]

	# Explore valid adjacent rooms
	stack += [(r + dr, c + dc) for dr, dc in directions if (r + dr, c + dc) in lit and (r + dr, c + dc) not in seen]

# Write number of lit rooms accessible from (1, 1) to output file
print(len(lit), file=open("lightson.out", "w"))
'''