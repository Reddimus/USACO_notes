// Depth First Search (DFS) | Flood Fill Graph approach
// T & M: O(n^2), where n is the side length of the grid

#include <bits/stdc++.h>

using namespace std;

struct Road { int sr, sc, er, ec; };
// Implement comparator to use Road struct in set
inline bool operator<(const Road &a, const Road &b) {
	return tie(a.sr, a.sc, a.er, a.ec) < tie(b.sr, b.sc, b.er, b.ec);
}

int main() {
	freopen("countcross.in", "r", stdin);
	// Read in first line: n = grid side length, k = # of cows, r = # of roads
	int n, k, r;
	cin >> n >> k >> r;
	// Read in start (r, c) and end (r', c') positions of two-way roads
	set<Road> roads;
	for (int ln = 0; ln < r; ++ln) {
		int sr, sc, er, ec;
		cin >> sr >> sc >> er >> ec;
		roads.insert({--sr, --sc, --er, --ec});
		roads.insert({er, ec, sr, sc});
	}
	// Read in start (r, c) positions of cows
	vector<vector<bool>> cows(n, vector<bool>(n, false));
	for (int ln = 0; ln < k; ++ln) {
		int r, c;
		cin >> r >> c;
		cows[--r][--c] = true;
	}

	vector<vector<bool>> visited(n, vector<bool>(n, false));

	// Depth first search number of cows that can be reached without crossing a road
	function<int(int, int, int, int)> dfs = [&](int r, int c, int pr, int pc) -> int {
		if (r < 0 || n <= r ||
		c < 0 || n <= c ||
		visited[r][c] ||
		roads.count(Road{r, c, pr, pc}))
			return 0;

		visited[r][c] = true;
		
		return (cows[r][c] +
		dfs(r + 1, c, r, c) +
		dfs(r - 1, c, r, c) +
		dfs(r, c + 1, r, c) +
		dfs(r, c - 1, r, c));
	};

	// Group size of cow components to calculate distant pairs
	vector<int> cowComponents;
	for (int r = 0; r < n; ++r)
		for (int c = 0; c < n; ++c)
			if (!visited[r][c] && cows[r][c])
				cowComponents.push_back(dfs(r, c, r, c));

	// Sum product of pairs from distinct cow groups for distant pairs
	int distantPairs = 0;
	for (int i = 0; i < cowComponents.size(); ++i)
		for (int j = i + 1; j < cowComponents.size(); ++j)
			distantPairs += cowComponents[i] * cowComponents[j];

	// Write number of distant pairs to output file
	freopen("countcross.out", "w", stdout);
	cout << distantPairs << endl;
	return 0;
}