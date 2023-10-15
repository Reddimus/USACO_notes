#include <bits/stdc++.h>
// #include <iostream>
// #include <vector>
// #include <deque>
// #include <algorithm>
// #include <climits>

#define ll long long

using namespace std;

int main() {
	freopen("cbarn2.in", "r", stdin);
	// Read first line: n = rooms, k = unlocked exterior doors
	int n, k;
	cin >> n >> k;
	// For the next n lines, read in the desired number of cows in each room (r_i)
	deque<int> rooms(n);
	for (int &r : rooms)
		cin >> r;
	
	// // print rooms deque
	// cout << "rooms deque: ";
	// for (int r : rooms)
	// 	cout << r << " ";
	// cout << endl << endl;

	ll minDist = INT64_MAX;
	// Rotate through all the starting position of the rooms for each dp table
	for (int startPos = 0; startPos < n; ++startPos) {
		vector<vector<ll>> dp(k + 1, vector<ll>(n + 1, INT64_MAX));
		dp[0][n] = 0;   // 0 doors unlocked base case
		// Iterate through all possible number of doors unlocked
		for (int unlockedDoors = 1; unlockedDoors <= k; ++unlockedDoors) {
			// Iterate through all possible positions to place this new door
			for (int newDoorPos = 0; newDoorPos < n; ++newDoorPos) {
				if (unlockedDoors >= k && newDoorPos >= 1)  // If dp[k][0] is done calculating
					break;
				// Calculate distance for rooms between new and last door
				ll partialDist = 0;
				// Loop through last door positions
				for (int lastDoorPos = newDoorPos + 1; lastDoorPos <= n; ++lastDoorPos) {
					// Add distance needed to fill the new room at lastDoorPos - 1
					partialDist += rooms[lastDoorPos - 1] * (lastDoorPos - newDoorPos - 1);
					ll newDist = dp[unlockedDoors - 1][lastDoorPos];
					if (newDist < INT64_MAX)
						newDist += partialDist;
					dp[unlockedDoors][newDoorPos] = min(dp[unlockedDoors][newDoorPos], newDist);

					// // print dp table
					// cout << "dp table at startPos = " << startPos << ", unlockedDoors = " << unlockedDoors << ", newDoorPos = " << newDoorPos << ", lastDoorPos = " << lastDoorPos << endl;
					// for (int DoorPos = 0; DoorPos <= n; ++DoorPos)
					// 	cout << "DoorPos " << DoorPos << "	";
					// cout << endl;
					// for (int unlockedDoors = 0; unlockedDoors <= k; ++unlockedDoors) {
					// 	cout << "unlockedDoors = " << unlockedDoors << ": ";
					// 	for (int newDoorPos = 0; newDoorPos <= n; ++newDoorPos) {
					// 		if (dp[unlockedDoors][newDoorPos] == INT64_MAX)
					// 			cout << "inf" << " ";
					// 		else
					// 			cout << dp[unlockedDoors][newDoorPos] << " ";
					// 	}
					// 	cout << endl;
					// }
					// cout << endl;
				}
			}
		}
		// Update the best answer using the current dp with current starting position
		minDist = min(minDist, dp[k][0]);
		// Rotate first room to end
		rooms.push_back(rooms.front());
		rooms.pop_front();

		// cout << "minDist = min(minDist, dp[" << k << "][0]) = min(" << minDist << ", " << dp[k][0] << ") = " << min(minDist, dp[k][0]) << endl;
		// // print rooms deque
		// cout << "rooms deque: ";
		// for (int r : rooms)
		// 	cout << r << " ";
		// cout << endl << endl;
	}

	// Write the minDist accross all starting positions, with all possible doors unlocked
	freopen("cbarn2.out", "w", stdout);
	cout << minDist << endl;
}
