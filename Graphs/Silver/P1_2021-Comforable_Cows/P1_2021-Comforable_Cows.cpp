#include <bits/stdc++.h>

#define N_MAX 100001
#define SIDE_MAX 1001

using namespace std;

int main() {
	// Read first line: n = number of cows
	int n;
	cin >> n;
	bitset<SIDE_MAX * 3> grid[SIDE_MAX * 3] = {};
	static const pair<int, int> directions[4] = {
		{0, 1}, {0, -1}, {1, 0}, {-1, 0}
	};

	// For the next n lines read in coordinates of cows
	queue<pair<int, int>> cowsToPlace;
	int totalCows = 0;
	for (int initialCow = 1; initialCow <= n; ++initialCow) {
		int x, y;
		cin >> x >> y;
		cowsToPlace.push({x + 1000, y + 1000});	// Shift to avoid negative indices

		// Queue cows to make target cow uncomfortable
		function <void(int, int)> reEvalute = [&](int x, int y) -> void {
			if (!grid[x][y]) 
				return;

			int adjCount = 0;
			for (const pair<int, int>& d : directions) 
				if (grid[x + d.first][y + d.second]) 
					++adjCount;
			
			// If cow is uncomfortable ignore it
			if (adjCount != 3) 
				return;

			// Else queue neighboring cells to make target cow uncomfortable
			for (const pair<int, int>& d : directions) 
				if (!grid[x + d.first][y + d.second]) 
					cowsToPlace.push({x + d.first, y + d.second});
		};

		while (!cowsToPlace.empty()) {
			pair<int, int> loc = cowsToPlace.front();
			cowsToPlace.pop();
			if (grid[loc.first][loc.second]) 
				continue;
			
			++totalCows;
			grid[loc.first][loc.second] = 1;	// Place cow

			reEvalute(loc.first, loc.second);	// Check if cow is uncomfortable
			for (const pair<int, int>& d : directions) 
				reEvalute(loc.first + d.first, loc.second + d.second);
		}
		cout << totalCows - initialCow << endl;
	}

	return 0;
}