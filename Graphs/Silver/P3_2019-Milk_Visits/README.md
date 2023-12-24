# [USACO 2019 December Contest, Silver](http://www.usaco.org/index.php?page=dec19results)
## [Problem 3. Milk Visits](http://www.usaco.org/index.php?page=viewproblem2&cpid=968)

Farmer John is planning to build `N (1 ≤ N ≤ 10 ^5)` farms that will be connected by `N−1` roads, forming a tree (i.e., all farms are reachable from each-other, and there are no cycles). Each farm contains a cow, whose breed is either Guernsey or Holstein.

Farmer John's `M` friends `(1 ≤ M ≤ 10^5)` often come to visit him. During a visit with friend i, Farmer John will walk with his friend along the unique path of roads from farm `Ai` to farm `Bi` (it may be the case that `Ai = Bi`). Additionally, they can try some milk from any cow along the path they walk. Since most of Farmer John's friends are also farmers, they have very strong preferences regarding milk. Some of his friends will only drink Guernsey milk, while the remainder will only drink Holstein milk. Any of Farmer John's friends will only be happy if they can drink their preferred type of milk during their visit.

Please determine whether each friend will be happy after visiting.

### SCORING:
	- Test cases 2-4 satisfy `N ≤ 10^3, M ≤ 10^3`.

### INPUT FORMAT (file milkvisits.in):
The first line of input contains `N` and `M`.

The second line contains a string of length `N`. The *ith* character of the string is 'G' if the cow in the *ith* farm is a Guernsey, or 'H' if the cow in the *ith* farm is a Holstein.

The next `N−1` lines each contain two distinct integers `X` and `Y` `(1 ≤ X, Y ≤ N)`, indicating that there is a road between farms `X` and `Y`.

The next `M` lines contain integers `A_i`, `B_i`, and a character `C_i`. `A_i` and `B_i` represent the endpoints of the path walked during friend *i's* visit, while `C_i` is either G or H if the *ith* friend prefers Guernsey milk or Holstein milk.

### OUTPUT FORMAT (file milkvisits.out):
Print a binary string of length `M`. The *ith* character of the string should be '1' if the *ith* friend will be happy, or '0' otherwise.

### SAMPLE INPUT
```
5 5
HHGHG
1 2
2 3
2 4
1 5
1 4 H
1 4 G
1 3 G
1 3 H
5 5 H
```

### SAMPLE OUTPUT
```
10110
```

Here, the path from farm 1 and farm 4 involves farms 1, 2, and 4. All of these contain Holsteins, so the first friend will be satisfied while the second one will not.

# [Solutions](https://github.com/Reddimus/USACO_notes/tree/main/Graphs/Silver/P3_2019-Milk_Visits)

## Graphs - Breadth First Search (BFS) w/ Connected Components detection

### Steps
1. 

### Time & Space complexity:
Time: `O(n + m)` | `O(V + E)`  
Space: `O(n + m)` | `O(V + E)`  

Where `n` is number of farms, `m` is number farmer John's friends, `V` is number of vertices, and `E` is number of edges.

### Python Code
```python
```

### C++ Code:
```cpp
// Breadth First Search (BFS) w/ Connected Components detection Graph approach
// T & M: O(n + m) | O(V + E), where n = num of farms, m = num of friends

#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("milkvisits.in", "r", stdin);
	// Read in First line: n = num of farms, m = num of FJ's friends
	int n, m;
	cin >> n >> m;

	// Second line: string of farm types
	vector<char> milkTypes(n + 1);
	for (int idx = 1; idx <= n; ++idx)
		cin >> milkTypes[idx];

	// For the next n-1 lines read in the edges of the graph
	vector<vector<int>> farms(n + 1);
	for (int ln = 0; ln < n - 1; ++ln) {
		int x, y;
		cin >> x >> y;
		farms[x].push_back(y);
		farms[y].push_back(x);
	}

	// Process the tree & detect the different components
	vector<int> components(n + 1, -1);
	for (int farm = 1; farm <= n; ++farm) {
		// Don't process a farm if it's been visited already
		if (components[farm] != -1)
			continue;
		
		// BFS to find all the farms in the same subtree
		char type = milkTypes[farm];
		queue<int> q;
		q.push(farm);
		while (!q.empty()) {
			int qdFarm = q.front();
			q.pop();
			
			// Mark the queue'd farm as same path as current component (farm)
			components[qdFarm] = farm;

			// Visit a neighbor if it's new & is of the same type
			for (int& neighbor : farms[qdFarm])
				if (milkTypes[neighbor] == type && components[neighbor] == -1)
					q.push(neighbor);
		}
	}

	// For the next m lines read & check if friend's path satisfies them
	string ans = "";
	for (int ln = 0; ln < m; ++ln) {
		int start, end;
		char preference;
		cin >> start >> end >> preference;

		if (components[start] == components[end] && milkTypes[start] != preference)
			ans += '0';
		else
			ans += '1';
	}
	
	// Write satisfaction of each friend in sting form to output file
	freopen("milkvisits.out", "w", stdout);
	cout << ans << endl;
	return 0;
}
```

### Java Code:
```java
```