// 2-D Dynamic Programming + Deque 
// T: O(n^3 * k), M: O(k * n)
// Where n = number of rooms, k = number of doors to unlock

#include <bits/stdc++.h>

#define ll long long

using namespace std;

int main() {
	freopen("cbarn2.in", "r", stdin);
	// Read first line: n = rooms, k = unlocked exterior doors
	int n, k;
	cin >> n >> k;
	// For the next n lines, read the number of cows in each room (r_i)
	deque<int> rooms(n);
	for (int &r : rooms)
		cin >> r;
	// print rooms deque
	cout << "rooms deque: ";
	for (int r : rooms)
		cout << r << " ";
	cout << endl << endl;

	ll minDist = INT64_MAX;
	// Iterate through all possible starting rooms
	for (int startPos = 0; startPos < n; ++startPos) {
		vector<vector<ll>> dp(k + 1, vector<ll>(n + 1, INT64_MAX));
		// With no door used, the distance is 0 if there is no room filled
		dp[0][n] = 0;
		// Iterate through number of doors used
		for (int usedDoor = 1; usedDoor <= k; ++usedDoor) {
			// Iterate through all possible positions to place this new door
			for (int newDoorPos = 0; newDoorPos < n; ++newDoorPos) {
				// if (usedDoor >= k && newDoorPos >= 1)
				// 	break;
				// partialDist stores the sum of distance to fill rooms [i, j-1]
				ll partialDist = 0;
				// Iterate through all possible positions to place the last door
				// Find the minimum distance if we use this placement with our new door at i
				for (int lastDoorPos = newDoorPos + 1; lastDoorPos <= n; ++lastDoorPos) {
					// Add the amount of distance needed to fill the new room at j-1
					partialDist += rooms[lastDoorPos - 1] * (lastDoorPos - newDoorPos - 1);
					ll newDist = dp[usedDoor - 1][lastDoorPos];
					if (newDist < INT64_MAX)
						newDist += partialDist;
					dp[usedDoor][newDoorPos] = min(dp[usedDoor][newDoorPos], newDist);
					// print dp table
					cout << "dp table at startPos = " << startPos << ", usedDoor = " << usedDoor << ", newDoorPos = " << newDoorPos << ", lastDoorPos = " << lastDoorPos << endl;
					for (int DoorPos = 0; DoorPos <= n; ++DoorPos)
						cout << "DoorPos " << DoorPos << "	";
					cout << endl;
					for (int usedDoor = 0; usedDoor <= k; ++usedDoor) {
						cout << "usedDoor = " << usedDoor << ": ";
						for (int newDoorPos = 0; newDoorPos <= n; ++newDoorPos) {
							if (dp[usedDoor][newDoorPos] == INT64_MAX)
								cout << "inf" << " ";
							else
								cout << dp[usedDoor][newDoorPos] << " ";
						}
						cout << endl;
					}
					cout << endl;
				}

			}
		}
		// Update the best answer using the current dp answer
		minDist = min(minDist, dp[k][0]);
		// Put the first room to the end of the deque so that the first door would be placed at the second room
		int firstRoom = rooms.front();
		rooms.pop_front();
		rooms.push_back(firstRoom);

		cout << "minDist = min(minDist, dp[" << k << "][0]) = " << minDist << endl;
		// print rooms deque
		cout << "rooms deque: ";
		for (int r : rooms)
			cout << r << " ";
		cout << endl << endl;
	}

	freopen("cbarn2.out", "w", stdout);
	cout << minDist << endl;
}
