# [USACO 2020 February Contest, Gold](http://www.usaco.org/index.php?page=feb20results)
## [Problem 1. Timeline](http://www.usaco.org/index.php?page=viewproblem2&cpid=1017)

Bessie attended `N` milking sessions `(1≤N≤10^5)` over the past `M` days `(2≤M≤10^9)`. However, she is having trouble remembering when she attended each session.

For each session `i=1…N`, she knows that it occurred no earlier than day `Si (1≤Si≤M)`. Additionally, Bessie has `C` memories `(1≤C≤10^5)`, each described by a triple `(a,b,x)`, where she recalls that session `b` happened at least `x` days after `a`.

Help Bessie by computing the earliest possible date of occurrence for each milking session. It is guaranteed that Bessie did not remember incorrectly; in other words, there exists an assignment of sessions to days in the range `1…M` such that all constraints from her memories are satisfied.

### SCORING:
- Test cases 2-4 satisfy `N, C≤10^3`.
- Test cases 5-10 satisfy no additional constraints.

### INPUT FORMAT (file timeline.in):

The first line of input contains `N`, `M`, and `C`.

The next line contains `N` space-separated integers `S_1,S_2,…,S_N`. Each is in the range `1…M`.

The next `C` lines contain three integers, `a`, `b`, and `x` indicating that session `b` happened at least `x` days after `a`. For each line, `a≠b`, `a` and `b` are in the range `1…N`, and `x` is in the range `1…M`.

### OUTPUT FORMAT (file timeline.out):

Output `N` lines giving the earliest possible date of occurrence for each session.

### SAMPLE INPUT:

```
4 10 3
1 2 3 4
1 2 5
2 4 2
3 4 4
```

### SAMPLE OUTPUT:

```
1
6
3
8
```

Session two occurred at least five days after session one, so it cannot have occurred before day `1+5=6.` Session four occurred at least two days after session two, so it cannot have occurred before day `6+2=8`.

### Hint:
- We must update the earliest possible date in the session's path in chronological order.

# [Solutions](https://github.com/Reddimus/USACO_notes/tree/main/Graphs/Gold/P1_2020-Timeline)

## Adjacency List Graphs - Topological Sort approach

### Steps
1. **Read in data of the "timeline.in" input file**:
    - First line: `n` = number of milking sessions, `m` = total days, `c` = number of memories
    - Second line: Build a sessions array of size `n` that contains the minimum possible day milked for each session.
    - For the next `c` lines, build an Adjacency List graph with `n` vertices for Bessie's memories. Each memory is a directed edge from session `a` to session `b` with a weight `x` indicating that session `b` happened at least `x` days after session `a`.
2. **Build topological order of memory graph**:
    - Recursively depth-first search session path with `a` and `b` session values in the memories graph to build topological order.
3. **Update session dependencies in reverse topological order of the memory graph**:
    - Remember session `b` happened at least `x` days after session `a`. Therefore we contantly update sessions `b` with the maximum possible day it could have occurred.
4. **Write updated session answers to output file**.

### Time & Space complexity:
Time: `O(N + M)`
Space: `O(N + M)`

Where `N` is the number of milking sessions, `M` is the total number of days, `C` is the number of memories.

### C++ Code:
```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("timeline.in", "r", stdin);
	// First line: n = # of milking sessions, m = total days, c = # of memories
	int n, m, c;
	cin >> n >> m >> c;
	// Second line: 1->n indexed sessions filled with min possible day milked 
	vector<int> sessions(n+1);
	for (int idx = 1; idx <= n; ++idx) 
		cin >> sessions[idx];
	// For the next c lines build 1-indexed memory graph
	vector<vector<pair<int, int>>> memories(n+1);
	for (int ln = 0; ln < c; ++ln) {
		// Session b happened at least x days after session a
		int a, b, x;
		cin >> a >> b >> x;
		memories[a].push_back({b, x});
	}

	// Build topological order of memory graph
	vector<int> topologicalOrder;
	vector<bool> visited(n+1);
	// Recursively depth-first search session path to build topological order
	function<void(int)> build_order = [&](int session) {
		if (visited[session]) 
			return;

		visited[session] = true;

		for (pair<int, int>& mem : memories[session]) 
			if (!visited[mem.first])
				build_order(mem.first);

		topologicalOrder.push_back(session);
	};

	for (int session = 1; session <= n; ++session) 
		build_order(session);
	
	// Update session dependencies in topological order of the memory graph
	for (int idx = n - 1; idx >= 0; --idx) {
		int a = topologicalOrder[idx];
		for (pair<int, int>& mem : memories[a]) {
			int b = mem.first, x = mem.second;
			sessions[b] = max(sessions[b], sessions[a] + x);
		}
	}

	// Write 1-indexed session answers to output file
	freopen("timeline.out", "w", stdout);
	for (int idx = 1; idx <= n; ++idx) 
		cout << sessions[idx] << endl;
	return 0;
}
```

### Java Code:
```java
// Adjacency List Graphs - Topological Sort approach
// T & M: O(N + M), where N = # of sessions, M =  total days

import java.io.*;
import java.util.*;

public class Timeline {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("timeline.in"));
		// First line: n = # of milking sessions, m = total days, c = # of memories
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int c = Integer.parseInt(st.nextToken());
		// Second line: 1->n indexed sessions filled with min possible day milked 
		st = new StringTokenizer(in.readLine());
		int[] sessions = new int[n + 1];
		for (int idx = 1; idx <= n; ++idx) 
			sessions[idx] = Integer.parseInt(st.nextToken());
		// For the next c lines build 1-indexed memory graph
		ArrayList<int[]>[] memories = new ArrayList[n+1];
		for (int session = 1; session <= n; ++session)
			memories[session] = new ArrayList<>();
		for (int ln = 0; ln < c; ++ln) {
			st = new StringTokenizer(in.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			int x = Integer.parseInt(st.nextToken());
			// Session b happened at least x days after session a
			memories[a].add(new int[] {b, x});
		}
		in.close();

		// Build topological order of memory graph
		ArrayList<Integer> topologicalOrder = buildTopOrder(memories);

		// Update session dependencies in topological order of the memory graph
		for (int a : topologicalOrder) {
			for (int[] mem : memories[a]) {
				int b = mem[0], x = mem[1];
				sessions[b] = Math.max(sessions[b], sessions[a] + x);
			}
		}

		// Write 1-indexed session answers to output file
		PrintWriter out = new PrintWriter("timeline.out");
		for (int idx = 1; idx <= n; ++idx) 
			out.println(sessions[idx]);
		out.close();
	}

	// Recursively depth-first search session path to build topological order
	private static HashSet<Integer> visited = new HashSet<>();
	private static LinkedList<Integer> topOrder = new LinkedList<>();

	private static ArrayList<Integer> buildTopOrder(ArrayList<int[]>[] memories) {
		for (int session = 1; session < memories.length; ++session) 
			dfs(session, memories);
		return new ArrayList<>(topOrder);
	}

	private static void dfs(int session, ArrayList<int[]>[] memories) {
		if (visited.contains(session))
			return;

		visited.add(session);

		for (int[] mem : memories[session]) 
			dfs(mem[0], memories);

		topOrder.addFirst(session);
	}
}
```