// Graphs - Disjoint Set Union (DSU) approach
// T: O(N + M * alpha(N)), M: O(N + M)
// Where N = # of barns, M = # of paths, and α(N) ≈ O(1) ≈ inverse Ackermann function

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