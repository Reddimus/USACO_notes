# [USACO 2019 January Contest, Silver](http://www.usaco.org/index.php?page=jan19results)
## [Problem 2. Icy Perimeter](http://www.usaco.org/index.php?page=viewproblem2&cpid=895)

Farmer John is going into the ice cream business! He has built a machine that produces blobs of ice cream but unfortunately in somewhat irregular shapes, and he is hoping to optimize the machine to make the shapes produced as output more reasonable.

The configuration of ice cream output by the machine can be described using an `N×N` grid `(1≤N≤1000)` as follows:

```
##....
....#.
.#..#.
.#####
...###
....##
```

Each '.' character represents empty space and each '#' character represents a 1×1 square cell of ice cream.

Unfortunately, the machine isn't working very well at the moment and might produce multiple disconnected blobs of ice cream (the figure above has two). A blob of ice cream is connected if you can reach any ice cream cell from every other ice cream cell in the blob by repeatedly stepping to adjacent ice cream cells in the north, south, east, and west directions.

Farmer John would like to find the area and perimeter of the blob of ice cream having the largest area. The area of a blob is just the number of '#' characters that are part of the blob. If multiple blobs tie for the largest area, he wants to know the smallest perimeter among them. In the figure above, the smaller blob has area 2 and perimeter 6, and the larger blob has area 13 and perimeter 22.

Note that a blob could have a "hole" in the middle of it (empty space surrounded by ice cream). If so, the boundary with the hole also counts towards the perimeter of the blob. Blobs can also appear nested within other blobs, in which case they are treated as separate blobs. For example, this case has a blob of area 1 nested within a blob of area 16:

```
#####
#...#
#.#.#
#...#
#####
```

Knowing both the area and perimeter of a blob of ice cream is important, since Farmer John ultimately wants to minimize the ratio of perimeter to area, a quantity he calls the icyperimetric measure of his ice cream. When this ratio is small, the ice cream melts slower, since it has less surface area relative to its mass.

### INPUT FORMAT (file perimeter.in):

The first line of input contains `N`, and the next `N` lines describe the output of the machine. At least one '#' character will be present.

### OUTPUT FORMAT (file perimeter.out):

Please output one line containing two space-separated integers, the first being the area of the largest blob, and the second being its perimeter. If multiple blobs are tied for largest area, print the information for whichever of these has the smallest perimeter.

### SAMPLE INPUT:

```
6
##....
....#.
.#..#.
.#####
...###
....##
```

### SAMPLE OUTPUT:

```
13 22
```

### Hints:
- We can calculate the area and perimeter of a blob by performing a Breadth First Search (BFS) simulating a flood fill.
- Perimeter is counted once for each edge of the blob, this can be interpreted the number of times the current `#` cell is adjacent to a `.` cell.

## Graphs - Breadth First Search (BFS) | Flood Fill approach

### Steps
1. Read in input file.
	- First line: `n = sides of graph`
	- For the next `n` lines read `n` sized strings representing ice cream blob graph.
2. Create Breadth First Search (BFS) function to find the area and perimeter of a blob.
	- Mark the current cell as visited.
	- Add the current cell to the queue.
	- While the queue is not empty:
		- Pop the front of the queue.
		- For each adjacent cell:
			- If adjacent cell is outside of the blob, increment the perimeter.
			- Else if adjacent cell is part of the same blob, increment the area and add the adjacent cell to the queue.
3. Iterate through each cell in the graph.
	- If cell is part of a blob, perform a Breadth First Search (BFS) to find the area and perimeter of the blob.
	- Update the largest blob to the blob with the largest area and smallest perimeter.
4. Write the largest blob with smallest perimeter to output file.

### Time & Space complexity:
Time: `O(N^2)`  
Space: `O(N^2)`  

Where `N` is the side length of the grid.

### Python Code
```python
from collections import deque

with open("perimeter.in", "r") as fin:
	# First line: n = sides of graph
	n = int(fin.readline())
	# For the next n lines read n sized strings representing ice cream blob graph
	graph = [list(fin.readline().strip()) for ln in range(n)]

directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

# Breadth First Search (BFS) perimeter and area of blob
def bfs(r: int, c: int) -> tuple:
	area, perimeter = 1, 0
	graph[r][c] = ' '	# mark as visited
	q = deque([(r, c)])
	while q:
		qr, qc = q.popleft()

		for dr, dc in directions:
			ar, ac = qr + dr, qc + dc
			# If adjacent row/col outside of blob
			if (ar < 0 or n <= ar or
			ac < 0 or n <= ac or
			graph[ar][ac] == '.'):
				perimeter += 1
			# Else if adjacent row/col is part of the same blob component
			elif (graph[ar][ac] == '#'):
				area += 1
				graph[ar][ac] = ' '
				q.append((ar, ac))
	return (area, perimeter)
	
largest_blob = (0, n + 1)	# largest_blob = area, perimeter
for r in range(n):
	for c in range(n):
		# Group blobs into their own components and update largest blob
		if graph[r][c] == '#':
			blob = bfs(r, c)
			# Update blob to largest area then smallest perimeter
			if (largest_blob[0] < blob[0] or
			(largest_blob[0] == blob[0] and largest_blob[1] > blob[1])):
				largest_blob = blob

# Write largest blob with smallest perimeter to output file
print(f"{largest_blob[0]} {largest_blob[1]}", file=open("perimeter.out", "w"))
```

### C++ Code
```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("perimeter.in", "r", stdin);
	// First line: n = sides of graph
	int n;
	cin >> n;
	// For the next n lines read n sized strings representing ice cream blob graph
	vector<vector<char>> graph(n, vector<char>(n));
	for (int r = 0; r < n; ++r)
		for (int c = 0; c < n; ++c)
			cin >> graph[r][c];

	struct indices { const int row, col; };
	struct blob { int area, perimeter; };
	indices directions[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	// Breadth First Search (BFS) perimeter and area of blob
	function<blob(int, int)> bfs = [&](int r, int c) -> blob {
		int area = 1, perimeter = 0;
		graph[r][c] = ' ';	// Mark as visited
		queue<indices> q;
		q.push({r, c});
		while (!q.empty()) {
			indices qd = q.front();
			q.pop();

			for (const indices& d : directions) {
				int ar = qd.row + d.row, ac = qd.col + d.col;
				// If adjacent row/col outside of blob
				if (ar < 0 || ar >= n || 
				ac < 0 || ac >= n || 
				graph[ar][ac] == '.') {
					++perimeter;
				} 
				// Else if adjacent row/col is part of the same blob component
				else if (graph[ar][ac] == '#') {
					++area;
					graph[ar][ac] = ' ';
					q.push({ar, ac});
				}
			}
		}
		return {area, perimeter};
	};

	blob maxBlob = {0, n + 1};
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			// Group blobs into their own components and update largest blob
			if (graph[r][c] == '#') {
				blob currBlob = bfs(r, c);
				// Update blob to largest area then smallest perimeter
				if (maxBlob.area < currBlob.area ||
				(maxBlob.area == currBlob.area && maxBlob.perimeter > currBlob.perimeter))
					maxBlob = currBlob;
			}
		}
	}

	// Write largest blob with smallest perimeter to output file
	freopen("perimeter.out", "w", stdout);
	cout << maxBlob.area << " " << maxBlob.perimeter << endl;
	return 0;
}
```

### Java Code
```java
import java.io.*;
import java.util.*;

public class IcyPerimeter {
	static int n;
	static char[][] graph;
	static int[][] directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("perimeter.in"));
		// First line: n = sides of graph
		n = Integer.parseInt(in.readLine());
		// For the next n lines read n sized strings representing ice cream blob graph
		graph = new char[n][n];
		for (int r = 0; r < n; ++r)
			graph[r] = in.readLine().toCharArray();
		in.close();

		int[] maxBlob = new int[]{0, n + 1};	// {area, perimeter}
		for (int r = 0; r < n; ++r) {
			for (int c = 0; c < n; ++c) {
				// Group blobs into their own components and update largest blob
				if (graph[r][c] == '#') {
					int[] blob = bfs(r, c);
					// Update blob to largest area then smallest perimeter
					if (maxBlob[0] < blob[0] ||
					(maxBlob[0] == blob[0] && maxBlob[1] > blob[1]))
						maxBlob = blob;
				}
			}
		}

		// Write largest blob with smallest perimeter to output file
		PrintWriter out = new PrintWriter("perimeter.out");
		out.println(maxBlob[0] + " " + maxBlob[1]);
		out.close();
	}

	// Breadth First Search (BFS) perimeter and area of blob
	private static int[] bfs(int r, int c) {
		int area = 1, perimeter = 0;
		graph[r][c] = ' ';	// mark as visited
		Queue<int[]> q = new LinkedList<int[]>();
		q.add(new int[]{r, c});
		while (!q.isEmpty()) {
			int[] qd = q.poll();

			for (int[] d : directions) {
				int ar = qd[0] + d[0], ac = qd[1] + d[1];
				// If adjacent row/col outside of blob
				if (ar < 0 || ar >= n || 
				ac < 0 || ac >= n || 
				graph[ar][ac] == '.') {
					++perimeter;
				}
				// Else if adjacent row/col is part of the same blob component
				else if (graph[ar][ac] == '#') {
					++area;
					graph[ar][ac] = ' ';
					q.add(new int[]{ar, ac});
				}
			}
		}

		return new int[]{area, perimeter};
	}
}
```
