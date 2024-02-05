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
	for (int idx = 0; idx < c; ++idx) {
		// Session b happened at least x days after session a
		int a, b, x;
		cin >> a >> b >> x;
		memories[a].push_back({b, x});
	}

	// Build topological order of memory graph
	vector<int> topologicalOrder;
	vector<bool> visited(n+1);

	function<void(int)> build_order = [&](int day) {
		if (visited[day]) 
			return;

		visited[day] = true;

		for (pair<int, int>& m : memories[day]) 
			if (!visited[m.first])
				build_order(m.first);

		topologicalOrder.push_back(day);
	};

	for (int day = 1; day <= n; ++day) 
		build_order(day);
	
	// Update session dependencies in reverse topological order of the memory graph
	for (int idx = n - 1; idx >= 0; --idx) {
		int a = topologicalOrder[idx];
		for (pair<int, int>& m : memories[a]) {
			int b = m.first, x = m.second;
			sessions[b] = max(sessions[b], sessions[a] + x);
		}
	}

	// Write 1-indexed session answers to output file
	freopen("timeline.out", "w", stdout);
	for (int idx = 1; idx <= n; ++idx) 
		cout << sessions[idx] << endl;
	return 0;
}