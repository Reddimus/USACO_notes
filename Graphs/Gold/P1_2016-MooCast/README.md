# [USACO 2016 December Contest, Gold](http://www.usaco.org/index.php?page=dec16results)
## [Problem 1. Moocast](http://www.usaco.org/index.php?page=viewproblem2&cpid=669)

Farmer John's `N` cows `(1≤N≤1000)` want to organize an emergency "moo-cast" system for broadcasting important messages among themselves.

Instead of mooing at each-other over long distances, the cows decide to equip themselves with walkie-talkies, one for each cow. These walkie-talkies each have a limited transmission radius, but cows can relay messages to one-another along a path consisting of several hops, so it is not necessary for every cow to be able to transmit directly to every other cow.

The cows need to decide how much money to spend on their walkie-talkies. If they spend $X, they will each get a walkie-talkie capable of transmitting up to a distance of `sqrt(X)`. That is, the squared distance between two cows must be at most `X` for them to be able to communicate.

Please help the cows determine the minimum integer value of `X` such that a broadcast from any cow will ultimately be able to reach every other cow.

### INPUT FORMAT (file moocast.in):

The first line of input contains `N`.

The next `N` lines each contain the `x` and `y` coordinates of a single cow. These are both integers in the range `0…25,000`.

### OUTPUT FORMAT (file moocast.out):

Write a single line of output containing the integer `X` giving the minimum amount the cows must spend on walkie-talkies.

### SAMPLE INPUT:

```
4
1 3
5 4
7 2
6 1
```

### SAMPLE OUTPUT:

```
17
```

# [Solutions](https://github.com/Reddimus/USACO_notes/tree/main/Graphs/Gold/P1_2016-MooCast)

## Graphs - Disjoint Set Union (DSU) approach

### Steps
1.

### Time & Space complexity:
Time: `O(N^2 * log(N))`  
Space: `O(N^2)`

Where `N` is the number of cows. `α(N)` is the inverse Ackermann function which means it is effectively constant.

### Python Code:
```python
class DisjointSetUnion:
	# Initialize nodes to single sized node graphs
	def __init__(self, n: int) -> None:
		self.parent = [*range(n)]
		self.size = [1] * n

	# Recursively find and assign parent of current node
	def get_parent(self, v: int) -> int:
		if self.parent[v] == v:
			return v
		# Path compression optimization
		self.parent[v] = self.get_parent(self.parent[v])
		return self.parent[v]
	
	# Attempt to union two components
	def link(self, a: int, b: int) -> bool:
		a, b = self.get_parent(a), self.get_parent(b)
		if a == b:		# If nodes are already in same component
			return False
		
		if self.size[a] < self.size[b]:
			a, b = b, a		# Union by size optimization
		# Merge smaller component (b) into larger component (a)
		self.parent[b] = a
		self.size[a] += self.size[b]
		return True

with open("moocast.in", "r") as fin:
	# First line: n = number of cows
	n = int(fin.readline().strip())
	# For the next n lines read in coordinates of cows
	coords = [tuple(map(int, fin.readline().split())) for ln in range(n)]

# Store edges of indexed coordinates and calculate distances between all pairs of cows
edges = [(l_idx, r_idx, (coords[l_idx][0] - coords[r_idx][0])**2 + (coords[l_idx][1] - coords[r_idx][1])**2) for l_idx in range(n - 1) for r_idx in range(l_idx + 1, n)]

# Sort edges by their distance
edges.sort(key=lambda x: x[2])

# Union closest cows until all cows are connected
last_dist = 0
dsu = DisjointSetUnion(n)
for l_idx, r_idx, dist in edges:
	if dsu.link(l_idx, r_idx):
		last_dist = dist
		n -= 1
		if n == 1:	# If all cows are connected
			break

# The distance of the last unioned edge is the minimum amount to spend
print(last_dist, file=open("moocast.out", "w"))
```

### C++ Code:
```cpp
#include <bits/stdc++.h>

using namespace std;

class DisjointSetUnion {
private:
	vector<int> parent;
	vector<int> size;
public:
	// Initialize nodes to single sized node graphs
	DisjointSetUnion(int n) : size(n, 1) {
		for (int node = 0; node < n; ++node)
			parent.push_back(node);
	}

	// Recursively find and assign parent of current node (path compression)
	int get_parent(int v) {
		return (v == parent[v]) ? v : (parent[v] = get_parent(parent[v]));
	}

	// Attempt to union two components
	bool link(int a, int b) {
		a = get_parent(a), b = get_parent(b);
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
	freopen("moocast.in", "r", stdin);
	// First line: n = number of cows
	int n;
	cin >> n;
	// For the next n lines read in coordinates of cows
	vector<pair<int, int>> coords(n);
	for (int idx = 0; idx < n; ++idx)
		cin >> coords[idx].first >> coords[idx].second;
	
	// Store edges and calculated distance between cows
	vector<tuple<int, int, int>> edges;
	for (int i = 0; i < n - 1; ++i) {
		// Calculate distance between cow i and all other cows
		for (int j = i + 1; j < n; ++j) {
			int dx = coords[i].first - coords[j].first;
			int dy = coords[i].second - coords[j].second;
			edges.push_back(make_tuple(i, j, (dx * dx) + (dy * dy)));
		}
	}

	// Sort edges by their distance
	sort(edges.begin(), edges.end(), 
	[](tuple<int, int, int> a, tuple<int, int, int> b) {
		return get<2>(a) < get<2>(b);
	});

	// Union closest cows until all cows are connected
	int lastDist = 0;
	DisjointSetUnion dsu(n);
	for (tuple<int, int, int>& e : edges) {
		if (dsu.link(get<0>(e), get<1>(e))) {
			lastDist = get<2>(e);
			if (--n == 1)	// If all cows are connected
				break;
		}
	}

	// The distance of the last unioned edge is the minimum amount to spend
	freopen("moocast.out", "w", stdout);
	cout << lastDist << endl;
	return 0;
}
```

## Graphs - Minimum Spanning Tree (MST) approach

### Steps
1.

### Time & Space complexity:
Time: `O(N^2)`  
Space: `O(N)`

Where `N` is the number of cows. 

### Python Code:
```python
with open("moocast.in", "r") as fin:
	# First line: n = number of cows
	n = int(fin.readline().strip())
	# For the next n lines read in coordinates of cows
	coords = [tuple(map(int, fin.readline().split())) for ln in range(n)]

# Initialize distance hashmap (x, y) -> distance and answer variable
distance = {coord: float("inf") for coord in coords}
distance[coords[0]] = 0
spend = 0

# For every cow, find the closest cow and update answer
for cow in range(n):
	ax, ay = min(distance, key=distance.get)	# Get smallest coordinate
	spend = max(spend, distance[(ax, ay)])
	del distance[(ax, ay)]
	# For every other non-visited/deleted coordinate, update distance
	for bx, by in distance.keys():
		curr_distance = (ax - bx)**2 + (ay - by)**2
		distance[(bx, by)] = min(distance[(bx, by)], curr_distance)

# Write the minimum distance/price to spend to the output file
print(spend, file=open("moocast.out", "w"))
```

### C++ Code:
```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("moocast.in", "r", stdin);
	// First line: n = number of cows
	int n;
	cin >> n;
	// For the next n lines read in coordinates of cows
	vector<pair<int, int>> coords(n);
	for (int idx = 0; idx < n; ++idx)
		cin >> coords[idx].first >> coords[idx].second;

	// Initialize answer and distance array (idx of coordinate -> distance)
	vector<int> distance(n, INT_MAX - 1);
	distance[0] = 0;
	int spend = 0;

	// For every cow, find the closest cow and update answer
	for (int cow = 0; cow < n; ++cow) {
		int i = min_element(distance.begin(), distance.end()) - distance.begin();
		spend = max(spend, distance[i]);
		distance[i] = INT_MAX;
		for (int j = 0; j < n; ++j) {
			if (distance[j] == INT_MAX)
				continue;
			int dx = coords[i].first - coords[j].first;
			int dy = coords[i].second - coords[j].second;
			int dist = (dx * dx) + (dy * dy);
			distance[j] = min(distance[j], dist);
		}
	}

	// Write the minimum distance/price to spend to the output file
	freopen("moocast.out", "w", stdout);
	cout << spend << endl;
	return 0;
}
```
