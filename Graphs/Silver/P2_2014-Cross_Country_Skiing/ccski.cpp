#include <bits/stdc++.h>
#define MAX_SIDE 502

using namespace std;

int main() {
	freopen("ccski.in", "r", stdin);
	// Read in first line: n = rows, m = columns
	int n, m;
	cin >> n >> m;
	// For the next n lines, read in the elevations
	int maxElevation = 0;
	int elevations[MAX_SIDE][MAX_SIDE];
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			cin >> elevations[r][c];
			maxElevation = max(maxElevation, elevations[r][c]);
		}
	}
	// For the next n lines, read in the waypoints
	bitset<MAX_SIDE> waypoints[MAX_SIDE];
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			bool waypoint;
			cin >> waypoint;
			waypoints[r][c] = waypoint;
		}
	}

	// Find the starting waypoint coordinates
	int wrs = 0, wcs = 0;
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			if (waypoints[r][c]) {
				wrs = r;
				wcs = c;
				break;
			}
		}
	}

	pair<int, int> directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	function<bool(int)> reachable = [&](int d) {
		queue<pair<int, int>> q;

		q.push({wrs, wcs});
		bitset<MAX_SIDE> visited[MAX_SIDE];
		visited[wrs][wcs] = true;

		while (!q.empty()) {
			auto [r, c] = q.front();
			q.pop();

			for (auto [dr, dc] : directions) {
				int nr = r + dr, nc = c + dc;
				if (nr < 0 || nr >= n ||
				nc < 0 || nc >= m ||
				visited[nr][nc] ||
				abs(elevations[r][c] - elevations[nr][nc]) > d)
					continue;

				if 
			}
		}
	};

	// Binary search for the elevation difference
	int lo = 0, hi = maxElevation;
	while (lo < hi) {
		int d = lo + (hi - lo) / 2;
		if (reachable(d))
			hi = d;
		else
			lo = d + 1;
	}

	// Output the result
	cout << lo << endl;
	return 0;
}
