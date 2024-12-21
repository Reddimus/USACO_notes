#include <bits/stdc++.h>
#define N_MAX 101
#define COLS 10

using namespace std;

int main() {
	freopen("mooyomooyo.in", "r", stdin);
	// Read in first line: n = rows, k = min tetris pop size
	int n, k;
	cin >> n >> k;
	// For the next N lines, read in the grid
	char grid[N_MAX][COLS];
	for (int r = 0; r < n; r++) {
		string currRow;
		cin >> currRow;
		for (int c = 0; c < COLS; c++) {
			grid[r][c] = currRow[c];
		}
	}

	pair<int, int> directions[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	bool gridChanged = true;
	while (gridChanged) {
		gridChanged = false;
		for (int r = 0; r < n; r++) {
			for (int c = 0; c < COLS; c++) {
				if (grid[r][c] == '0') 
					continue;

				// Perform a BFS to find all connected cells
				queue<pair<int, int>> q;
				q.push({r, c});
				vector<pair<int, int>> connected;
				while (!q.empty()) {
					auto [currR, currC] = q.front();
					q.pop();

					for (auto [dr, dc] : directions) {
						int nxtR = currR + dr, nxtC = currC + dc;
						if (nxtR < 0 || nxtR >= n ||
						nxtC < 0 || nxtC >= COLS ||
						grid[nxtR][nxtC] != grid[r][c])
							continue;

						q.push({nxtR, nxtC});
					}
				}

				if (connected.size() < k) 
					continue;

				// If the size of the connected cells is greater than k, pop them
				
			}
		}
	}

	// Print out the grid
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < COLS; c++) {
			cout << grid[r][c];
		}
		cout << endl;
	}
	cout << endl;
	return 0;
}
