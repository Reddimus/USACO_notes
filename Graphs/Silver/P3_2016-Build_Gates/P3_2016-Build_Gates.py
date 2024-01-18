# Graphs - Flood Fill approach
# T & M: O(x * y + n)
# Where x & y are the number of steps between the min and max x/y coordinates of the fence and n is the number of steps Farmer John takes

with open("gates.in", "r") as fin:
	n = int(fin.readline().strip())	# Number of steps
	moves = fin.readline().strip()	# Directions of steps

# Initialize starting position and set of fence coordinates
x = y = 0
fences = set([(x, y)])
min_x = min_y = n
max_x = max_y = -n

# Track fence positions based on Farmer John's movements
for move in moves:
	# Scale movements by 2 steps to view smallest regions
	if move == 'N':
		y += 1
		fences.add((x, y))
		y += 1
		max_y = max(max_y, y)
	elif move == 'E':
		x += 1
		fences.add((x, y))
		x += 1
		max_x = max(max_x, x)
	elif move == 'S':
		y -= 1
		fences.add((x, y))
		y -= 1
		min_y = min(min_y, y)
	else:
		x -= 1
		fences.add((x, y))
		x -= 1
		min_x = min(min_x, x)
	fences.add((x, y))

# Expand boundaries to include outer region surrounding the fence
min_x -= 1
min_y -= 1
max_x += 1
max_y += 1

# Iteratively flood-fill/search for current component
seen = set()
def ff(x: int, y: int):
	stack = [(x, y)]	# First come, last out
	while stack:
		x, y = stack.pop()
		if (x < min_x or max_x < x or
		y < min_y or max_y < y or
		(x, y) in seen or 
		(x, y) in fences):
			continue

		seen.add((x, y))

		stack.append((x + 1, y))
		stack.append((x - 1, y))
		stack.append((x, y + 1))
		stack.append((x, y - 1))

# Find number of regions our fence graph is split into
regions = 0
for x in range(min_x, max_x + 1):
	for y in range(min_y, max_y + 1):
		if (x, y) not in seen and (x, y) not in fences:
			ff(x, y)
			regions += 1

# Every region inside the fences needs a gate
print(regions - 1, file=open("gates.out", "w"))