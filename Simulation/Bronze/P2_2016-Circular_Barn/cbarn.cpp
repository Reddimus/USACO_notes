#include <bits/stdc++.h>
#define MAX_ROOMS 1001

using namespace std;

int main() {
	freopen("cbarn.in", "r", stdin);
	// Read in total number of rooms
	int n;
	cin >> n;
	// Read in the number of cows in each room
	int rooms[MAX_ROOMS];
	for (int i = 0; i < n; i++)
		cin >> rooms[i];

	// Try each room as the first room to unlock
	int minDist = INT_MAX;
	for (int unlock = 0; unlock < n; unlock++) {
		int dist = 0;
		for (int r = 0; r < n; r++) 
			dist += rooms[(unlock + r) % n] * r;
		minDist = min(minDist, dist);
	}

	freopen("cbarn.out", "w", stdout);
	cout << minDist << endl;
	return 0;
}
