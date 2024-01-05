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

### Hints:
- How can we preprocess the farmer's steps to each barn?
- If the farmer's preprocessed steps are less than or equal to Bessie's steps at the same barn then the farmer can catch Bessie at that barn.

# [Solutions](https://github.com/Reddimus/USACO_notes/tree/main/Graphs/Gold/P2_2018-Cow_At_Large)

## Graphs - Breadth-First Search (BFS) w/ Greedy Approach

### Steps
1. **Read in the input file:**
	- First line: `n = number of barns`, `k = Bessie's starting barn`.
	- For the next `n - 1` lines, create a graph representing the farm, reading in edges `t1` and `t2` that connect the barns.

2. **Identify Exit Barns:**
	- Create a list of `exits` containing all barns with only one connection (tunnel), which are potential escape points for Bessie.

3. **Calculate Minimum Steps for Farmers:**
	- **Initialize:** Create a `dist_farmer` array to store the minimum steps for a farmer to reach each barn from the nearest exit. Initialize each barn's distance as `infinity`.
	- **Set Exit Barns:** Set the distance for each exit barn in `dist_farmer` to `0`, representing the starting points for farmers.
	- **BFS from Exits:** Perform Breadth-First Search starting from each exit barn to calculate the minimum number of steps required for a farmer to reach every other barn. Update `dist_farmer` accordingly.
		- Enqueue all exit barns, and for each barn dequeued, update the distance for its adjacent barns if not already visited by a farmer.

4. **Determine Farmers Needed to Catch Bessie:**
	- **Initialize:** Set `farmers_needed` to `0` and create a `dist_bessie` array, similar to `dist_farmer`, to track the minimum steps for Bessie to reach each barn from her starting position.
	- **Set Bessie's Starting Barn:** Initialize the distance for Bessie's starting barn in `dist_bessie` to `0`.
	- **BFS from Bessie's Barn:** Use Breadth-First Search to explore all possible paths Bessie can take from her starting barn.
		- For each barn visited by Bessie, compare her distance to the farmer's distance (from `dist_farmer`). If a farmer can reach the barn in the same or fewer steps than Bessie, increment `farmers_needed`. This indicates a farmer can intercept Bessie at this barn.
		- Continue exploring until all potential escape paths are covered.

5. **Write the number of farmers needed to catch Bessie to output file**

### Time & Space complexity:
Time: `O(V + E)`  
Space: `O(V + E)`  

Where `V` and  is the number of vertices/barns and `E` is the number of edges/tunnels.  
	- `V = N`, where `N` is also the number of barns.

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
#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("atlarge.in", "r", stdin);
	// Read in first line: n = # of barns, k = Bessie's starting barn
	int n, k;
	cin >> n >> k;
	// For the next n - 1 lines, read in the barns connected by a path/tunnel
	vector<vector<int>> graph(n);
	for (int ln = 0; ln < n - 1; ++ln) {
		int t1, t2;
		cin >> t1 >> t2;
		graph[--t1].push_back(--t2);
		graph[t2].push_back(t1);
	}

	vector<int> exits;
	for (int idx = 0; idx < n; ++idx)
		if (graph[idx].size() == 1)
			exits.push_back(idx);

	vector<int> distFarmer(n, -1);	// stores min steps for farmer to reach node
	for (int& exit : exits)
		if (distFarmer[exit] == -1)
			distFarmer[exit] = 0;	// initialize exit nodes to 0 steps

	// BFS to compute the minimum steps for farmers to reach each barn from exits
	queue<int> q;
	for (int& exit : exits)
		q.push(exit);
	while (!q.empty()) {
		int qdBarn = q.front();
		q.pop();

		for (int& adj : graph[qdBarn]) {
			// If adjacent barn has not yet been mapped to minumum steps
			if (distFarmer[adj] == -1) {
				distFarmer[adj] = distFarmer[qdBarn] + 1;	// increment farmer's steps
				q.push(adj);
			}
		}
	}

	int farmersNeeded = 0;
	
	vector<int> distBessie(n, -1);	// stores min steps for bessie to reach node
	distBessie[k - 1] = 0;			// initialize Bessie's starting node to 0 steps

	// As Bessie explores the graph, count the farmers needed to catch her using BFS
	q.push(k - 1);
	while (!q.empty()) {
		int qdBarn = q.front();
		q.pop();

		// If Bessie's current step count >= farmer's current step count
		if (distBessie[qdBarn] >= distFarmer[qdBarn]) {
			++farmersNeeded;	// A farmer could catch Bessie at this barn
			continue;			// no need to explore subgraph further
		}

		for (int& adj : graph[qdBarn]) {
			// If adjacent barn has not yet been visited by Bessie
			if (distBessie[adj] == -1) {
				distBessie[adj] = distBessie[qdBarn] + 1;	// increment Bessie's steps
				q.push(adj);
			}
		}
	}

	// Write the number of farmers needed to catch Bessie to output file
	freopen("atlarge.out", "w", stdout);
	cout << farmersNeeded << endl;
	return 0;
}
```

### Java Code:
```java
import java.io.*;
import java.util.*;

public class CowAtLarge {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("atlarge.in"));
		// Read in first line: n = # of barns, k = Bessie's starting barn
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		// For the next n - 1 lines, read in the barns connected by a path/tunnel
		ArrayList<Integer>[] graph = new ArrayList[n + 1];
		for (int idx = 0; idx < n + 1; ++idx)
			graph[idx] = new ArrayList<>();
		for (int ln = 0; ln < n - 1; ++ln) {
			st = new StringTokenizer(in.readLine());
			int t1 = Integer.parseInt(st.nextToken());
			int t2 = Integer.parseInt(st.nextToken());
			graph[t1].add(t2);
			graph[t2].add(t1);
		}
		in.close();

		ArrayList<Integer> exits = new ArrayList<>();
		for (int idx = 1; idx <= n; ++idx)
			if (graph[idx].size() == 1)
				exits.add(idx);

		int[] distFarmer = new int[n + 1];	// stores min steps for farmer to reach node
		Arrays.fill(distFarmer, -1);
		for (int exit : exits)
			distFarmer[exit] = 0;			// initialize exit nodes to 0 steps

		// BFS to compute the minimum steps for farmers to reach each barn from exits
		Queue<Integer> q = new LinkedList<>(exits);
		while (!q.isEmpty()) {
			int qdBarn = q.poll();

			for (int adj : graph[qdBarn]) {
				// If adjacent barn has not yet been mapped to minumum steps
				if (distFarmer[adj] == -1) {
					distFarmer[adj] = distFarmer[qdBarn] + 1;	// increment farmer's steps
					q.add(adj);
				}
			}
		}

		int farmersNeeded = 0;

		// stores min steps for bessie to reach node
		int[] distBessie = new int[n + 1];
		Arrays.fill(distBessie, -1);
		distBessie[k] = 0;	// initialize Bessie's starting node to 0 steps

		// As Bessie explores the graph, count the farmers needed to catch her using BFS
		q.add(k);
		while (!q.isEmpty()) {
			int qdBarn = q.poll();

			// If Bessie's current step count >= farmer's current step count
			if (distBessie[qdBarn] >= distFarmer[qdBarn]) {
				++farmersNeeded;
				continue;
			}

			for (int adj : graph[qdBarn]) {
				// If adjacent barn has not yet been visited by Bessie
				if (distBessie[adj] == -1) {
					distBessie[adj] = distBessie[qdBarn] + 1;	// increment Bessie's steps
					q.add(adj);
				}
			}
		}

		// Write the number of farmers needed to catch Bessie to output file
		PrintWriter out = new PrintWriter("atlarge.out");
		out.println(farmersNeeded);
		out.close();
	}
}
```