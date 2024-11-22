#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("mootube.in", "r", stdin);
	// Read in first line: n = number of videos, q = number of questions
	int n, q;
	cin >> n >> q;
	// Create adjacency list
	vector<vector<pair<int, int>>> adj(n + 1);
	// For the next n lines, read in node neighbors and relevance weights
	for (int ln = 1; ln < n; ln++) {
		int a, b, r;
		cin >> a >> b >> r;
		adj[a].push_back({b, r});
		adj[b].push_back({a, r});
	}

	freopen("mootube.out", "w", stdout);
	// For the next q lines, read in the threshold and starting node
	for (int ln = 0; ln < q; ++ln) {
		int r, v;
		cin >> r >> v;

		// Search for the # of videos that can be reached with >= (r)elevance
		int audienceReach = 0;
		bitset<5001> visited;
		visited[v] = true;
		queue<int> q;
		q.push(v);
		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			for (auto& [nxt, w] : adj[cur]) {
				if (!visited[nxt] && w >= r) {
					visited[nxt] = true;
					++audienceReach;
					q.push(nxt);
				}
			}
		}

		// Write the audience reach to the output file for the current query
		cout << audienceReach << endl;
	}
}