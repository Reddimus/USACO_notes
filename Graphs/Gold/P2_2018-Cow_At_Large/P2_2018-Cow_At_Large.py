# Graphs - Breath-First Search (BFS) w/ greedy approach
# T & M: O(V + E), where V = N = # of barns, E = # of paths/tunnels

from collections import deque

with open("atlarge.in", "r") as infile:
	# Read in first line: n = # of barns, k = Bessie's starting barn
	n, k = map(int, infile.readline().split())
	# For the next n - 1 lines, read in the barns connected by a path/tunnel
	graph = [[] for idx in range(n)]
	for ln in range(n - 1):
		t1, t2 = map(lambda t: int(t) - 1, infile.readline().split())
		graph[t1].append(t2)
		graph[t2].append(t1)


exits = [node for node, adj_list in enumerate(graph) if len(adj_list) == 1]
dist_farmer = [float("inf")] * n	# stores min steps for farmer to reach node
for exit_node in exits:
	dist_farmer[exit_node] = 0			# initialize exit nodes to 0 steps

# BFS to compute the minimum steps for farmers to reach each barn from exits
q = deque(exits)
while q:
	qd_barn = q.popleft()

	for adj in graph[qd_barn]:
		# If adjacent barn has not yet been mapped to minumum steps
		if dist_farmer[adj] == float("inf"):
			dist_farmer[adj] = dist_farmer[qd_barn] + 1	# increment farmer's steps
			q.append(adj)

farmers_needed = 0

dist_bessie = [float("inf")] * n	# stores min steps for bessie to reach node
dist_bessie[k - 1] = 0				# initialize Bessie's starting node to 0 steps

# As Bessie explores the graph, count the farmers needed to catch her using BFS
q = deque([k - 1])
while q:
	qd_barn = q.popleft()

	# If Bessie's current step count >= farmer's current step count
	if dist_bessie[qd_barn] >= dist_farmer[qd_barn]:
		farmers_needed += 1	# A farmer could catch Bessie at this barn
		continue			# no need to explore subgraph further

	for adj in graph[qd_barn]:
		# If adjacent barn has not yet been visited by Bessie
		if dist_bessie[adj] == float("inf"):
			dist_bessie[adj] = dist_bessie[qd_barn] + 1	# increment Bessie's steps
			q.append(adj)

# Write the number of farmers needed to catch Bessie to output file
print(farmers_needed, file=open("atlarge.out", "w"))