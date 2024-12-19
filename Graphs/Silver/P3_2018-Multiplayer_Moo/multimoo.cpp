#include <bits/stdc++.h>
#define MAX_N 251

using namespace std;

int main() {
	freopen("multimoo.in", "r", stdin);
	// Read in the first line: n = side length of the square grid
	int n;
	cin >> n;
	// For the next n lines read in the grid
	int grid[MAX_N][MAX_N];
	for (int r = 0; r < n; r++)
		for (int c = 0; c < n; c++)
			cin >> grid[r][c];

	// Flood fill to find the size of the largest connected component
	vector<vector<set<pair<int, int>>>> visited(n, vector<set<pair<int, int>>>(n, set<pair<int, int>>()));
	function<int(int, int, int, int)> searchConnectedComponentSize = [&](int r, int c, int id1, int id2) -> int {
		if (r < 0 || r >= n ||
		c < 0 || c >= n ||
		grid[r][c] != id1 && grid[r][c] != id2 ||
		visited[r][c].find({id1, id2}) != visited[r][c].end())
			return 0;

		visited[r][c].insert({id1, id2});

		return (
			1 +
			searchConnectedComponentSize(r - 1, c, id1, id2) +
			searchConnectedComponentSize(r + 1, c, id1, id2) +
			searchConnectedComponentSize(r, c - 1, id1, id2) +
			searchConnectedComponentSize(r, c + 1, id1, id2)
		);
	};

	// Find the size of the largest individual component
	int maxComponentSize = 0;
	for (int r = 0; r < n; r++)
		for (int c = 0; c < n; c++)
			maxComponentSize = max(maxComponentSize, searchConnectedComponentSize(r, c, grid[r][c], grid[r][c]));

	// Find the size of the largest connected component (two adjacent components)
	int maxConnectedComponentSize = 0;
	for (int r = 0; r < n - 1; r++) {
		for (int c = 0; c < n - 1; c++) {
			if (grid[r][c] < grid[r][c + 1])
				maxConnectedComponentSize = max(maxConnectedComponentSize, searchConnectedComponentSize(r, c, grid[r][c], grid[r][c + 1]));
			else if (grid[r][c] > grid[r][c + 1])
				maxConnectedComponentSize = max(maxConnectedComponentSize, searchConnectedComponentSize(r, c + 1, grid[r][c + 1], grid[r][c]));

			if (grid[r][c] < grid[r + 1][c])
				maxConnectedComponentSize = max(maxConnectedComponentSize, searchConnectedComponentSize(r, c, grid[r][c], grid[r + 1][c]));
			else if (grid[r][c] > grid[r + 1][c])
				maxConnectedComponentSize = max(maxConnectedComponentSize, searchConnectedComponentSize(r + 1, c, grid[r + 1][c], grid[r][c]));
		}
	}

	// Write the largest individual component size & the largest connected component size to the output file
	freopen("multimoo.out", "w", stdout);
	cout << maxComponentSize << endl;
	cout << maxConnectedComponentSize << endl;
	return 0;
}
