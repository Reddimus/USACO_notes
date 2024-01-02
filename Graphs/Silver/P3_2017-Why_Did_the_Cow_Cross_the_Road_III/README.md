# [USACO 2017 February Contest, Silver](http://www.usaco.org/index.php?page=feb17results)
## [Problem 3. Why Did the Cow Cross the Road III](http://www.usaco.org/index.php?page=viewproblem2&cpid=716)

Why did the cow cross the road? Well, one reason is that Farmer John's farm simply has a lot of roads, making it impossible for his cows to travel around without crossing many of them.

FJ's farm is arranged as an `N×N` square grid of fields `(2≤N≤100)`, Certain pairs of adjacent fields (e.g., north-south or east-west) are separated by roads, and a tall fence runs around the external perimeter of the entire grid, preventing cows from leaving the farm. Cows can move freely from any field to any other adjacent field (north, east, south, or west), although they prefer not to cross roads unless absolutely necessary.

There are `K` cows `(1≤K≤100,K≤N2)` on FJ's farm, each located in a different field. A pair of cows is said to be "distant" if, in order for one cow to visit the other, it is necessary to cross at least one road. Please help FJ count the number of distant pairs of cows.

### INPUT FORMAT (file countcross.in):

The first line of input contains `N`, `K`, and `R`. The next `R` lines describe `R` roads that exist between pairs of adjacent fields. Each line is of the form `r c r′ c′` (integers in the range `1…N`), indicating a road between the field in (row `r`, column `c`) and the adjacent field in (row `r′`, column `c′`). The final `K` lines indicate the locations of the `K` cows, each specified in terms of a row and column.

### OUTPUT FORMAT (file countcross.out):

Print the number of pairs of cows that are distant.

### SAMPLE INPUT:

```
3 3 3
2 2 2 3
3 3 3 2
3 3 2 3
3 3
2 2
2 3
```

### SAMPLE OUTPUT:

```
2
```

### Hints:
- Depth First Search or Breadth First Search number of cows that can be reached without crossing a road
- For each cow component, add the product of their non-overlapping sizes to the number of distant pairs.

# [Solutions](https://github.com/Reddimus/USACO_notes/tree/main/Graphs/Silver/P3_2017-Why_Did_the_Cow_Cross_the_Road_III)

## Graphs - Depth First Search (DFS) | Flood Fill

### Steps
1. Read in input file.
	- Read in first line: `n` = grid side length, `k` = # of cows, `r` = # of roads
	- For the next `r` lines, read in start `(r, c)` and end `(r', c')` positions of two-way roads
	- For the next `k` lines, read in `(r, c)` positions of cows
2. Group size of cow components to calculate distant pairs
	- For each cow, perform a depth first search (DFS) to find the number of cows that can be reached without crossing a road
	- Add the number of cows in each component to a list
3. Sum product of pairs from distinct cow groups for distant pairs
	- For each pair of cow components, add the product of their sizes to the number of distant pairs
4. Write number of distant pairs to output file

### Time & Space complexity:
Time: `O(N^2)`  
Space: `O(N^2)`  

Where `N` is the side length of the grid, `K` is the number of cows, and `R` is the number of roads.

### Python Code
```python
with open("countcross.in", "r") as f:
	# Read in first line: n = grid side length, k = # of cows, r = # of roads
	n, k, r = map(int, f.readline().split())
	# Read in start (r, c) and end (r', c') positions of two-way roads
	roads = set()
	for ln in range(r):
		sr, sc, er, ec = map(int, f.readline().split())
		roads.add((sr, sc, er, ec))
		roads.add((er, ec, sr, sc))
	# Read in (r, c) positions of cows
	cows = set(tuple(map(int, f.readline().split())) for ln in range(k))

visited = set()

# Depth first search number of cows that can be reached without crossing a road
def dfs(r: int, c: int, prev_r: int, prev_c: int) -> int:
	if (r < 1 or n < r
	or c < 1 or n < c
	or (r, c) in visited
	or (r, c, prev_r, prev_c) in roads):
		return 0
	
	visited.add((r, c))
	cow_count = 1 if (r, c) in cows else 0

	return (cow_count +
	dfs(r + 1, c, r, c) +
	dfs(r - 1, c, r, c) +
	dfs(r, c + 1, r, c) +
	dfs(r, c - 1, r, c))

# Group size of cow components to calculate distant pairs
cow_components = [dfs(r, c, r, c) for r, c in cows]

# Sum product of pairs from distinct cow groups for distant pairs
distant_pairs = 0
for i in range(len(cow_components)):
	for j in range(i + 1, len(cow_components)):
		distant_pairs += cow_components[i] * cow_components[j]

# Write number of distant pairs to output file
print(distant_pairs, file=open("countcross.out", "w"))
```

### C++ Code:
```cpp
#include <bits/stdc++.h>

using namespace std;

struct Road { int sr, sc, er, ec; };
// Implement comparator to use Road struct in set
inline bool operator<(const Road &a, const Road &b) {
	return tie(a.sr, a.sc, a.er, a.ec) < tie(b.sr, b.sc, b.er, b.ec);
}

int main() {
	freopen("countcross.in", "r", stdin);
	// Read in first line: n = grid side length, k = # of cows, r = # of roads
	int n, k, r;
	cin >> n >> k >> r;
	// Read in start (r, c) and end (r', c') positions of two-way roads
	set<Road> roads;
	for (int ln = 0; ln < r; ++ln) {
		int sr, sc, er, ec;
		cin >> sr >> sc >> er >> ec;
		roads.insert({--sr, --sc, --er, --ec});
		roads.insert({er, ec, sr, sc});
	}
	// Read in start (r, c) positions of cows
	vector<vector<bool>> cows(n, vector<bool>(n, false));
	for (int ln = 0; ln < k; ++ln) {
		int r, c;
		cin >> r >> c;
		cows[--r][--c] = true;
	}

	vector<vector<bool>> visited(n, vector<bool>(n, false));

	// Depth first search number of cows that can be reached without crossing a road
	function<int(int, int, int, int)> dfs = [&](int r, int c, int pr, int pc) -> int {
		if (r < 0 || n <= r ||
		c < 0 || n <= c ||
		visited[r][c] ||
		roads.count(Road{r, c, pr, pc}))
			return 0;

		visited[r][c] = true;
		
		return (cows[r][c] +
		dfs(r + 1, c, r, c) +
		dfs(r - 1, c, r, c) +
		dfs(r, c + 1, r, c) +
		dfs(r, c - 1, r, c));
	};

	// Group size of cow components to calculate distant pairs
	vector<int> cowComponents;
	for (int r = 0; r < n; ++r)
		for (int c = 0; c < n; ++c)
			if (!visited[r][c] && cows[r][c])
				cowComponents.push_back(dfs(r, c, r, c));

	// Sum product of pairs from distinct cow groups for distant pairs
	int distantPairs = 0;
	for (int i = 0; i < cowComponents.size(); ++i)
		for (int j = i + 1; j < cowComponents.size(); ++j)
			distantPairs += cowComponents[i] * cowComponents[j];

	// Write number of distant pairs to output file
	freopen("countcross.out", "w", stdout);
	cout << distantPairs << endl;
	return 0;
}
```

### Java Code:
```java
import java.io.*;
import java.util.*;

public class CowCrossIII {
	private static class Road {
		int sr, sc, er, ec;
		Road(int sr, int sc, int er, int ec) {
			this.sr = sr;
			this.sc = sc;
			this.er = er;
			this.ec = ec;
		}

		@Override
		public int hashCode() {
			return Objects.hash(sr, sc, er, ec);
		}

		@Override
		public boolean equals(Object o) {
			if (!(o instanceof Road)) { return false; }
			Road r = (Road)o;
			return sr == r.sr && sc == r.sc && er == r.er && ec == r.ec;
		}
	}

	private static int n, k, r;
	private static Set<Road> roads = new HashSet<>();
	private static boolean[][] cows, visited;

	// Depth first search number of cows that can be reached without crossing a road
	private static int dfs(int r, int c, int prevR, int prevC) {
		if (r < 0 || n <= r ||
		c < 0 || n <= c ||
		visited[r][c] ||
		roads.contains(new Road(r, c, prevR, prevC)))
			return 0;

		visited[r][c] = true;
		int cowCount = cows[r][c] ? 1 : 0;

		return (cowCount +
		dfs(r + 1, c, r, c) +
		dfs(r - 1, c, r, c) +
		dfs(r, c + 1, r, c) +
		dfs(r, c - 1, r, c));
	}

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("countcross.in"));
		// Read in first line: n = grid side length, k = # of cows, r = # of roads
		StringTokenizer st = new StringTokenizer(in.readLine());
		n = Integer.parseInt(st.nextToken());
		k = Integer.parseInt(st.nextToken());
		r = Integer.parseInt(st.nextToken());
		// Read in start (r, c) and end (r', c') positions of two-way roads
		for (int ln = 0; ln < r; ++ln) {
			st = new StringTokenizer(in.readLine());
			int sr = Integer.parseInt(st.nextToken()) - 1;
			int sc = Integer.parseInt(st.nextToken()) - 1;
			int er = Integer.parseInt(st.nextToken()) - 1;
			int ec = Integer.parseInt(st.nextToken()) - 1;
			roads.add(new Road(sr, sc, er, ec));
			roads.add(new Road(er, ec, sr, sc));
		}
		// Read in start (r, c) positions of cows
		cows = new boolean[n][n];
		for (int ln = 0; ln < k; ++ln) {
			st = new StringTokenizer(in.readLine());
			int cr = Integer.parseInt(st.nextToken()) - 1;
			int cc = Integer.parseInt(st.nextToken()) - 1;
			cows[cr][cc] = true;
		}

		visited = new boolean[n][n];

		// Group size of cow components to calculate distant pairs
		List<Integer> cowComponents = new ArrayList<>();
		for (int r = 0; r < n; ++r) {
			for (int c = 0; c < n; ++c) {
				int cowCount = dfs(r, c, r, c);
				if (cowCount > 0)
					cowComponents.add(cowCount);
			}
		}

		// Sum product of pairs from distinct cow groups for distant pairs
		int distantPairs = 0;
		for (int i = 0; i < cowComponents.size(); ++i)
			for (int j = i + 1; j < cowComponents.size(); ++j)
				distantPairs += cowComponents.get(i) * cowComponents.get(j);

		// Write number of distant pairs to output file
		PrintWriter out = new PrintWriter("countcross.out");
		out.println(distantPairs);
		out.close();
	}
}
```