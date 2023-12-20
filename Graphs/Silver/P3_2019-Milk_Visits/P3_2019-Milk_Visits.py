
with open('milkvisits.in', 'r') as f:
	# First line: n = num of farms, m = FJ's friends
	n, m  = map(int, f.readline().split())
	# Second line: string of farm types
	farm_types = f.readline()
	# For the next n-1 lines read in the edges of the graph
	roads = {}
	for ln in range(n-1):
		x, y = map(int, f.readline().split())
		roads[x] = roads.get(x, []) + [y]
		roads[y] = roads.get(y, []) + [x]

	def satisfies(start: int, end: int, prefered: str) -> bool:
		# DFS path from start to end
		path = []
		visited = set()
		def dfs() -> bool:

	# For the next m lines read & check friend's path satisfies them
	satisfied = ""
	for ln in range(m):
		x, y, prefered = f.readline().split()
		if satisfies(int(x), int(y), prefered):
			satisfied += '1'
		else:
			satisfied += '0'

print(satisfied, file=open("milkvisits.out", "w"))
