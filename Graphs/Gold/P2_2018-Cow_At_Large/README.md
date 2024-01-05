# [USACO 2018 January Contest, Gold](http://www.usaco.org/index.php?page=jan18results)
## [Problem 2. Cow at Large](http://www.usaco.org/index.php?page=viewproblem2&cpid=790)

Cornered at last, Bessie has gone to ground in a remote farm. The farm consists of `N` barns `(2 <= N <= 10^5)` and `N-1` bidirectional tunnels between barns, so that there is a unique path between every pair of barns. Every barn which has only one tunnel is an exit. When morning comes, Bessie will surface at some barn and attempt to reach an exit.

But the moment Bessie surfaces, the law will be able to pinpoint her location. Some farmers will then start at various exit barns, and attempt to catch Bessie. The farmers move at the same speed as Bessie (so in each time step, each farmer can move from one barn to an adjacent barn). The farmers know where Bessie is at all times, and Bessie knows where the farmers are at all times. The farmers catch Bessie if at any instant a farmer is in the same barn as Bessie, or crossing the same tunnel as Bessie. Conversely, Bessie escapes if she reaches an exit barn before any farms catch her.

Bessie is unsure about her chances of success, which depends on the number of farmers that the law is able to deploy. Given that Bessie surfaces at barn `K`, help Bessie determine the minimum number of farmers who would be needed to catch Bessie, assuming that the farmers distribute themselves optimally among the exit barns.

### INPUT FORMAT (file atlarge.in):
The first line of the input contains `N` and `K`. Each of the following `N−1` lines specify two integers, each in the range `1…N`, describing a tunnel between two barns.

### OUTPUT FORMAT (file atlarge.out):
Please output the minimum number of farmers needed to ensure catching Bessie.

### SAMPLE INPUT:
```
7 1
1 2
1 3
3 4
3 5
4 6
5 7
```

### SAMPLE OUTPUT:
```
3
```

# [Solutions](https://github.com/Reddimus/USACO_notes/tree/main/Graphs/Gold/P2_2018-Cow_At_Large)

## Graphs - Breadth-First Search (BFS) w/ Greedy Approach

### Steps
1. 

### Time & Space complexity:
Time: `O(V + E)`  
Space: `O(V + E)`  

Where `V` and  is the number of vertices/barns and `E` is the number of edges/tunnels.
    - `V = N`

### Python Code:
```python
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
```

### C++ Code:
```cpp
```

### Java Code:
```java
```