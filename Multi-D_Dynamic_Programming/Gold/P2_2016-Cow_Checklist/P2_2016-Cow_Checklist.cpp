// Paths on Grids + 3-D Dynamic Programming approach
// T&M: O(h * g), where h = Holsteins, g = Guernseys

#define ui unsigned int

#include <bits/stdc++.h>

using namespace std;

struct Coordinates {int x, y;};

// Find the distance between two points then square it
ui energy(const Coordinates &a, const Coordinates &b) {
	int xDist = a.x - b.x;
	int yDist = a.y - b.y;
	return (xDist * xDist) + (yDist * yDist);
}

/*
void print3DArr(vector<vector<vector<ui>>> &arr) {
	cout << "[";
	for (int idx = 0; idx < arr.size(); ++idx) {
		cout << "[";
		for (int jdx = 0; jdx < arr[idx].size(); ++jdx) {
			cout << "[";
			for (int kdx = 0; kdx < arr[idx][jdx].size(); ++kdx) {
				if (INT_MAX - 1 <= arr[idx][jdx][kdx])
					cout << "INF";
				else
					cout << arr[idx][jdx][kdx];
				
				if (kdx != arr[idx][jdx].size() - 1)
					cout << ", ";
			}
			cout << "]";
			if (jdx != arr[idx].size() - 1)
				cout << ", ";
		}
		cout << "]";
		if (idx != arr.size() - 1)
			cout << ", " << endl;
	}
	cout << "]" << endl << endl;
}
*/

int main() {
	freopen("checklist.in", "r", stdin);
	// Read first line input: h = Holstein num, g = guernseys num
	int h, g;
	cin >> h >> g;
	// For the next H lines then next G lines read breed coordinates
	Coordinates hs[h], gs[g];
	for (int idx = 0; idx < h; ++idx)
		cin >> hs[idx].x >> hs[idx].y;
	for (int idx = 0; idx < g; ++idx)
		cin >> gs[idx].x >> gs[idx].y;
	
	// Pre-compute all the distance energies
	// Energy between neighbouring holsteins, where hIdx = 0 is a dummy value
	vector<ui> hsEnergy(h, 0);
	for (int hIdx = 1; hIdx < h; ++hIdx)
		hsEnergy[hIdx] = energy(hs[hIdx], hs[hIdx - 1]);
	// Energy between neighbouring guernseys, where gIdx = 0 is a dummy value
	vector<ui> gsEnergy(g, 0);
	for (int gIdx = 1; gIdx < g; ++gIdx)
		gsEnergy[gIdx] = energy(gs[gIdx], gs[gIdx - 1]);
	// Energy between holsteins and guernseys
	vector<vector<ui>> crossEnergy(h, vector<ui>(g));
	for (int hIdx = 0; hIdx < h; ++hIdx) {
		for (int gIdx = 0; gIdx < g; ++gIdx) {
			crossEnergy[hIdx][gIdx] = energy(hs[hIdx], gs[gIdx]);
		}
	}

	// dp[h+1][g+1][2] filled with MAX values to solve for min dist across breeds
	// where hIdx = 0 are dummy values, & gIdx = 0 are base cases/dummy values
	// Where the 3rd dimension is 0 = Holstein, 1 = Guernsey
	vector<vector<vector<ui>>> dp(h + 1, vector<vector<ui>>(g + 1, vector<ui>(2, INT_MAX)));
	dp[1][0][0] = 0;	// Base case: Start with 0 distance
	for (int hIdx = 1; hIdx <= h; ++hIdx) {
		for (int gIdx = 0; gIdx <= g; ++gIdx) {
			// Check neighboring holsteins distances
			if (hIdx > 1) {
				dp[hIdx][gIdx][0] = 
					min(dp[hIdx][gIdx][0], dp[hIdx - 1][gIdx][0] + hsEnergy[hIdx - 1]);
			}
			// Check neighboring guernseys distances
			if (gIdx > 1) {
				dp[hIdx][gIdx][1] = 
					min(dp[hIdx][gIdx][1], dp[hIdx][gIdx - 1][1] + gsEnergy[gIdx - 1]);
			}
			// Check across breeds distances
			if (hIdx > 0 && gIdx > 0) {
				dp[hIdx][gIdx][0] = 
					min(dp[hIdx][gIdx][0], dp[hIdx - 1][gIdx][1] + crossEnergy[hIdx - 1][gIdx - 1]);
				dp[hIdx][gIdx][1] = 
					min(dp[hIdx][gIdx][1], dp[hIdx][gIdx - 1][0] + crossEnergy[hIdx - 1][gIdx - 1]);
			}
			// print3DArr(dp);
		}
	}

	freopen("checklist.out", "w", stdout);
	cout << dp[h][g][0] << endl;
}