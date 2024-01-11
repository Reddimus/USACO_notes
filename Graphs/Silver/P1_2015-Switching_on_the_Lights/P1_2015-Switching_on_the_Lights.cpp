// Graphs - Breadth First Search (DFS) | Flood fill approach
// T & M: O(n^2 + m) 
// Where n is the number of rows and columns in the switches graph and m is the number of switches

#include <bits/stdc++.h>

using namespace std;

struct indices {const int row, col;};

int main() {
	freopen("lightson.in", "r", stdin);
	// First line: n = graph side length, m = # of switches
	int n, m;
	cin >> n >> m;
	// For the next m lines map x, y room to room a, b that can be lit
	vector<vector<vector<indices>>> switches(n, vector<vector<indices>>(n));
	for (int ln = 0; ln < m; ++ln) {
		int x, y, a, b;
		cin >> x >> y >> a >> b;
		switches[x - 1][y - 1].push_back({a - 1, b - 1});
	}

	vector<indices> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	vector<vector<bool>> seen(n, vector<bool>(n)), lit(n, vector<bool>(n));
	queue<indices> q;

	int litCount = 1;
	lit[0][0] = true;
	q.push({0, 0});
	while (!q.empty()) {
		indices qd = q.front();
		q.pop();
		if (seen[qd.row][qd.col]) 
			continue;
		seen[qd.row][qd.col] = true;

		// Turn on new lights of current room
		for (indices& sw : switches[qd.row][qd.col]) {
			if (lit[sw.row][sw.col])
				continue;
			lit[sw.row][sw.col] = true;
			++litCount;
			// Check if the newly lit room can be connected and hasn't been visited
			for (indices& d : directions) {
				const int aswr = sw.row + d.row, aswc = sw.col + d.col;
				if ((-1 < aswr && aswr < n) && 
				(-1 < aswc && aswc < n) && 
				seen[aswr][aswc] &&
				!seen[sw.row][sw.col])
					q.push(sw);
			}
		}

		// Explore valid adjacent rooms
		for (indices& d : directions) {
			const int ar = qd.row + d.row, ac = qd.col + d.col;
			if ((-1 < ar && ar < n) && 
			(-1 < ac && ac < n) &&
			lit[ar][ac] &&
			!seen[ar][ac])
				q.push({ar, ac});
		}
	}

	// Write number of lit rooms accessible from (1, 1) to output file
	freopen("lightson.out", "w", stdout);
	cout << litCount << endl;
	return 0;
}