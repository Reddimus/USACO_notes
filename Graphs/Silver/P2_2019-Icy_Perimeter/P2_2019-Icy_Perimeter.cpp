// Breadth First Search (BFS) | Flood fill Graph approach
// T & M: O(n^2) where n is the side length of the grid

#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("perimeter.in", "r", stdin);
	// First line: n = sides of graph
	int n;
	cin >> n;
	// For the next n lines read n sized strings representing ice cream blob graph
	vector<vector<char>> graph(n, vector<char>(n));
	for (int r = 0; r < n; ++r)
		for (int c = 0; c < n; ++c)
			cin >> graph[r][c];

	struct indices { const int row, col; };
	struct blob { int area, perimeter; };
	indices directions[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	// Breadth First Search (BFS) perimeter and area of blob
	function<blob(int, int)> bfs = [&](int r, int c) -> blob {
		int area = 1, perimeter = 0;
		graph[r][c] = ' ';	// Mark as visited
		queue<indices> q;
		q.push({r, c});
		while (!q.empty()) {
			indices qd = q.front();
			q.pop();

			for (const indices& d : directions) {
				int ar = qd.row + d.row, ac = qd.col + d.col;
				// If adjacent row/col outside of blob
				if (ar < 0 || ar >= n || 
				ac < 0 || ac >= n || 
				graph[ar][ac] == '.') {
					++perimeter;
				} 
				// Else if adjacent row/col is part of the same blob component
				else if (graph[ar][ac] == '#') {
					++area;
					graph[ar][ac] = ' ';
					q.push({ar, ac});
				}
			}
		}
		return {area, perimeter};
	};

	blob maxBlob = {0, n + 1};
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			// Group blobs into their own components and update largest blob
			if (graph[r][c] == '#') {
				blob currBlob = bfs(r, c);
				// Update blob to largest area then smallest perimeter
				if (maxBlob.area < currBlob.area ||
				(maxBlob.area == currBlob.area && maxBlob.perimeter > currBlob.perimeter))
					maxBlob = currBlob;
			}
		}
	}

	// Write largest blob with smallest perimeter to output file
	freopen("perimeter.out", "w", stdout);
	cout << maxBlob.area << " " << maxBlob.perimeter << endl;
	return 0;
}