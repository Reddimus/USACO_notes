# [USACO 2016 January Contest, Silver](http://www.usaco.org/index.php?page=jan16results)
## [Problem 3. Build Gates](http://www.usaco.org/index.php?page=viewproblem2&cpid=596)

Farmer John decides to build a new fence around parts of his farm, but he keeps getting distracted and ends up building the fence into a much stranger shape than he intended!

Specifically, FJ starts at position `(0,0)` and takes `N` steps, each moving one unit of distance north, south, east, or west. Each step he takes, he lays a unit of fence behind him. For example, if his first step is to the north, he adds a segment of fence from `(0,0)` to `(0,1)`. FJ might re-visit points multiple times and he may even lay the same segment of fence multiple times. His fence might even cross over itself if his path cuts through a run of fencing he has already built.

Needless to say, FJ is rather dismayed at the result after he completes the fence. In particular, he notices that it may be the case that he has now partitioned off some areas of the farm from others, so that one can no longer walk from one region to another without crossing a fence. FJ would like to add gates to his fences to fix this problem. A gate can be added to any unit-length segment of fence he has built, allowing passage between the two sides of this segment.

Please determine the minimum number of gates FJ needs to build so that every region of the farm is once again reachable from every other region.

### INPUT FORMAT (file gates.in):

The first line of input contains `N` `(1≤N≤1000)`. The next line contains a string of length `N` describing FJ's path. Each character is either `N (north)`, `E (east)`, `S (south)`, or `W (west)`.

### OUTPUT FORMAT (file gates.out):

Write out a single integer giving the minimum number of gates FJ needs to build to restore complete connectivity to all regions of his farm. Note that the answer could be zero if the farm is connected to begin with.

### SAMPLE INPUT:

```
14
NNNESWWWSSEEEE
```

### SAMPLE OUTPUT:

```
2
```

### Hints:
- Think of how to initialize your coordinate plane for your fences graph.
	- What should the boundaries be for your coordinate plane?
	- What should the origin be?
	- How can you represent the smallest regions of the inner fences?

## Graphs - Flood Fill approach

### Steps
1. Read in the input file `gates.in`.
	- First line: `N = Total number of steps`
	- Second line: `N` characters representing the direction (`North`, `East`, `South`, `West`) of each step.
2. Initialize the coordinates data structure to represent the graph of the fences.

### Time & Space complexity notation:
- Where `N` is the number of steps. 
- Where `X` & `Y` are the number of steps between the minimum and maximum `X` & `Y` coordinates of the fences.

### Python code
Time & Space complexity: `O(X * Y + N)`  
```python
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
```

### C++ code
```cpp
```

### Java code
```java
```
