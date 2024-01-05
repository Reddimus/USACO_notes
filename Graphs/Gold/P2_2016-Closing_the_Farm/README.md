# [USACO 2016 US Open Contest, Gold](http://www.usaco.org/index.php?page=open16results)
## [Problem 2. Closing the Farm](http://www.usaco.org/index.php?page=viewproblem2&cpid=646)

Farmer John and his cows are planning to leave town for a long vacation, and so FJ wants to temporarily close down his farm to save money in the meantime.

The farm consists of `N` barns connected with `M` bidirectional paths between some pairs of barns `(1≤N, M≤200,000)`. To shut the farm down, FJ plans to close one barn at a time. When a barn closes, all paths adjacent to that barn also close, and can no longer be used.

FJ is interested in knowing at each point in time (initially, and after each closing) whether his farm is "fully connected" -- meaning that it is possible to travel from any open barn to any other open barn along an appropriate series of paths. Since FJ's farm is initially in somewhat in a state of disrepair, it may not even start out fully connected.

### INPUT FORMAT (file closing.in):
The first line of input contains `N` and `M`. The next `M` lines each describe a path in terms of the pair of barns it connects (barns are conveniently numbered `1…N`). The final `N` lines give a permutation of `1…N` describing the order in which the barns will be closed.

### OUTPUT FORMAT (file closing.out):
The output consists of `N` lines, each containing "YES" or "NO". The first line indicates whether the initial farm is fully connected, and line `i+1` indicates whether the farm is fully connected after the `ith` closing.

### SAMPLE INPUT:
```
4 3
1 2
2 3
3 4
3
4
1
2
```

### SAMPLE OUTPUT:
```
YES
NO
YES
YES
```

### Hint:
- Instead of thinking about removing barns, think about adding them. 
    - If you add barns in the reverse order of the given list, you can use a disjoint set union data structure to keep track of which barns are connected to each other.

# [Solutions](https://github.com/Reddimus/USACO_notes/tree/main/Graphs/Gold/P2_2016-Closing_the_Farm)

## Graphs - Disjoint Set Union (DSU) approach

### Steps
1. 

### Time & Space complexity:
Time: `O(N + M * α(N))` ≈ `O(N + M)`
Space: `O(N + M)`

Where `N` is the number of barns and `M` is the number of paths. `α(N)` is the inverse Ackermann function, which is less than 5 for all practical values of `N` which means it is effectively constant.

### Python Code:
```python
class DisjointSetUnion:
	# Initialize nodes to single sized node graphs
	def __init__(self, num_barns: int) -> None:
		self.parent = [*range(num_barns)]
		self.size = [1] * num_barns

	# Recursively find the parent of entire component
	def find_parent(self, v: int) -> int:
		if self.parent[v] == v:
			return v
		# Path compression optimization
		self.parent[v] = self.find_parent(self.parent[v])
		return self.parent[v]
	
	# Attempt to union two components
	def union(self, a: int, b: int) -> bool:
		a, b = self.find_parent(a), self.find_parent(b)
		if a == b:		# If nodes are already in same component
			return False
		
		if self.size[a] < self.size[b]:
			a, b = b, a		# Union by size optimization
		# Merge smaller component (b) into larger component (a)
		self.parent[b] = a
		self.size[a] += self.size[b]
		return True

with open("closing.in", "r") as fin:
	# Read in first line: n = # of barns, m = # of paths
	n, m = map(int, fin.readline().split())
	# For the next m lines, read in the barns connected by a path into graph
	graph = [[] for idx in range(n)]
	for ln in range(m):
		b1, b2 = map(lambda b: int(b) - 1, fin.readline().split())
		graph[b1].append(b2)
		graph[b2].append(b1)
	# For the next n lines, read in the barns to be removed
	remove_order = [int(fin.readline()) - 1 for ln in range(n)]

# In reverse removed order, open barns and union them to any open adjacent barns
dsu = DisjointSetUnion(n)
open_barns = set()
components = 0
fully_connected = []	# List of answer(s) in reversed order
for barn in reversed(remove_order):
	components += 1
	for adj in graph[barn]:
		if adj in open_barns and dsu.union(barn, adj):
			components -= 1	# group barns into one connected component

	fully_connected.append("YES" if components == 1 else "NO")
	open_barns.add(barn)

# Write fully connected barns in removed order to output file
print(*reversed(fully_connected), sep="\n", file=open("closing.out", "w"))
```

### C++ Code:
```cpp
#include <bits/stdc++.h>

using namespace std;

class DisjointSetUnion {
public:
	vector<int> parent;
	vector<int> size;
	// Initialize nodes to single sized node graphs
	DisjointSetUnion(int n) : size(n, 1) {
		for (int node = 0; node < n; ++node)
			parent.push_back(node);
	}

	// Recursively find and assign parent of current node
	int find_parent(int node) {
		if (parent[node] == node) 
			return node;
		// Path compression optimization
		parent[node] = find_parent(parent[node]);
		return parent[node];
	}

	// Attempt to union two components
	bool union_components(int a, int b) {
		a = find_parent(a), b = find_parent(b);
		if (a == b) // If nodes are already in same component
			return false;

		if (size[a] < size[b]) 
			swap(a, b); // Union by size optimization
		// Merge smaller component (b) into larger component (a)
		parent[b] = a;
		size[a] += size[b];
		return true;
	}
};

int main() {
	freopen("closing.in", "r", stdin);
	// Read in first line: n = # of barns, m = # of paths
	int n, m;
	cin >> n >> m;
	// For the next m lines, read in the barns connected by a path into graph
	vector<vector<int>> graph(n);
	for (int ln = 0; ln < m; ++ln) {
		int b1, b2;
		cin >> b1 >> b2;
		graph[--b1].push_back(--b2);
		graph[b2].push_back(b1);
	}
	// For the next n lines, read in the barns to be removed
	vector<int> removeOrder(n);
	for (int ln = 0; ln < n; ++ln) {
		cin >> removeOrder[ln];
		--removeOrder[ln];
	}

	// In reverse removed order, open barns and union them to any open adjacent barns
	DisjointSetUnion dsu(n);
	unordered_set<int> openBarns;
	int components = 0;
	vector<string> fullyConnected;   // List of answer(s) in reversed order
	for (int idx = n - 1; idx >= 0; --idx) {
		int barn = removeOrder[idx];

		++components;
		for (int& adj : graph[barn])
			if (openBarns.find(adj) != openBarns.end() 
			&& dsu.union_components(barn, adj))
				--components;   // group barns into one connected component

		fullyConnected.push_back(components == 1 ? "YES" : "NO");
		openBarns.insert(barn);
	}

	// Write fully connected barns in removed order to output file
	freopen("closing.out", "w", stdout);
	for (int idx = n - 1; idx >= 0; --idx)
		cout << fullyConnected[idx] << '\n';
	return 0;
}
```

### Java Code:
```
```