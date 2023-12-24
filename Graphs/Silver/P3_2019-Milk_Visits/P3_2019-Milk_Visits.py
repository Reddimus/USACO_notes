# Breadth First Search (BFS) w/ Connected Components detection Graph approach
# T & M: O(n + m) | O(V + E), where n = num of farms, m = num of friends

import collections

with open("milkvisits.in", "r") as f:
	# Read in First line: n = num of farms, m = num of FJ's friends
	n, m = map(int, f.readline().split())

	# Second line: string of farm types
	milk_types = " " + f.readline()
	
	# For the next n-1 lines read in the edges of the graph
	farms = [[] for idx in range(n + 1)]
	for ln in range(n-1):
		x, y = map(int, f.readline().split())
		farms[x].append(y)
		farms[y].append(x)

	# Process the tree & detect the different components
	components = [-1] * (n + 1)
	for farm in range(1, n + 1):
		# Don't process a farm if it's been visited already
		if components[farm] != -1:
			continue

		# BFS to find all the farms in the same subtree
		type = milk_types[farm]
		q = collections.deque([farm])
		while q:
			qdFarm = q.popleft()

			# Mark the queue'd farm as same path as current component (farm)
			components[qdFarm] = farm

			# Visit a neighbor if it's new & is of the same type
			for neighbor in farms[qdFarm]:
				if milk_types[neighbor] == type and components[neighbor] == -1:
					q.append(neighbor) 

	# For the next m lines read & check if friend's path satisfies them
	ans = ""
	for ln in range(m):
		start, end, preference = f.readline().split()

		single_type = components[int(start)] == components[int(end)]
		same_preference = milk_types[int(start)] == preference

		if single_type and not same_preference:
			ans += '0'
		else:
			ans += '1'

# Write satisfaction of each friend in sting form to output file
print(ans, file=open("milkvisits.out", "w"))
