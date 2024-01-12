// Graphs - Disjoint Set Union (DSU) approach
// T: O((N + Q)log(N + Q) + N * α(N) + Q), M: O(N + Q)
// Where N = number of videos, Q = number of questions, and α(N) ≈ O(1) ≈ inverse Ackermann function

#include <bits/stdc++.h>

using namespace std;

class DisjointSetUnion {
public:
	vector<int> parentOrSize;	// less space, more runtime
	// Initialize parentOrSize array of size n with negative sizes
	DisjointSetUnion(int n) : parentOrSize(n, -1) {}

	// Recursively find and assign parent (optimization) of current node
	int get_parent(int node) {
		if (parentOrSize[node] < 0)
			return node;
		return parentOrSize[node] = get_parent(parentOrSize[node]);
	}

	// Recursively find size of component of current node
	int size(int x) {
		return -parentOrSize[get_parent(x)];
	}

	// Attempt to union two components
	bool unite(int a, int b) {
		a = get_parent(a), b = get_parent(b);
		if (a == b)	// If nodes are already in same component
			return false;
		
		if (parentOrSize[a] > parentOrSize[b])
			swap(a, b);	// Union by size optimization
		// Merge the smaller component into the larger component
		parentOrSize[a] += parentOrSize[b];
		parentOrSize[b] = a;
		return true;
	}
};

int main() {
	freopen("mootube.in", "r", stdin);
	// Read in First Line: n = # of videos, q = # of questions
	int n, q;
	cin >> n >> q;
	// For the next n-1 lines, read in edges of the graph network
	vector<pair<int, pair<int, int>>> edges(n-1);
	for (int i = 0; i < n-1; ++i) {
		int pi, qi, ri;
		cin >> pi >> qi >> ri;
		edges[i] = {ri, {--pi, --qi}};
	}
	// For the next q lines, read in FJ's questions
	vector<pair<int, pair<int, int>>> queries(q);
	for (int i = 0; i < q; ++i) {
		int ki, vi;	// ki = minimum relevance, vi = video
		cin >> ki >> vi;
		queries[i] = {i, {ki, --vi}};
	}

	// Sort edges and queries by descending relevance
	sort(edges.begin(), edges.end(), 
	[](const pair<int, pair<int, int>> &a, const pair<int, pair<int, int>> &b) {
		return a.first > b.first;
	});
	sort(queries.begin(), queries.end(), 
	[](const pair<int, pair<int, int>> &a, const pair<int, pair<int, int>> &b) {
		return a.second.first > b.second.first;
	});

	DisjointSetUnion dsu(n);
	vector<int> querySuggestions(q);
	int eIdx = 0;
	// For each query, count suggested videos by joining edges with enough relevance
	for (pair<int, pair<int, int>>& query : queries) {
		int queryOrder = query.first;
		int k = query.second.first, v = query.second.second;
		// While the current edge's relevance >= the query's relevance
		while (eIdx < n-1 && edges[eIdx].first >= k) {
			dsu.unite(edges[eIdx].second.first, edges[eIdx].second.second);
			++eIdx;
		}
		// Suggested videos are the size of the component minus the video itself
		querySuggestions[queryOrder] = dsu.size(v) - 1;
	}

	// Write the number of suggested videos for each query in initial order
	freopen("mootube.out", "w", stdout);
	for (int suggestions : querySuggestions)
		cout << suggestions << endl;
	return 0;
}