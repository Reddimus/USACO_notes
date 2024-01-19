// Graphs - Flood Fill/Depth First Search approach
// T & M: O(n^2 + x * y)
// Where n is the number of steps Farmer John takes and x & y are the number of steps between the min and max x/y coordinates of the fence.

#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("gates.in", "r", stdin);
	int n;			// Number of steps
	string moves;	// Directions of steps (North, East, South, West)
	cin >> n >> moves;

	// Initialize starting position and set of fence coordinates
	int sides = n * 4 + 1;
	int x = sides / 2, y = sides / 2;
	int minX = sides - 1, minY = sides - 1;
	int maxX = 0, maxY = 0;
	vector<vector<bool>> fences(sides, vector<bool>(sides, false));
	fences[y][x] = true;

	// Track fence positions based on Farmer John's movements
	unordered_map<char, pair<int, int>> directions {
		{'N', {0, -1}}, 	// Move up 1 row in array
		{'E', {1, 0}}, 
		{'S', {0, 1}}, 		// Move down 1 row in array
		{'W', {-1, 0}}};
	for (char& m : moves) {
		// Scale movements by 2 steps to view smallest regions
		x += directions[m].first, y += directions[m].second;
		fences[y][x] = true;
		x += directions[m].first, y += directions[m].second;
		fences[y][x] = true;
		minX = min(minX, x), minY = min(minY, y);
		maxX = max(maxX, x), maxY = max(maxY, y);
	}

	// Expand boundaries to include outer region surrounding the fence
	--minX, --minY, ++maxX, ++maxY;

	// Flood-fill/depth first search for current component
	vector<vector<bool>> seen(sides, vector<bool>(sides, false));
	function<void(int, int)> dfs = [&](int x, int y) {
		if (x < minX || maxX < x ||
		y < minY || maxY < y ||
		seen[y][x] || 
		fences[y][x]) 
			return;

		seen[y][x] = true;

		dfs(x + 1, y);
		dfs(x - 1, y);
		dfs(x, y + 1);
		dfs(x, y - 1);
	};

	// Find number of regions our fence graph is split into
	int regions = 0;
	for (int y = minY; y <= maxY; ++y) {
		for (int x = minX; x <= maxX; ++x) {
			if (!seen[y][x] && !fences[y][x]) {
				dfs(x, y);
				++regions;
			}
		}
	}

	// Every region inside the fences needs a gate
	freopen("gates.out", "w", stdout);
	cout << regions - 1 << endl;
	return 0;
}