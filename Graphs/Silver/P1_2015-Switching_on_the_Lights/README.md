# [USACO 2015 December Contest, Silver](http://www.usaco.org/index.php?page=dec15results)
## [Problem 1. Switching on the Lights](http://www.usaco.org/index.php?page=viewproblem2&cpid=570)

Farmer John has recently built an enormous barn consisting of an `N×N` grid of rooms `(2≤N≤100)`, numbered from `(1,1)` up to `(N,N)`. Being somewhat afraid of the dark, Bessie the cow wants to turn on the lights in as many rooms as possible.

Bessie starts in room `(1,1)`, the only room that is initially lit. In some rooms, she will find light switches that she can use to toggle the lights in other rooms; for example there might be a switch in room `(1,1)` that toggles the lights in room `(1,2)`. Bessie can only travel through lit rooms, and she can only move from a room (x,y) to its four adjacent neighbors (x−1,y), (x+1,y), (x,y−1) and (x,y+1) (or possibly fewer neighbors if this room is on the boundary of the grid).

Please determine the maximum number of rooms Bessie can illuminate.

### INPUT FORMAT (file lightson.in):

The first line of input contains integers `N` and `M` `(1≤M≤20,000)`.The next `M` lines each describe a single light switch with four integers `x`, `y`, `a`, `b`, that a switch in room `(x,y)` can be used to toggle the lights in room `(a,b)`. Multiple switches may exist in any room, and multiple switches may toggle the lights of any room.

### OUTPUT FORMAT (file lightson.out):

A single line giving the maximum number of rooms Bessie can illuminate.

### SAMPLE INPUT:

```
3 6
1 1 1 2
2 1 2 2
1 1 1 3
2 3 3 1
1 3 1 2
1 3 2 1
```

### SAMPLE OUTPUT:

```
5
```

Here, Bessie can use the switch in `(1,1)` to turn on lights in `(1,2)` and `(1,3)`. She can then walk to `(1,3)` and turn on the lights in `(2,1)`, from which she can turn on the lights in `(2,2)`. The switch in `(2,3)` is inaccessible to her, being in an unlit room. She can therefore illuminate at most 5 rooms.

### Hints:
- Some paths are not available to Bessie until after she has turned on some lights.
	- We need to keep track of the rooms that are newly lit and not yet visited to revisit them later.
- Some rooms light up the same room.
	- When we count lit rooms we do not want to count the same room twice.

## Graphs - Breadth First Search (BFS) | Flood Fill approach

### Steps
1. Read the input file.
	- First line: `n = switches graph side length`, `m = number of switches`
	- For the next `m` lines map `x, y` room to room `a, b` that can be lit.
2. Initialize data structures.
	- `lit` to keep track of lit rooms. Starts with room `(1, 1)` lit.
	- `seen` to keep track of visited rooms.
	- `directions` to check adjacent rooms.
	- `q` to keep track of the queued rooms to visit. The `q` starts with the room `(1, 1)`.
3. Breadth First Search (BFS) lit rooms while keeping track of number of lit rooms.
	- While the `q` is not empty:
		- Pop the first room in the `q`.
		- If the room has been visited, skip it.
		- Mark the room as visited.
		- Turn on new lights of current room.
			- If the current room has switches, turn on the lights of the rooms that can be lit.
			- Check if the newly lit room can be connected and hasn't been visited.
				- If so, add it to the queue.
		- Explore valid adjacent rooms.
			- Check if the adjacent room is lit and hasn't been visited.
				- If so, add it to the queue.
4. Write number of lit rooms accessible from `(1, 1)` room to output file.

### Time & Space complexity:
Time: `O(N^2 + M)`  
Space: `O(N^2 + M)`  

Where `N` is the number of rows and columns in the switches graph and `M` is the number of switches.

### Python Code
```python
from collections import deque

with open("lightson.in", "r") as fin:
	# First line: n = graph side length, m = # of switches
	n, m = map(int, fin.readline().split())
	# For the next m lines map x, y room to room a, b that can be lit
	graph = {}	# 1-indexed
	for ln in range(m):
		x, y, a, b = map(int, fin.readline().split())
		graph[(x, y)] = graph.get((x, y), []) + [(a, b)]

lit = {(1, 1)}
seen = set()
directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
q = deque([(1, 1)])

# Breadth First Search (BFS) lit rooms
while q:
	r, c = q.popleft()
	if (r, c) in seen:
		continue
	seen.add((r, c))

	# Turn on new lights of current room
	if (r, c) in graph:
		for sr, sc in graph[(r, c)]:
			if (sr, sc) in lit:
				continue
			lit.add((sr, sc))
			# Check if the newly lit room can be connected and hasn't been visited
			q += [(sr, sc) for dr, dc in directions if (sr + dr, sc + dc) in seen and (sr, sc) not in seen]

	# Explore valid adjacent rooms
	q += [(r + dr, c + dc) for dr, dc in directions if (r + dr, c + dc) in lit and (r + dr, c + dc) not in seen]

# Write number of lit rooms accessible from (1, 1) to output file
print(len(lit), file=open("lightson.out", "w"))
```

### C++ Code
```cpp
#include <bits/stdc++.h>

using namespace std;

struct indices {const int row, col;};

int main() {
	freopen("lightson.in", "r", stdin);
	// First line: n = graph side length, m = # of switches
	int n, m;
	cin >> n >> m;
	// For the next m lines map x, y room to room a, b that can be lit
	vector<vector<vector<indices>>> switches(n, vector<vector<indices>>(n));
	for (int ln = 0; ln < m; ++ln) {
		int x, y, a, b;
		cin >> x >> y >> a >> b;
		switches[x - 1][y - 1].push_back({a - 1, b - 1});
	}

	vector<indices> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	vector<vector<bool>> seen(n, vector<bool>(n)), lit(n, vector<bool>(n));
	queue<indices> q;

	int litCount = 1;
	lit[0][0] = true;
	q.push({0, 0});
	while (!q.empty()) {
		indices qd = q.front();
		q.pop();
		if (seen[qd.row][qd.col]) 
			continue;
		seen[qd.row][qd.col] = true;

		// Turn on new lights of current room
		for (indices& sw : switches[qd.row][qd.col]) {
			if (lit[sw.row][sw.col])
				continue;
			lit[sw.row][sw.col] = true;
			++litCount;
			// Check if the newly lit room can be connected and hasn't been visited
			for (indices& d : directions) {
				const int aswr = sw.row + d.row, aswc = sw.col + d.col;
				if ((-1 < aswr && aswr < n) && 
				(-1 < aswc && aswc < n) && 
				seen[aswr][aswc] &&
				!seen[sw.row][sw.col])
					q.push(sw);
			}
		}

		// Explore valid adjacent rooms
		for (indices& d : directions) {
			const int ar = qd.row + d.row, ac = qd.col + d.col;
			if ((-1 < ar && ar < n) && 
			(-1 < ac && ac < n) &&
			lit[ar][ac] &&
			!seen[ar][ac])
				q.push({ar, ac});
		}
	}

	// Write number of lit rooms accessible from (1, 1) to output file
	freopen("lightson.out", "w", stdout);
	cout << litCount << endl;
	return 0;
}
```

### Java Code
```java
import java.io.*;
import java.util.*;

public class SwitchingLights {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("lightson.in"));
		// First line: n = graph side length, m = # of switches
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		// For the next m lines map x, y room to room a, b that can be lit
		ArrayList<int[]>[][] switches = (ArrayList<int[]>[][]) new ArrayList[n][n];
		for (int r = 0; r < n; ++r)
			for (int c = 0; c < n; ++c) 
				switches[r][c] = new ArrayList<int[]>();
		for (int ln = 0; ln < m; ++ln) {
			st = new StringTokenizer(in.readLine());
			int x = Integer.parseInt(st.nextToken()) - 1;
			int y = Integer.parseInt(st.nextToken()) - 1;
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			switches[x][y].add(new int[] {a, b});
		}
		in.close();
		
		int litCount = 1;
		int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
		boolean[][] seen = new boolean[n][n], lit = new boolean[n][n];
		lit[0][0] = true;
		Queue<int[]> q = new LinkedList<int[]>();
		q.add(new int[] {0, 0});

		// Breadth First Search (BFS) lit rooms
		while (!q.isEmpty()) {
			int[] qdIdxs = q.poll();
			final int r = qdIdxs[0], c = qdIdxs[1];
			if (seen[r][c])
				continue;
			seen[r][c] = true;

			// Turn on new lights of current room
			for (int[] swIdxs : switches[r][c]) {
				final int sr = swIdxs[0], sc = swIdxs[1];
				if (lit[sr][sc])
					continue;
				lit[sr][sc] = true;
				++litCount;
				// Check if the newly lit room can be connected and hasn't been visited
				for (int[] d : directions) {
					final int asr = sr + d[0], asc = sc + d[1];
					if ((-1 < asr && asr < n) &&
					(-1 < asc && asc < n) &&
					seen[asr][asc] &&
					!seen[sr][sc])
						q.add(swIdxs);
				}
			}

			// Explore valid adjacent rooms
			for (int[] d : directions) {
				final int ar = r + d[0], ac = c + d[1];
				if ((-1 < ar && ar < n) &&
				(-1 < ac && ac < n) &&
				lit[ar][ac] &&
				!seen[ar][ac])
					q.add(new int[]{ar, ac});
			}
		}

		// Write number of lit rooms accessible from (1, 1) to output file
		PrintWriter out = new PrintWriter("lightson.out");
		out.println(litCount);
		out.close();
	}
}
```
