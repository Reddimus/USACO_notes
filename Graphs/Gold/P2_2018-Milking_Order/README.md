# [USACO 2018 US Open Contest, Gold](http://www.usaco.org/index.php?page=open18results)
## [Problem 2. Milking Order](http://www.usaco.org/index.php?page=viewproblem2&cpid=838)

Farmer John's `N` cows `(1≤N≤105)`, numbered `1…N` as always, happen to have too much time on their hooves. As a result, they have worked out a complex social hierarchy related to the order in which Farmer John milks them every morning.

After weeks of study, Farmer John has made `M` observations about his cows' social structure `(1≤M≤50,000)`. Each observation is an ordered list of some of his cows, indicating that these cows should be milked in the same order in which they appear in this list. For example, if one of Farmer John's observations is the list 2, 5, 1, Farmer John should milk cow 2 sometime before he milks cow 5, who should be milked sometime before he milks cow 1.

Farmer John's observations are prioritized, so his goal is to maximize the value of `X` for which his milking order meets the conditions outlined in the first `X` observations. If multiple milking orders satisfy these first `X` conditions, Farmer John believes that it is a longstanding tradition that cows with lower numbers outrank those with higher numbers, so he would like to milk the lowest-numbered cows first. More formally, if multiple milking orders satisfy these conditions, Farmer John would like to use the lexicographically smallest one. An ordering `x` is lexicographically smaller than an ordering `y` if for some `j`, `xi=yi` for all `i<j` and `xj<yj` (in other words, the two orderings are identical up to a certain point, at which `x` is smaller than `y`).

Please help Farmer John determine the best order in which to milk his cows.

### INPUT FORMAT (file milkorder.in):
The first line contains `N` and `M`. The next `M` lines each describe an observation. Line `i+1` describes observation `i`, and starts with the number of cows `m_i` listed in the observation followed by the list of `m_i` integers giving the ordering of cows in the observation. The sum of the `m_i's` is at most `200,000`.

### OUTPUT FORMAT (file milkorder.out):
Output `N` space-separated integers, giving a permutation of `1…N` containing the order in which Farmer John should milk his cows.

### SAMPLE INPUT:
```
4 3
3 1 2 3
2 4 2
3 3 4 1
```

### SAMPLE OUTPUT:
```
1 4 2 3
```

Here, Farmer John has four cows and should milk cow 1 before cow 2 and cow 2 before cow 3 (the first observation), cow 4 before cow 2 (the second observation), and cow 3 before cow 4 and cow 4 before cow 1 (the third observation). The first two observations can be satisfied simultaneously, but Farmer John cannot meet all of these criteria at once, as to do so would require that cow 1 come before cow 3 and cow 3 before cow 1.

This means there are two possible orderings: 1 4 2 3 and 4 1 2 3, the first being lexicographically smaller.

### Hints:
- The problem asks to find maximum `X` ordered conditions that can be met for the milking order. In other words `0 -> M` observation(s) should be satisfied for the milking order answer.
- If all cows/nodes are dependent on each other, then the milking order is not possible as there is a cycle in the graph.
- A priority queue can be used to find the lexicographically smallest ordering.

# [Solutions](https://github.com/Reddimus/USACO_notes/tree/main/Graphs/Gold/P2_2018-Milking_Order)

## Adjacency List Graphs - Topological Sort approach

### Steps
1. **Read in the input file:**
    - First line: `N = number of cows` and `M = number of observations`
    - For the next `M` lines, read in the observation paths.
        - Create a 2-D array consisting of all the observations mapped the same way as the input file.
2. **Binary search for maximum number of observations that can be satisfied**
    - The answer consists of `0 -> M` observations that can be satisfied for the milking order. Therefore our lower bound is `0` and upper bound is `M`.
    3. **Within our midpoint of our lower and upper bounds, check if the number of `X` observations can be satisfied**
        - Build the adjacency list graph for `X` observations.
        - Build the amount of edges that are coming into each node.
        - Use a priority queue to find the lexicographically smallest cow to milk.
        - Traverse non-dependent cows in lexicographical order from graph using a topological sort approach. As we traverse, we remove the edges from the graph and update the amount of edges that are coming into each node, which will allow us to queue the next cow to milk.
        - Return if we were able to visit all the cows.
    - If we were able to satisfy the `X` observations, then we can increase our lower bound to `X + 1` `(midpoint + 1)` to find the maximum number of observations that can be satisfied and update our answer.
    - Else, we decrease our upper bound to `X` `(midpoint)`.
4. **Write the maximum number of x-ordered observations to the output file**

### Time & Space complexity:
Time: `O(log M * (E * N log N))`  
Space: `O(N + E)`  

Where `N` is the number of cows, `M` is the number of observations, and `E` is the number of edges in the graph.

### C++ Code:
```cpp
#include <bits/stdc++.h>

using namespace std;

class MilkingOrder {
public:
	MilkingOrder(vector<vector<int>>& observations, int& n, int& m) : 
	observations(observations), n(n), m(m) {}

	// Binary search for maximum number of observations that can be satisfied
	vector<int> search_max_conditions(void) {
		int lo = 0, hi = m;
		while (lo < hi) {
			int mid = lo + (hi - lo) / 2;
			check_x_conditions(mid) ? lo = mid + 1 : hi = mid;
		}
		return answer;
	}
private:
	vector<vector<int>> observations;
	vector<int> answer;
	int n, m;

	// Topological sort the x-observations graph to check if all cows can be visited
	bool check_x_conditions(int& x) {
		// Using up to x observations build adjacency list & count edges per node
		vector<vector<int>> graph(n + 1);
		vector<int> inDegree(n + 1, 0);
		for (int i = 0; i < x; ++i) {
			// Map observation path by pairs
			for (int j = 0; j < observations[i].size() - 1; ++j) {
				graph[observations[i][j]].push_back(observations[i][j + 1]);
				++inDegree[observations[i][j + 1]];
			}
		}

		// Queue non-dependent cows in lexicographical order
		priority_queue<int, vector<int>, greater<int>> pq;
		for (int cow = 1; cow <= n; ++cow)
			if (inDegree[cow] == 0) 
				pq.push(cow);

		// Traverse non-dependent cows in lexicographical order from graph
		vector<int> tempAnswer(n);
		int visits = 0;
		for (visits = 0; !pq.empty(); ++visits) {
			int cow = pq.top(); pq.pop();
			tempAnswer[visits] = cow;

			for (int& adj : graph[cow]) {
				--inDegree[adj];	// Remove the edge from the adjacent cow/node
				if (inDegree[adj] == 0) 
					pq.push(adj);
			}
		}

		// Check if all cows/nodes were visited
		if (visits < n) 
			return false;
		answer = tempAnswer;
		return true;
	}
};

int main(void) {
	freopen("milkorder.in", "r", stdin);
	// First line: n = # of cows, m = # of observations
	int n, m;
	cin >> n >> m;
	// For the next m lines, read in the observation paths
	vector<vector<int>> observations(m);
	for (int i = 0; i < m; ++i) {
		int mi;
		cin >> mi;
		vector<int> observation(mi);
		for (int j = 0; j < mi; ++j) 
			cin >> observation[j];
		observations[i] = observation;
	}

	// Binary search & topological sort to find the maximum number of observations
	MilkingOrder mo(observations, n, m);
	const vector<int>& answer = mo.search_max_conditions();

	// Write the maximum number of x-ordered observations to the output file
	freopen("milkorder.out", "w", stdout);
	for (int idx = 0; idx < n - 1; ++idx) 
		cout << answer[idx] << " ";
	cout << answer[n - 1] << endl;
	return 0;
}
```

### Java Code:
```java
import java.io.*;
import java.util.*;

public class MilkingOrder {
	private static int n, m;
	private static int[][] observations;
	private static int[] answer;
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("milkorder.in"));
		// First line: n = # of cows, m = # of observations
		StringTokenizer st = new StringTokenizer(in.readLine());
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		// For the next m lines, read in the observation paths
		observations = new int[m][];
		for (int i = 0; i < m; ++i) {
			st = new StringTokenizer(in.readLine());
			int mi = Integer.parseInt(st.nextToken());
			int[] observation = new int[mi];
			for (int j = 0; j < mi; ++j) 
				observation[j] = Integer.parseInt(st.nextToken());
			observations[i] = observation;
		}
		in.close();

		// Binary search for maximum number of observations that can be satisfied
		int lo = 0, hi = m;
		while (lo < hi) {
			int mid = lo + (hi - lo) / 2;
			// Topological sort to find if graph is valid & build answer
			if (check_x_conditions(mid)) 
				lo = mid + 1;
			else 
				hi = mid;
		}

		// Write the maximum number of x-ordered observations to the output file
		PrintWriter out = new PrintWriter("milkorder.out");
		for (int idx = 0; idx < n - 1; ++idx)
			out.print(answer[idx] + " ");
		out.println(answer[n - 1]);
		out.close();
	}

	// Topological sort the x-observations graph to check if all cows can be visited
	private static boolean check_x_conditions(int x) {
		int[] indegree = new int[n + 1];
		ArrayList<Integer>[] graph = new ArrayList[n + 1];
		for (int cow = 1; cow <= n; ++cow) 
			graph[cow] = new ArrayList<>();
		// Using up to x observations build adjacency list & count edges per node
		for (int i = 0; i < x; ++i) {
			// Map observation path by pairs
			for (int j = 0; j < observations[i].length - 1; ++j) {
				graph[observations[i][j]].add(observations[i][j + 1]);
				++indegree[observations[i][j + 1]];
			}
		}

		// Queue non-dependent cows in lexicographical order
		PriorityQueue<Integer> pq = new PriorityQueue<>();
		for (int cow = 1; cow <= n; ++cow) 
			if (indegree[cow] == 0) 
				pq.add(cow);

		// Traverse non-dependent cows in lexicographical order from graph
		int[] tempAnswer = new int[n];
		int visits = 0;
		for (visits = 0; !pq.isEmpty(); ++visits) {
			int cow = pq.poll();
			tempAnswer[visits] = cow;

			for (int adj : graph[cow]) {
				--indegree[adj];	// Remove the edge from the adjacent cow/node
				if (indegree[adj] == 0) 
					pq.add(adj);
			}
		}

		// Check if all cows/nodes were visited
		if (visits < n) 
			return false;
		answer = tempAnswer;
		return true;
	}
}
```
