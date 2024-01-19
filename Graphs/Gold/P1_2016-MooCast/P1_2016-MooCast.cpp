// Graphs - Minimum Spanning Tree (MST) approach
// T: O(n^2), M: O(n), where n is the number of cows

#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("moocast.in", "r", stdin);
	// First line: n = number of cows
	int n;
	cin >> n;
	// For the next n lines read in coordinates of cows
	vector<pair<int, int>> coords(n);
	for (int idx = 0; idx < n; ++idx)
		cin >> coords[idx].first >> coords[idx].second;

	// Initialize answer variable and distance array (idx of coordinate -> distance)
	vector<int> distance(n, INT_MAX - 1);
	distance[0] = 0;
	int spend = 0;

	// For every cow, find the closest cow and update answer
	for (int cow = 0; cow < n; ++cow) {
		int i = min_element(distance.begin(), distance.end()) - distance.begin();
		spend = max(spend, distance[i]);
		distance[i] = INT_MAX;
		for (int j = 0; j < n; ++j) {
			if (distance[j] == INT_MAX)
				continue;
			int dx = coords[i].first - coords[j].first;
			int dy = coords[i].second - coords[j].second;
			int dist = (dx * dx) + (dy * dy);
			distance[j] = min(distance[j], dist);
		}
	}

	// Write the minimum distance/price to spend to the output file
	freopen("moocast.out", "w", stdout);
	cout << spend << endl;
	return 0;
}

/*
// T: O(n^2)

#include <bits/stdc++.h>
using namespace std;

#define dis(x, y) (p[x].first - p[y].first) * (p[x].first - p[y].first) + (p[x].second - p[y].second) * (p[x].second - p[y].second)

class UF {
private:
    vector<int> parent;

public:
    int count;
    UF(int n) {
        for (int i = 0; i <= n; i++)
            parent.push_back(i);
        count = n; // Initialize count to n
    }

    int find(int x) {
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void Union(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
            count--; // Decrement count only when a merge occurs
        }
    }

    bool connected(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        return rootX == rootY;
    }
};

int n;
pair<int, int> p[1001];

bool help(int k) {
    UF u(n);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (dis(i, j) <= k)
                u.Union(i, j);
        }
    }
    return u.count == 1; // Check if all cows are connected
}

int main() {
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i].first >> p[i].second;
    }
    int l = 0, r = INT_MAX; // Use a larger range for r
    while (l <= r) {
        int mid = (l + r) / 2;
        if (help(mid))
            r = mid - 1;
        else
            l = mid + 1;
    }
    cout << l << endl;
    return 0;
}
*/

/*
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
*/