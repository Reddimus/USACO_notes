// Adjacency List Graphs - Topological Sort approach
// T & M: O(N + M), where N = # of sessions, M =  total days

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
	
	// Update session dependencies in reverse topological order of the memory graph
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