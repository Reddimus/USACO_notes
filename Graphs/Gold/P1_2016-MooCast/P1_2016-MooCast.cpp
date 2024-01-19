// Graphs - Disjoint Set Union (DSU) approach
// T: O(n^2 * log(n)), M: O(n^2), where n is the number of cows

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