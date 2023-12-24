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

### Hints:
- Try to find a way to determine whether two farms are in the same connected component of the graph. This can be done with a depth-first search or breadth-first search.

# [Solutions](https://github.com/Reddimus/USACO_notes/tree/main/Graphs/Silver/P3_2019-Milk_Visits)

## Graphs - Breadth First Search (BFS) w/ Connected Components detection

### Steps
1. Read in first line: `n` = num of farms, `m` = num of FJ's friends
2. Read in second line: string of farm types where `G` = Guernsey, `H` = Holstein and string is 1-indexed.
3. For the next `n-1` lines read in the edges of the graph and create an adjacency list of the farms (1-indexed).
4. Process the tree & detect the different components
	1. Create an array of size `n + 1` to store the component of each farm. Initialize all values to `-1` or `0` (if 1-indexed) to indicate that they haven't been visited yet.
	2. For each farm, if it hasn't been visited yet, BFS to find all the farms in the same subtree.
		1. Create a queue to store the farms to visit.
		2. Add the current farm to the queue.
		3. While the queue isn't empty, pop the front farm and mark it as visited.
		4. Visit a neighbor if it's new & is of the same type.
		5. Repeat steps 3.2.3 - 3.2.4 until the queue is empty.
	3. Repeat steps 3.2 - 3.3 until all farms and their components have been visited.
5. For the next `m` lines read & check if friend's path satisfies them
	1. Read in the start farm, end farm, and preference of the friend.
	2. Check if the start and end farms are in the same component and if the start farm's type is the same as the friend's preference.
	3. If the friend is satisfied, add a `1` to the answer string, otherwise add a `0`.
6. Write satisfaction of each friend in sting form to output file
### Time & Space complexity:
Time: `O(n + m)` | `O(V + E)`  
Space: `O(n + m)` | `O(V + E)`  

Where `n` is number of farms, `m` is number farmer John's friends, `V` is number of vertices, and `E` is number of edges.

### Python Code
```python
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
import java.io.*;
import java.util.*;

public class MilkVisits {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("milkvisits.in"));
		// Read in First line: n = num of farms, m = num of FJ's friends
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());

		// Second line: string of farm types
		String milkTypes = " " + in.readLine();

		// For the next n-1 lines read in the edges of the graph
		ArrayList<Integer>[] farms = new ArrayList[n + 1];
		for (int idx = 0; idx < n + 1; ++idx)
			farms[idx] = new ArrayList<>();
		for (int ln = 0; ln < n - 1; ++ln) {
			st = new StringTokenizer(in.readLine());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());

			farms[x].add(y);
			farms[y].add(x);
		}

		// Process the tree & detect the different components
		int[] components = new int[n + 1];
		for (int farm = 1; farm <= n; ++farm) {
			// Don't process a farm if it's been visited already
			if (components[farm] != 0)
				continue;

			// BFS to find all the farms in the same subtree
			char type = milkTypes.charAt(farm);
			Queue<Integer> q = new LinkedList<>();
			q.add(farm);
			while (!q.isEmpty()) {
				int qdFarm = q.poll();
				
				// Mark the queue'd farm as same path as current component (farm)
				components[qdFarm] = farm;

				// Visit a neighbor if it's new & is of the same type
				for (int neighbor : farms[qdFarm])
					if (milkTypes.charAt(neighbor) == type && components[neighbor] == 0)
						q.add(neighbor);
			}
		}

		// For the next m lines read & check if friend's path satisfies them
		StringBuilder ans = new StringBuilder();
		for (int ln = 0; ln < m; ++ln) {
			st = new StringTokenizer(in.readLine());
			int start = Integer.parseInt(st.nextToken());
			int end = Integer.parseInt(st.nextToken());
			String preference = st.nextToken();

			boolean singleType = components[start] == components[end];
			boolean samePreference = milkTypes.charAt(start) == preference.charAt(0);
			ans.append(singleType && !samePreference ? 0 : 1);
		}
		in.close();

		// Write satisfaction of each friend in sting form to output file
		PrintWriter out = new PrintWriter("milkvisits.out");
		out.println(ans);
		out.close();
	}
}
```