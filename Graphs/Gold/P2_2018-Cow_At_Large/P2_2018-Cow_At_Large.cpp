// Graphs - Breath-First Search (BFS) w/ greedy approach
// T & M: O(V + E), where V = N = # of barns, E = # of paths/tunnels

#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("atlarge.in", "r", stdin);
	// Read in first line: n = # of barns, k = Bessie's starting barn
	int n, k;
	cin >> n >> k;
	// For the next n - 1 lines, read in the barns connected by a path/tunnel
	vector<vector<int>> graph(n);
	for (int ln = 0; ln < n - 1; ++ln) {
		int t1, t2;
		cin >> t1 >> t2;
		graph[--t1].push_back(--t2);
		graph[t2].push_back(t1);
	}

	vector<int> exits;
	for (int idx = 0; idx < n; ++idx)
		if (graph[idx].size() == 1)
			exits.push_back(idx);

	vector<int> distFarmer(n, -1);	// stores min steps for farmer to reach node
	for (int& exit : exits)
		if (distFarmer[exit] == -1)
			distFarmer[exit] = 0;	// initialize exit nodes to 0 steps

	// BFS to compute the minimum steps for farmers to reach each barn from exits
	queue<int> q;
	for (int& exit : exits)
		q.push(exit);
	while (!q.empty()) {
		int qdBarn = q.front();
		q.pop();

		for (int& adj : graph[qdBarn]) {
			// If adjacent barn has not yet been mapped to minumum steps
			if (distFarmer[adj] == -1) {
				distFarmer[adj] = distFarmer[qdBarn] + 1;	// increment farmer's steps
				q.push(adj);
			}
		}
	}

	int farmersNeeded = 0;
	
	vector<int> distBessie(n, -1);	// stores min steps for bessie to reach node
	distBessie[k - 1] = 0;			// initialize Bessie's starting node to 0 steps

	// As Bessie explores the graph, count the farmers needed to catch her using BFS
	q.push(k - 1);
	while (!q.empty()) {
		int qdBarn = q.front();
		q.pop();

		// If Bessie's current step count >= farmer's current step count
		if (distBessie[qdBarn] >= distFarmer[qdBarn]) {
			++farmersNeeded;	// A farmer could catch Bessie at this barn
			continue;			// no need to explore subgraph further
		}

		for (int& adj : graph[qdBarn]) {
			// If adjacent barn has not yet been visited by Bessie
			if (distBessie[adj] == -1) {
				distBessie[adj] = distBessie[qdBarn] + 1;	// increment Bessie's steps
				q.push(adj);
			}
		}
	}

	// Write the number of farmers needed to catch Bessie to output file
	freopen("atlarge.out", "w", stdout);
	cout << farmersNeeded << endl;
	return 0;
}